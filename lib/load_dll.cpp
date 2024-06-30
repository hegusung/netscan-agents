#include "load_dll.h"

#include "../lib/NoCRT.h"

fnLoadLibraryA pLoadLibraryA = NULL;

HMODULE LoadLibraryA_byname(const char* ModuleName) {
	// Check if existing
	HMODULE mod = GetModuleHandle_byname(ModuleName);

	if (mod == NULL)
	{
		if (pLoadLibraryA == NULL)
		{
			CTIME_API_HASH(LoadLibraryA);
			CTIME_STRING_HASH(KERNEL32, "KERNEL32.DLL");

			// Resolve LoadLibraryA
			HMODULE kernel32 = GetModuleHandle_byhash(KERNEL32_hash);
			if (kernel32 == NULL)
				return NULL;

			pLoadLibraryA = (fnLoadLibraryA)GetProcAddress_byhash(kernel32, LoadLibraryA_hash);
		}

		mod = pLoadLibraryA(ModuleName);
	}

	return mod;
}


HMODULE GetModuleHandle_byhash(unsigned int dwModuleNameHash) {

	if (dwModuleNameHash == NULL)
		return NULL;

#ifdef _WIN64
	PPEB      pPeb = (PEB*)(__readgsqword(0x60));
#elif _WIN32
	PPEB      pPeb = (PEB*)(__readfsdword(0x30));
#endif

	PPEB_LDR_DATA            pLdr = (PPEB_LDR_DATA)(pPeb->Ldr);
	PLDR_DATA_TABLE_ENTRY	pDte = (PLDR_DATA_TABLE_ENTRY)(pLdr->InMemoryOrderModuleList.Flink);

	while (pDte) {

		if (pDte->FullDllName.Length != NULL && pDte->FullDllName.Length < MAX_PATH) {

			// Converting `FullDllName.Buffer` to upper case string 
			CHAR UpperCaseDllName[MAX_PATH];

			DWORD i = 0;
			while (pDte->FullDllName.Buffer[i]) {
				UpperCaseDllName[i] = (CHAR)custom_toupper(pDte->FullDllName.Buffer[i]);
				i++;
			}
			UpperCaseDllName[i] = '\0';

			// hashing `UpperCaseDllName` and comparing the hash value to that's of the input `dwModuleNameHash`
			if (STRING_HASH(UpperCaseDllName) == dwModuleNameHash)
				return (HMODULE)(pDte->Reserved2[0]);

		}
		else {
			break;
		}

		pDte = *(PLDR_DATA_TABLE_ENTRY*)(pDte);
	}

	return NULL;
}

HMODULE GetModuleHandle_byname(const char* ModuleName) {

	if (ModuleName == NULL)
		return NULL;

	CHAR UpperCaseModuleName[MAX_PATH];
	DWORD i = 0;
	while (ModuleName[i]) {
		UpperCaseModuleName[i] = (CHAR)custom_toupper(ModuleName[i]);
		i++;
	}
	UpperCaseModuleName[i] = '\0';

#ifdef _WIN64
	PPEB      pPeb = (PEB*)(__readgsqword(0x60));
#elif _WIN32
	PPEB      pPeb = (PEB*)(__readfsdword(0x30));
#endif

	PPEB_LDR_DATA            pLdr = (PPEB_LDR_DATA)(pPeb->Ldr);
	PLDR_DATA_TABLE_ENTRY	pDte = (PLDR_DATA_TABLE_ENTRY)(pLdr->InMemoryOrderModuleList.Flink);

	while (pDte) {

		if (pDte->FullDllName.Length != NULL && pDte->FullDllName.Length < MAX_PATH) {

			// Converting `FullDllName.Buffer` to upper case string 
			CHAR UpperCaseDllName[MAX_PATH];

			DWORD i = 0;
			while (pDte->FullDllName.Buffer[i]) {
				UpperCaseDllName[i] = (CHAR)custom_toupper(pDte->FullDllName.Buffer[i]);
				i++;
			}
			UpperCaseDllName[i] = '\0';

			// hashing `UpperCaseDllName` and comparing the hash value to that's of the input `dwModuleNameHash`
			if (strcmp(UpperCaseModuleName, UpperCaseDllName) == 0)
				return (HMODULE)(pDte->Reserved2[0]);

		}
		else {
			break;
		}

		pDte = *(PLDR_DATA_TABLE_ENTRY*)(pDte);
	}

	return NULL;
}

FARPROC GetProcAddress_byhash(HMODULE hModule, unsigned int dwApiNameHash) {

	printf2("GetProcAddress_byhash\n");
	if (hModule == NULL || dwApiNameHash == NULL)
		return NULL;

	PBYTE pBase = (PBYTE)hModule;

	PIMAGE_DOS_HEADER         pImgDosHdr = (PIMAGE_DOS_HEADER)pBase;
	if (pImgDosHdr->e_magic != IMAGE_DOS_SIGNATURE)
		return NULL;

	PIMAGE_NT_HEADERS         pImgNtHdrs = (PIMAGE_NT_HEADERS)(pBase + pImgDosHdr->e_lfanew);
	if (pImgNtHdrs->Signature != IMAGE_NT_SIGNATURE)
		return NULL;

	IMAGE_OPTIONAL_HEADER     ImgOptHdr = pImgNtHdrs->OptionalHeader;

	PIMAGE_DATA_DIRECTORY dataDirectory = &(ImgOptHdr.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]);

	PIMAGE_EXPORT_DIRECTORY   pImgExportDir = (PIMAGE_EXPORT_DIRECTORY)(pBase + ImgOptHdr.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);


	PDWORD  FunctionNameArray = (PDWORD)(pBase + pImgExportDir->AddressOfNames);
	PDWORD  FunctionAddressArray = (PDWORD)(pBase + pImgExportDir->AddressOfFunctions);
	PWORD   FunctionOrdinalArray = (PWORD)(pBase + pImgExportDir->AddressOfNameOrdinals);

	for (DWORD i = 0; i < pImgExportDir->NumberOfFunctions; i++) {
		CHAR* pFunctionName = (CHAR*)(pBase + FunctionNameArray[i]);
		PVOID	pFunctionAddress = (PVOID)(pBase + FunctionAddressArray[FunctionOrdinalArray[i]]);

		// Hashing every function name pFunctionName
		// If both hashes are equal then we found the function we want 
		//unsigned int func_hash = string_hash(pFunctionName, SEED);
		//printf2("%s: %x: 0x%x\n", pFunctionName, func_hash, pFunctionAddress);
		if (dwApiNameHash == STRING_HASH(pFunctionName)) {

			// Forwarded exports support
			if ((FunctionAddressArray[FunctionOrdinalArray[i]] >= dataDirectory->VirtualAddress) && (FunctionAddressArray[FunctionOrdinalArray[i]] < dataDirectory->VirtualAddress + dataDirectory->Size))
			{
				// Get the name of the forwarder : DLL.FUNCTION
				char* forwarded_dll = (char*)((ULONG_PTR)pImgDosHdr + FunctionAddressArray[FunctionOrdinalArray[i]]);
				// Retrieve the function name with a simple split on '.'
				char* export_name = forwarded_dll;
				while (*export_name != '.') {
					if (*export_name == '\0') {
						return NULL;
					}
					export_name++;
				}
				size_t dll_name_length = export_name - forwarded_dll;
				export_name++;

				// create the module name
				CHAR module_name[MAX_PATH];
				memcpy(module_name, forwarded_dll, dll_name_length);
				module_name[dll_name_length] = '\0';
				strcat(module_name, ".dll");

				HMODULE mod = LoadLibraryA_byname(module_name);

				memset(module_name, 0, strlen(module_name));

				return GetProcAddress_byname(mod, export_name);
			}

			return (FARPROC)pFunctionAddress;
		}
	}

	return NULL;
}

#define DEREF_32( name )*(DWORD *)(name)

FARPROC GetProcAddress_byname(HMODULE hModule, const char* apiName) {
	// apiName can be an ordinal !

	if (hModule == NULL || apiName == NULL)
		return NULL;

	PBYTE pBase = (PBYTE)hModule;

	PIMAGE_DOS_HEADER         pImgDosHdr = (PIMAGE_DOS_HEADER)pBase;
	if (pImgDosHdr->e_magic != IMAGE_DOS_SIGNATURE)
		return NULL;

	PIMAGE_NT_HEADERS         pImgNtHdrs = (PIMAGE_NT_HEADERS)(pBase + pImgDosHdr->e_lfanew);
	if (pImgNtHdrs->Signature != IMAGE_NT_SIGNATURE)
		return NULL;

	IMAGE_OPTIONAL_HEADER     ImgOptHdr = pImgNtHdrs->OptionalHeader;

	PIMAGE_DATA_DIRECTORY dataDirectory = &(ImgOptHdr.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]);

	PIMAGE_EXPORT_DIRECTORY   pImgExportDir = (PIMAGE_EXPORT_DIRECTORY)(pBase + ImgOptHdr.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);


	PDWORD  FunctionNameArray = (PDWORD)(pBase + pImgExportDir->AddressOfNames);
	PDWORD  FunctionAddressArray = (PDWORD)(pBase + pImgExportDir->AddressOfFunctions);
	PWORD   FunctionOrdinalArray = (PWORD)(pBase + pImgExportDir->AddressOfNameOrdinals);

	// Check if it is an ordinal
	if (((DWORD)apiName & 0xFFFF0000) == 0x00000000)
	{
		// import by ordinal...

		// use the import ordinal (- export ordinal base) as an index into the array of addresses
		PDWORD uiAddressArray = FunctionAddressArray + ((IMAGE_ORDINAL((DWORD)apiName) - pImgExportDir->Base) * sizeof(DWORD));

		// resolve the address for this imported function
		return (FARPROC)(pBase + DEREF_32(uiAddressArray));
	}

	for (DWORD i = 0; i < pImgExportDir->NumberOfFunctions; i++) {

		CHAR* pFunctionName = (CHAR*)(pBase + FunctionNameArray[i]);
		PVOID	pFunctionAddress = (PVOID)(pBase + FunctionAddressArray[FunctionOrdinalArray[i]]);

		if (strcmp(pFunctionName, apiName) == 0) {

			// Forwarded exports support
			if ((FunctionAddressArray[FunctionOrdinalArray[i]] >= dataDirectory->VirtualAddress) && (FunctionAddressArray[FunctionOrdinalArray[i]] < dataDirectory->VirtualAddress + dataDirectory->Size))
			{
				// Get the name of the forwarder : DLL.FUNCTION
				char* forwarded_dll = (char*)((ULONG_PTR)pImgDosHdr + FunctionAddressArray[FunctionOrdinalArray[i]]);
				// Retrieve the function name with a simple split on '.'
				char* export_name = forwarded_dll;
				while (*export_name != '.') {
					if (*export_name == '\0') {
						return NULL;
					}
					export_name++;
				}
				size_t dll_name_length = export_name - forwarded_dll;
				export_name++;

				// create the module name
				CHAR module_name[MAX_PATH];
				memcpy(module_name, forwarded_dll, dll_name_length);
				module_name[dll_name_length] = '\0';
				strcat(module_name, ".dll");

				HMODULE mod = LoadLibraryA_byname(module_name);

				memset(module_name, 0, strlen(module_name));

				return GetProcAddress_byname(mod, export_name);
			}

			return (FARPROC)pFunctionAddress;
		}
	}

	return NULL;
}

char custom_toupper(char c) {
	// Check if the character is a lowercase letter
	if (c >= 'a' && c <= 'z') {
		// Convert to uppercase by subtracting the difference between 'a' and 'A'
		return c - ('a' - 'A');
	}
	// Return the character unchanged if it is not a lowercase letter
	return c;
}
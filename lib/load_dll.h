#pragma once

#ifndef LOADDLL_HEADER
#define LOADDLL_HEADER

#include <Windows.h>
#include <winternl.h>

#define SEED     0x47362036

#define KERNEL32_hash 0xd5b0ce0a
#define USER32_hash 0x76e0980d
#define NTDLL_hash 0xbd8b6973
#define WININET_hash 0x423c119a

// Kernel32
#define LoadLibraryA_hash 0x890fb7f9
#define GetProcAddress_hash 0x874abac6
#define FreeLibrary_hash 0xf51ef7cc
#define VirtualProtect_hash 0xe8905580
#define VirtualAlloc_hash 0x1a41f574
#define VirtualFree_hash 0x9f82b151
#define GetNativeSystemInfo_hash 0xa49b1ec1
#define HeapAlloc_hash 0xf5684590
#define GetProcessHeap_hash 0x89f2a5ee
#define HeapFree_hash 0xc3a02816
#define GetThreadLocale_hash 0xaa9dadab
#define lstrlenA_hash 0x4e447813
#define IsBadReadPtr_hash 0xfb8f1a32

// Wininet
#define InternetOpenA_hash 0x2da71074
#define InternetConnectA_hash 0xcff4d4fb
#define InternetCloseHandle_hash 0x6d210d26
#define HttpOpenRequestA_hash 0xb6e1b1ff
#define HttpSendRequestA_hash 0xe6d84958
#define InternetReadFile_hash 0x7cd11b19

#ifdef __cplusplus
extern "C" {
#endif

	// MurmurOAAT_32
	unsigned int string_hash(const char* str, unsigned int h);

	FARPROC GetProcAddress_byhash(HMODULE hModule, unsigned int dwApiNameHash);
	HMODULE GetModuleHandle_byhash(unsigned int dwModuleNameHash);

	char custom_toupper(char c);

#ifdef __cplusplus
}
#endif

#endif
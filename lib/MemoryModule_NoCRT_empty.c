/*
 * Memory DLL loading code
 * Version 0.0.4
 *
 * Copyright (c) 2004-2015 by Joachim Bauch / mail@joachim-bauch.de
 * http://www.joachim-bauch.de
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is MemoryModule.c
 *
 * The Initial Developer of the Original Code is Joachim Bauch.
 *
 * Portions created by Joachim Bauch are Copyright (C) 2004-2015
 * Joachim Bauch. All Rights Reserved.
 *
 *
 * THeller: Added binary search in MemoryGetProcAddress function
 * (#define USE_BINARY_SEARCH to enable it).  This gives a very large
 * speedup for libraries that exports lots of functions.
 *
 * These portions are Copyright (C) 2013 Thomas Heller.
 */

#include "MemoryModule_NoCRT.h"
#include <Windows.h>

typedef int (WINAPI* ExeEntryProc)(void);

#ifdef _WIN64
typedef struct POINTER_LIST {
    struct POINTER_LIST* next;
    void* address;
} POINTER_LIST;
#endif

typedef struct {
    PIMAGE_NT_HEADERS headers;
    unsigned char* codeBase;
    HCUSTOMMODULE* modules;
    int numModules;
    BOOL initialized;
    BOOL isDLL;
    BOOL isRelocated;
    CustomAllocFunc alloc;
    CustomFreeFunc free;
    CustomLoadLibraryFunc loadLibrary;
    CustomGetProcAddressFunc getProcAddress;
    CustomFreeLibraryFunc freeLibrary;
    struct ExportNameEntry* nameExportsTable;
    void* userdata;
    ExeEntryProc exeEntry;
    DWORD pageSize;
#ifdef _WIN64
    POINTER_LIST* blockedMemory;
#endif
} MEMORYMODULE, * PMEMORYMODULE;

typedef struct {
    LPVOID address;
    LPVOID alignedAddress;
    SIZE_T size;
    DWORD characteristics;
    BOOL last;
} SECTIONFINALIZEDATA, * PSECTIONFINALIZEDATA;

BOOL init_memorymodule()
{
    return TRUE;
}

static inline uintptr_t
AlignValueDown(uintptr_t value, uintptr_t alignment) {
    return 0;
}

static inline LPVOID
AlignAddressDown(LPVOID address, uintptr_t alignment) {
    return 0;
}

static inline size_t
AlignValueUp(size_t value, size_t alignment) {
    return 0;
}

static inline void*
OffsetPointer(void* data, ptrdiff_t offset) {
    return 0;
}

static inline void
OutputLastError(const char *msg)
{

}

#ifdef _WIN64
static void
FreePointerList(POINTER_LIST *head, CustomFreeFunc freeMemory, void *userdata)
{
   
}
#endif

static BOOL
CheckSize(size_t size, size_t expected) {
    
    return TRUE;
}

static BOOL
CopySections(const unsigned char *data, size_t size, PIMAGE_NT_HEADERS old_headers, PMEMORYMODULE module)
{
    return TRUE;
}

static SIZE_T
GetRealSectionSize(PMEMORYMODULE module, PIMAGE_SECTION_HEADER section) {
    DWORD size = section->SizeOfRawData;
    if (size == 0) {
        if (section->Characteristics & IMAGE_SCN_CNT_INITIALIZED_DATA) {
            size = module->headers->OptionalHeader.SizeOfInitializedData;
        } else if (section->Characteristics & IMAGE_SCN_CNT_UNINITIALIZED_DATA) {
            size = module->headers->OptionalHeader.SizeOfUninitializedData;
        }
    }
    return (SIZE_T) size;
}

static BOOL
FinalizeSection(PMEMORYMODULE module, PSECTIONFINALIZEDATA sectionData) {
    return TRUE;
}

static BOOL
FinalizeSections(PMEMORYMODULE module)
{
    return TRUE;
}

static BOOL
ExecuteTLS(PMEMORYMODULE module)
{
    return TRUE;
}

static BOOL
PerformBaseRelocation(PMEMORYMODULE module, ptrdiff_t delta)
{
    return TRUE;
}

static BOOL
BuildImportTable(PMEMORYMODULE module)
{
    return TRUE;
}

LPVOID MemoryDefaultAlloc(LPVOID address, SIZE_T size, DWORD allocationType, DWORD protect, void* userdata)
{
	return NULL;
}

BOOL MemoryDefaultFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType, void* userdata)
{
	return TRUE;
}

HCUSTOMMODULE MemoryDefaultLoadLibrary(LPCSTR filename, void *userdata)
{
    return NULL;
}

FARPROC MemoryDefaultGetProcAddress(HCUSTOMMODULE module, LPCSTR name, void *userdata)
{
    return NULL;
}

void MemoryDefaultFreeLibrary(HCUSTOMMODULE module, void *userdata)
{
   
}

HMEMORYMODULE MemoryLoadLibrary(const void *data, size_t size)
{
    return NULL;
}

HMEMORYMODULE MemoryLoadLibraryEx(const void *data, size_t size,
    CustomAllocFunc allocMemory,
    CustomFreeFunc freeMemory,
    CustomLoadLibraryFunc loadLibrary,
    CustomGetProcAddressFunc getProcAddress,
    CustomFreeLibraryFunc freeLibrary,
    void *userdata)
{
    return NULL;
}

static int _compare(const void *a, const void *b)
{
    return 0;
}

static int _find(const void *a, const void *b)
{
    return 0;
}

FARPROC MemoryGetProcAddress(HMEMORYMODULE mod, LPCSTR name)
{
    return 0;
}

void MemoryFreeLibrary(HMEMORYMODULE mod)
{
    
}

int MemoryCallEntryPoint(HMEMORYMODULE mod)
{
    return 0;
}

#define DEFAULT_LANGUAGE        MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL)

HMEMORYRSRC MemoryFindResource(HMEMORYMODULE module, LPCTSTR name, LPCTSTR type)
{
    return NULL;
}

static PIMAGE_RESOURCE_DIRECTORY_ENTRY _MemorySearchResourceEntry(
    void *root,
    PIMAGE_RESOURCE_DIRECTORY resources,
    LPCTSTR key)
{

    return NULL;
}

HMEMORYRSRC MemoryFindResourceEx(HMEMORYMODULE module, LPCTSTR name, LPCTSTR type, WORD language)
{
    
    return NULL;
}

DWORD MemorySizeofResource(HMEMORYMODULE module, HMEMORYRSRC resource)
{
    return 0;
}

LPVOID MemoryLoadResource(HMEMORYMODULE module, HMEMORYRSRC resource)
{
    return NULL;
}

int
MemoryLoadString(HMEMORYMODULE module, UINT id, LPTSTR buffer, int maxsize)
{
    return 0;
}

int
MemoryLoadStringEx(HMEMORYMODULE module, UINT id, LPTSTR buffer, int maxsize, WORD language)
{
    return 0;
}


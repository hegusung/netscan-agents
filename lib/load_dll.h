#pragma once

/*
* Custom GetProcAddress / GetModuleHandle
* Project : https://github.com/hegusung/netscan-agents
*/

#ifndef LOADDLL_HEADER
#define LOADDLL_HEADER

#include <Windows.h>

#include "obfuscation.h"


typedef HMODULE(WINAPI* fnLoadLibraryA)(LPCSTR lpLibFileName);

#ifdef __cplusplus
extern "C" {
#endif

	HMODULE LoadLibraryA_byname(const char* ModuleName);
	FARPROC GetProcAddress_byhash(HMODULE hModule, unsigned int dwApiNameHash);
	FARPROC GetProcAddress_byname(HMODULE hModule, const char* apiName);
	HMODULE GetModuleHandle_byhash(unsigned int dwModuleNameHash);
	HMODULE GetModuleHandle_byname(const char* ModuleName);

	char custom_toupper(char c);

#ifdef __cplusplus
}
#endif

#endif

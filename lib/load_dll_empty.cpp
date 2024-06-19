#include "load_dll.h"

// MurmurOAAT_32
unsigned int string_hash(const char* str, unsigned int h)
{
	return 0;
}

HMODULE GetModuleHandle_byhash(unsigned int dwModuleNameHash) {

	return NULL;
}

FARPROC GetProcAddress_byhash(HMODULE hModule, unsigned int dwApiNameHash) {
	return NULL;
}

char custom_toupper(char c) {
	return 'A';
}
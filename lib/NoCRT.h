#ifndef __NOCRT_HEADER
#define __NOCRT_HEADER

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

void __chkstk(size_t s);

/*
* Memory related functions:
* - malloc
* - realloc
* - free
* - memcpy
* - memcmp
*/

void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

#pragma intrinsic(memcpy)
#pragma function(memcpy)
void* memcpy(void* dest, const void* src, size_t count);
#pragma intrinsic(memmove)
#pragma function(memmove)
void* memmove(void* dest, const void* src, size_t num);
#pragma intrinsic(memset)
#pragma function(memset)
void* memset(void* dest, int c, size_t num);
#pragma intrinsic(memcmp)
#pragma function(memcmp)
int memcmp(const void* ptr1, const void* ptr2, size_t num);

/*
* String operations
*
*/

#pragma intrinsic(strcmp)
#pragma function(strcmp)
int strcmp(const char* str1, const char* str2);
#pragma intrinsic(strlen)
#pragma function(strlen)
size_t strlen(const char* str);
#pragma intrinsic(strcpy)
#pragma function(strcpy)
char* strcpy(char* dest, const char* src);
#pragma intrinsic(strcat)
#pragma function(strcat)
char* strcat(char* dest, const char* src);


/*
* String/Int conversion
* - mbstowcs
* - wcstombs
* - atoi
* - strtol
*/

size_t mbstowcs(wchar_t* dest, const char* src, size_t max);
size_t wcstombs(char* dest, const wchar_t* src, size_t max);
int _wcsnicmp(const wchar_t* str1, const wchar_t* str2, size_t count);
int atoi(const char* str);
char* itoa(int value, char* str, int base);
long strtol(const char* str, char** endptr, int base);

/*
* Other:
* - bsearch
* - qsort
*/

void* bsearch(const void* key, const void* base, size_t num, size_t size, int (*cmp)(const void*, const void*));
void qsort(void* base, size_t num, size_t size, int (*cmp)(const void*, const void*));
int printf2(const char* format, ...);



#ifdef __cplusplus
}
#endif

void* operator new(size_t size);

void* operator new[](size_t size);

void operator delete(void* p, size_t size);

void operator delete[](void* p, size_t size);

#endif  // __NOCRT_HEADER
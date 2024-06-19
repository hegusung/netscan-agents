#include "NoCRT.h"

/* 
* Reimplementation of the following functions:
* - malloc
* - realloc
* - free
* - memcpy
* - memcmp
*/

HANDLE heap = NULL;

void __chkstk(size_t s) {}

void initialize_heap() {
}

void* malloc(size_t size) {
    return NULL;
}

void* realloc(void* ptr, size_t size) {
    return NULL;
}

void free(void* ptr) {

}

void* memcpy(void* dest, const void* src, size_t count) {
    return NULL;
}

void* memmove(void* dest, const void* src, size_t num) {
    return NULL;
}

void* memset(void* dest, int c, size_t num) {
    return NULL;
}

int memcmp(const void* ptr1, const void* ptr2, size_t num) {
    return 0;
}

/*
* String operations
* - strcmp
* - strlen
* - strcpy
*/

int strcmp(const char* str1, const char* str2) {
    return 0;
}

size_t strlen(const char* str) {
    return 0;
}

char* strcpy(char* dest, const char* src) {
    return NULL;
}


char* strcat(char* first, const char* second) {
    return NULL;
}


/*
* String conversion
* - mbstowcs
* - wcstombs
* - wcsnicmp
* - atoi
* - strtol
*/

size_t mbstowcs(wchar_t* dest, const char* src, size_t max) {
    return 0;
}

size_t wcstombs(char* dest, const wchar_t* src, size_t max) {
    return 0;
}

int _wcsnicmp(const wchar_t* str1, const wchar_t* str2, size_t count) {
    return 0;
}

int atoi(const char* str) {
    return 0;
}

char* itoa(int value, char* str, int base) {
    return NULL;
}

long strtol(const char* str, char** endptr, int base) {
    return 0;
}

/*
* Other:
* - bsearch
* - qsort
*/


void* bsearch(const void* key, const void* base, size_t num, size_t size, int (*cmp)(const void*, const void*)) {
    return NULL; // Element not found
}

// Swaps two elements of size 'size'
void swap(void* a, void* b, size_t size) {
    
}

// Partition function for quicksort
void* partition(void* base, size_t size, int (*cmp)(const void*, const void*), int low, int high) {
    return NULL;
}

// Quick sort recursive function
void quicksort(void* base, size_t size, int (*cmp)(const void*, const void*), int low, int high) {
    
}

// Public function to sort an array
void qsort(void* base, size_t num, size_t size, int (*cmp)(const void*, const void*)) {
    
}

/*
int printf2(const char* format, ...) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return NULL;
    }

    // To improve... buffer overflow here
    char buffer[1024];
    char* bufptr = buffer;
    const char* f = format;
    va_list args;
    va_start(args, format);

    while (*f) {
        if (*f == '%' && *(f + 1) != '\0') {
            f++;
            switch (*f) {
            case 'd': {
                int value = va_arg(args, int);
                bufptr += wsprintfA(bufptr, "%d", value);
                break;
            }
            case 'x': {
                int value = va_arg(args, int);
                bufptr += wsprintfA(bufptr, "%x", value);
                break;
            }
            case 'C': {
                unsigned char value = va_arg(args, unsigned char);
                bufptr += wsprintfA(bufptr, "%02x", value);
                break;
            }
            case 's': {
                const char* str = va_arg(args, const char*);
                while (*str) {
                    *bufptr++ = *str++;
                }
                break;
            }
            case 'c': {
                char c = (char)va_arg(args, int);
                *bufptr++ = c;
                break;
            }
            default: {
                *bufptr++ = '%';
                *bufptr++ = *f;
                break;
            }
            }
        }
        else {
            *bufptr++ = *f;
        }
        f++;
    }

    *bufptr = '\0';

    DWORD written;
    WriteConsoleA(hConsole, buffer, (DWORD)(bufptr - buffer), &written, NULL);

    va_end(args);

    return NULL;
}
*/

// CPP

void* operator new(size_t size)
{
    return malloc(size);
}

void* operator new[](size_t size)
{
    return malloc(size);
}

void operator delete(void* p, size_t size)
{
    free(p);
}

void operator delete[](void* p, size_t size)
{
    free(p);
}

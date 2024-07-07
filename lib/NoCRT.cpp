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

extern "C" int _fltused = 0;

void initialize_heap() {
    if (heap == NULL) {
        //heap = HeapCreate(0, 0, 0);  // Default options, initial size, and maximum size
        heap = GetProcessHeap();
    }
}

void* malloc(size_t size) {

    initialize_heap();

    if (size == 0) {
        return NULL;
    }

    void* ptr = HeapAlloc(heap, HEAP_ZERO_MEMORY, size);

    if (ptr == NULL) {
        // Allocation failed

        return NULL;
    }

    return ptr;
}

void* realloc(void* ptr, size_t size) {
    initialize_heap();

    if (ptr == NULL) {
        // If the original pointer is NULL, realloc should act like malloc
        return malloc(size);
    }

    if (size == 0) {
        // If the size is zero, realloc should act like free
        free(ptr);
        return NULL;
    }

    void* new_ptr = HeapReAlloc(heap, 0, ptr, size);
    if (new_ptr == NULL) {
        return NULL;
    }

    return new_ptr;
}

void free(void* ptr) {

    if (ptr == NULL) {
        return;
    }

    HeapFree(heap, 0, ptr);
}

void* memcpy(void* dest, const void* src, size_t count) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }
    RtlMoveMemory(dest, src, count);
    return dest;
}

void* memmove(void* dest, const void* src, size_t num) {
    if (dest == NULL || src == NULL || num == 0) {
        return dest;
    }

    BYTE* d = (BYTE*)dest;
    const BYTE* s = (const BYTE*)src;

    if (d < s) {
        // Non-overlapping or source is before destination
        for (size_t i = 0; i < num; i++) {
            d[i] = s[i];
        }
    }
    else if (d > s) {
        // Overlapping, destination is after source
        for (size_t i = num; i > 0; i--) {
            d[i - 1] = s[i - 1];
        }
    }

    return dest;
}

void* memset(void* dest, int c, size_t num) {
    if (dest == NULL || num == 0) {
        return dest;
    }

    BYTE* d = (BYTE*)dest;

    for (size_t i = 0; i < num; i++) {
        d[i] = (BYTE)c;
    }

    return dest;
}

int memcmp(const void* ptr1, const void* ptr2, size_t num) {
    if (ptr1 == NULL || ptr2 == NULL) {
        return -1; // Or another error code, depending on your error handling preference
    }

    const BYTE* bytePtr1 = (const BYTE*)ptr1;
    const BYTE* bytePtr2 = (const BYTE*)ptr2;

    for (size_t i = 0; i < num; ++i) {
        if (bytePtr1[i] != bytePtr2[i]) {
            return bytePtr1[i] - bytePtr2[i];
        }
    }

    return 0;
}

/*
* String operations
* - strcmp
* - strlen
* - strcpy
*/

int strcmp(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1; // Or another error code, depending on your error handling preference
    }

    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

int wcscmp(const wchar_t* str1, const wchar_t* str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1; // Or another error code, depending on your error handling preference
    }

    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    return *(wchar_t*)str1 - *(wchar_t*)str2;
}

size_t strlen(const char* str) {
    const char* s = str;
    while (*s) {
        ++s;
    }
    return s - str;
}

char* strcpy(char* dest, const char* src) {
    char* d = dest;
    while ((*d++ = *src++) != '\0') {
        // copying each character from src to dest
    }
    return dest;
}


char* strcat(char* first, const char* second) {
    return strcpy(first + strlen(first), second);
}

size_t wcslen(const wchar_t* str) {
    const wchar_t* s = str;
    while (*s) {
        ++s;
    }
    return s - str;
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
    if (src == NULL) {
        return (size_t)-1;
    }

    // Determine the required size of the wide-character string
    int requiredSize = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0);
    if (requiredSize == 0) {
        return (size_t)-1;
    }

    // If dest is NULL, we just return the size needed
    if (dest == NULL) {
        return (size_t)requiredSize - 1; // -1 to exclude the null terminator
    }

    // Convert the multi-byte string to a wide-character string
    int charsConverted = MultiByteToWideChar(CP_ACP, 0, src, -1, dest, (int)max);
    if (charsConverted == 0) {
        return (size_t)-1;
    }

    // Return the number of wide characters written, excluding the null terminator
    return (size_t)charsConverted - 1;
}

size_t wcstombs(char* dest, const wchar_t* src, size_t max) {
    if (src == NULL || max == 0) {
        return (size_t)-1;
    }

    int num_bytes = WideCharToMultiByte(CP_ACP, 0, src, -1, NULL, 0, NULL, NULL);
    if (num_bytes == 0) {
        return (size_t)-1;
    }

    if (dest == NULL) {
        return num_bytes - 1; // excluding the null terminator
    }

    int converted = WideCharToMultiByte(CP_ACP, 0, src, -1, dest, max, NULL, NULL);
    if (converted == 0) {
        return (size_t)-1;
    }

    return converted - 1; // excluding the null terminator
}

int _wcsnicmp(const wchar_t* str1, const wchar_t* str2, size_t count) {
    if (str1 == NULL || str2 == NULL || count == 0) {
        return 0; // Strings are equal when either is NULL or count is 0
    }

    int result = 0;
    int comparisonCount = (int)count; // Convert size_t to int for use in CompareStringW

    // Perform case-insensitive comparison up to the specified count
    int cmpResult = CompareStringW(LOCALE_USER_DEFAULT, NORM_IGNORECASE, str1, comparisonCount, str2, comparisonCount);
    if (cmpResult == 0) {
        return 0; // Error occurred, consider strings equal
    }
    else if (cmpResult == CSTR_EQUAL) {
        return 0; // Strings are equal
    }
    else if (cmpResult == CSTR_LESS_THAN) {
        result = -1; // str1 is less than str2
    }
    else if (cmpResult == CSTR_GREATER_THAN) {
        result = 1; // str1 is greater than str2
    }

    return result;
}

int atoi(const char* str) {
    if (str == NULL) {
        return 0;
    }

    int result = 0;
    int sign = 1;

    // Skip leading whitespace
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r') {
        str++;
    }

    // Check for sign
    if (*str == '-' || *str == '+') {
        if (*str == '-') {
            sign = -1;
        }
        str++;
    }

    // Convert digits to integer
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    return result * sign;
}

char* itoa(int value, char* str, int base) {
    if (str == NULL || base < 2 || base > 36) {
        return NULL;
    }

    char* ptr = str;
    char* end = str;
    int sign = 0;

    // Handle negative numbers for base 10
    if (value < 0 && base == 10) {
        sign = 1;
        value = -value;
    }

    // Process individual digits
    do {
        int digit = value % base;
        *end++ = (digit > 9) ? (digit - 10 + 'a') : (digit + '0');
        value /= base;
    } while (value > 0);

    // Add negative sign for base 10
    if (sign) {
        *end++ = '-';
    }

    // Null-terminate the string
    *end = '\0';

    // Reverse the string
    char* start = str;
    end--;
    while (start < end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }

    return str;
}

long strtol(const char* str, char** endptr, int base) {
    if (str == NULL) {
        if (endptr != NULL) {
            *endptr = NULL;
        }
        return 0;
    }

    long result = 0;
    int sign = 1;

    // Skip leading whitespace
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r') {
        str++;
    }

    // Check for sign
    if (*str == '-' || *str == '+') {
        if (*str == '-') {
            sign = -1;
        }
        str++;
    }

    // Determine base if not specified
    if (base == 0) {
        if (*str == '0') {
            if (*(str + 1) == 'x' || *(str + 1) == 'X') {
                base = 16;
                str += 2;
            }
            else {
                base = 8;
                str++;
            }
        }
        else {
            base = 10;
        }
    }
    else if (base == 16 && *str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
        str += 2;
    }

    // Convert digits to integer
    while (*str) {
        int digit;
        if (*str >= '0' && *str <= '9') {
            digit = *str - '0';
        }
        else if (*str >= 'a' && *str <= 'f') {
            digit = *str - 'a' + 10;
        }
        else if (*str >= 'A' && *str <= 'F') {
            digit = *str - 'A' + 10;
        }
        else {
            break; // Invalid character, stop parsing
        }

        if (digit >= base) {
            break; // Digit is larger than the base, stop parsing
        }

        result = result * base + digit;
        str++;
    }

    // Set endptr
    if (endptr != NULL) {
        *endptr = (char*)str;
    }

    return result * sign;
}

/*
* Other:
* - bsearch
* - qsort
*/


void* bsearch(const void* key, const void* base0,
    size_t nmemb, size_t size,
    int (*compar)(const void*, const void*))
{
    const char* base = (const char*)base0;
    int lim, cmp;
    const void* p;

    for (lim = nmemb; lim != 0; lim >>= 1) {
        p = base + (lim >> 1) * size;
        cmp = (*compar)(key, p);
        if (cmp == 0)
            return (void*)p;
        if (cmp > 0) {	/* key > p: move right */
            base = (const char*)p + size;
            lim--;
        } /* else move left */
    }
    return (NULL);
}

// Swaps two elements of size 'size'
void swap(void* a, void* b, size_t size) {
    void* temp = HeapAlloc(GetProcessHeap(), 0, size);
    if (temp == NULL) {
        ExitProcess(EXIT_FAILURE); // Exit if memory allocation fails
    }

    RtlMoveMemory(temp, a, size);
    RtlMoveMemory(a, b, size);
    RtlMoveMemory(b, temp, size);

    HeapFree(GetProcessHeap(), 0, temp);
}

// Partition function for quicksort
void* partition(void* base, size_t size, int (*cmp)(const void*, const void*), int low, int high) {
    char* baseChar = (char*)base;
    void* pivot = baseChar + high * size;
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (cmp(baseChar + j * size, pivot) <= 0) {
            ++i;
            swap(baseChar + i * size, baseChar + j * size, size);
        }
    }
    swap(baseChar + (i + 1) * size, baseChar + high * size, size);
    return (void*)(i + 1);
}

// Quick sort recursive function
void quicksort(void* base, size_t size, int (*cmp)(const void*, const void*), int low, int high) {
    if (low < high) {
        int pi = (int)partition(base, size, cmp, low, high);

        quicksort(base, size, cmp, low, pi - 1);
        quicksort(base, size, cmp, pi + 1, high);
    }
}

// Public function to sort an array
void qsort(void* base, size_t num, size_t size, int (*cmp)(const void*, const void*)) {
    if (num > 0 && size > 0) {
        quicksort(base, size, cmp, 0, (int)num - 1);
    }
}


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

    /*
    HANDLE write = CreateFileA(TEXT("debug3.txt"), FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(write, buffer, (DWORD)(bufptr - buffer), 0, 0);
    CloseHandle(write);
    */

    va_end(args);

    return NULL;
}

// Custom vsnprintf implementation using wsprintfA
int vsnprintf(char* buffer, size_t count, const char* format, va_list argptr) {

    // Allocate a temporary buffer that we will format into
    char temp[4096];
    int result = wvsprintfA(temp, format, argptr);

    // Copy the formatted string to the provided buffer with truncation if necessary
    if (buffer != NULL)
    {
        if (count > result)
        {
            strcpy(buffer, temp);
            buffer[result] = '\0';
        }
        else
        {
            return -1;
        }

    }

    return result;
}

// https://frankcheng.com/win32/double_string.htm
void DoubleToCHAR(const double num, char* lpsz, DWORD dwSize)
{
    VARIANT vFrom, vTo;
    vFrom.vt = VT_R8;
    vFrom.dblVal = num;
    VariantInit(&vTo);
    VariantChangeType(&vTo, &vFrom, 0, VT_BSTR);
    WideCharToMultiByte(CP_ACP, 0, vTo.bstrVal, -1, lpsz, dwSize, NULL, NULL);
    SysFreeString(vTo.bstrVal);
}

// https://frankcheng.com/win32/double_string.htm
void DoubleToWCHAR(const double num, wchar_t* lpsz, DWORD dwSize)
{
    VARIANT vFrom, vTo;
    vFrom.vt = VT_R8;
    vFrom.dblVal = num;
    VariantInit(&vTo);
    VariantChangeType(&vTo, &vFrom, 0, VT_BSTR);
    lstrcpynW(lpsz, vTo.bstrVal, dwSize);
    SysFreeString(vTo.bstrVal);
}

// Custom implementation of rand() using Windows API
int rand() {
    // Buffer to store the random number
    unsigned long randNum = 0;

    // Generate the random number
    NTSTATUS status = BCryptGenRandom(
        NULL,                        // Algorithm handle, can be NULL for default RNG
        (PUCHAR)&randNum, // Buffer to receive the random number
        sizeof(randNum),        // Size of the buffer
        BCRYPT_USE_SYSTEM_PREFERRED_RNG // Use the system preferred RNG
    );

    // Return the random number within the range of RAND_MAX
    return randNum % RAND_MAX;
}


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

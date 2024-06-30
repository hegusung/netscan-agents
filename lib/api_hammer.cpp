#include "api_hammer.h"

#define TMPFILE "results.tmp"

void temp_file_creation()
{
    CHAR     szPath[MAX_PATH * 2],
        szTmpPath[MAX_PATH];
    HANDLE    hRFile = INVALID_HANDLE_VALUE,
        hWFile = INVALID_HANDLE_VALUE;

    DWORD   dwNumberOfBytesRead = NULL,
        dwNumberOfBytesWritten = NULL;

    PUCHAR   pRandBuffer = NULL;
    SIZE_T  sBufferSize = 0;

    // Generate the random number
    NTSTATUS status = BCryptGenRandom(
        NULL,                        // Algorithm handle, can be NULL for default RNG
        (PUCHAR)sBufferSize, // Buffer to receive the random number
        sizeof(sBufferSize),        // Size of the buffer
        BCRYPT_USE_SYSTEM_PREFERRED_RNG // Use the system preferred RNG
    );


    // Getting the tmp folder path
    if (!GetTempPathA(MAX_PATH, szTmpPath)) {
        //printf("[!] GetTempPathW Failed With Error : %d \n", GetLastError());
        return;
    }

    strcpy(szPath, szTmpPath);
    strcat(szPath, TMPFILE);

    // Getting the tmp folder path
    if (!GetTempPathA(MAX_PATH, szTmpPath)) {
        //printf("[!] GetTempPathW Failed With Error : %d \n", GetLastError());
        return;
    }

    // Creating the file in write mode
    if ((hWFile = CreateFileA(szPath, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL)) == INVALID_HANDLE_VALUE) {
        //printf("[!] CreateFileW Failed With Error : %d \n", GetLastError());
        return;
    }

    // Allocating a buffer and filling it with a random value
    pRandBuffer = (PUCHAR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sBufferSize);

    // Generate the random number
    status = BCryptGenRandom(
        NULL,                        // Algorithm handle, can be NULL for default RNG
        pRandBuffer, // Buffer to receive the random number
        sBufferSize,        // Size of the buffer
        BCRYPT_USE_SYSTEM_PREFERRED_RNG // Use the system preferred RNG
    );

    // Writing the random data into the file
    if (!WriteFile(hWFile, pRandBuffer, sBufferSize, &dwNumberOfBytesWritten, NULL) || dwNumberOfBytesWritten != sBufferSize) {
        //printf("[!] WriteFile Failed With Error : %d \n", GetLastError());
        //printf("[i] Written %d Bytes of %d \n", dwNumberOfBytesWritten, sBufferSize);
        return;
    }

    // Clearing the buffer & closing the handle of the file
    RtlZeroMemory(pRandBuffer, sBufferSize);
    CloseHandle(hWFile);

    // Opening the file in read mode & delete when closed
    if ((hRFile = CreateFileA(szPath, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE, NULL)) == INVALID_HANDLE_VALUE) {
        //printf("[!] CreateFileW Failed With Error : %d \n", GetLastError());
        return;
    }

    // Reading the random data written before 	
    if (!ReadFile(hRFile, pRandBuffer, sBufferSize, &dwNumberOfBytesRead, NULL) || dwNumberOfBytesRead != sBufferSize) {
        //printf("[!] ReadFile Failed With Error : %d \n", GetLastError());
        //printf("[i] Read %d Bytes of %d \n", dwNumberOfBytesRead, sBufferSize);
        return;
    }

    // Clearing the buffer & freeing it
    RtlZeroMemory(pRandBuffer, sBufferSize);
    HeapFree(GetProcessHeap(), NULL, pRandBuffer);

    // Closing the handle of the file - deleting it
    CloseHandle(hRFile);
}
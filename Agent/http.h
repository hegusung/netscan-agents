#pragma once

/*
* Simple C++ HTTP GET/POST project with the following capabilities:
* - Dynamic loading of wininet API
* - Custom GetProcAddress / GetModuleHandle
* Project : https://github.com/hegusung/netscan-agents
*/

#ifndef HTTP_HEADER
#define HTTP_HEADER

#include <stdio.h>
#include <Windows.h>
#include <wininet.h>

#include "../lib/NoCRT.h"
#include "../lib/load_dll.h"



typedef HMODULE (WINAPI * fnLoadLibraryA)(LPCSTR lpLibFileName);

// Wininet.dll
typedef LPVOID (WINAPI * fnInternetOpenA)(LPCSTR lpszAgent, DWORD  dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD  dwFlags);
typedef HINTERNET (WINAPI * fnInternetConnectA)(HINTERNET hInternet, LPCSTR lpszServerName, INTERNET_PORT nServerPort, LPCSTR lpszUserName, LPCSTR lpszPassword, DWORD dwService, DWORD dwFlags, DWORD_PTR dwContext);
typedef BOOL (WINAPI * fnInternetCloseHandle)(HINTERNET hInternet);
typedef HINTERNET (WINAPI * fnHttpOpenRequestA)(HINTERNET hConnect, LPCSTR    lpszVerb, LPCSTR    lpszObjectName, LPCSTR    lpszVersion, LPCSTR    lpszReferrer, LPCSTR* lplpszAcceptTypes, DWORD     dwFlags, DWORD_PTR dwContext);
typedef BOOL (WINAPI * fnHttpSendRequestA)(HINTERNET hRequest, LPCSTR    lpszHeaders, DWORD     dwHeadersLength, LPVOID    lpOptional, DWORD     dwOptionalLength);
typedef BOOL (WINAPI * fnInternetReadFile)(HINTERNET hFile, LPVOID    lpBuffer, DWORD     dwNumberOfBytesToRead, LPDWORD   lpdwNumberOfBytesRead);

class HTTP
{
public:
	HTTP(const char* ip, int port, const char* useragent);
	bool load_success();
	int get(const char* path, char** output, size_t* output_size);
	int post(const char* path, const char* data, size_t data_size, char** output, size_t* output_size);
private:
	int init_request();
	void cleanup_request();
	int get_response_content(HINTERNET hRequest, char** output, size_t* output_size);
	// Data
	char* ip;
	int port;
	char* useragent;
	bool loaded = false;
	// Request
	HINTERNET hInternet = NULL;
	HINTERNET hConnect = NULL;
	HINTERNET hRequest = NULL;
	// Functions
	fnInternetCloseHandle pInternetCloseHandle = NULL;
	fnInternetReadFile pInternetReadFile = NULL;
	fnInternetOpenA pInternetOpenA = NULL;
	fnInternetConnectA pInternetConnectA = NULL;
	fnHttpOpenRequestA pHttpOpenRequestA = NULL;
	fnHttpSendRequestA pHttpSendRequestA = NULL;
};

#endif
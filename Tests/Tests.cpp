// Tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include "../lib/NoCRT.h"
#include "../lib/BSON.h"
//#include "../lib/obfuscation.h"
#include "../lib/load_dll.h"

/*
#define IP_hash 0x4fbf257c
#define PORT_hash 0xc1986f88
#define URI_GET_hash 0x2545979c
#define URI_POST_hash 0x560d6d01
#define FUNCTION_hash 0x645a4efa
*/

void pretty_print(const char* buffer, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		if ((i % 8) == 0)
		{
			printf2("\n");
		}
		printf2("%C ", buffer[i]);
	}
}

void test()
{
	OBFUSCATE(HELLO, "Hello my friend")

	printf2("%s\n", HELLO.decrypt());
}

typedef int (WINAPI * fnMessageBoxA)(HWND   hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT   uType);

int main()
{
    printf2("Hello \n");

	printf2("Seed: 0x%x\n", g_SEED);

	test();

	OBFUSCATE(USER32, "User32.dll");
	CTIME_API_HASH(MessageBoxA);

	HMODULE mod = LoadLibraryA_byname(USER32.decrypt());

	fnMessageBoxA pMessageBoxA = (fnMessageBoxA)GetProcAddress_byhash(mod, MessageBoxA_hash);

	OBFUSCATE(Title, "Yo mama");
	OBFUSCATE(Desc, "Decription");
	pMessageBoxA(NULL, Title.decrypt(), Desc.decrypt(), MB_OK);

	printf2("Seed: 0x%x\n", g_SEED);

	/*
	printf2("#define IP_hash 0x%x\n", bson_string_hash("ip", BSON_HASH_SEED));
	printf2("#define PORT_hash 0x%x\n", bson_string_hash("port", BSON_HASH_SEED));
	printf2("#define URI_GET_hash 0x%x\n", bson_string_hash("uri_get", BSON_HASH_SEED));
	printf2("#define URI_POST_hash 0x%x\n", bson_string_hash("uri_post", BSON_HASH_SEED));
	printf2("#define FUNCTION_hash 0x%x\n", bson_string_hash("function", BSON_HASH_SEED));
	*/

	
	BSONDict d1 = BSONDict();
	d1["ip"] = new BSONObject(string("192.168.56.1"));
	d1["port"] = new BSONObject(8001);
	d1["uri_get"] =  new BSONObject(string("/ressources/05acfd6534736a8e01a76f965c20d7b0"));
	d1["uri_post"] = new BSONObject(string("/ressources/94b67c11073a50427afcffc9d981ce94"));
	d1["function"] = new BSONObject(string("launch"));

	BSONObject d1_o = BSONObject(d1);
	string buffer = d1_o.create_structure();

	pretty_print(buffer.c_str(), buffer.length());
	printf2("\n\n");

	BSONObject d2_o;
	d2_o.parse(buffer.c_str());

	if (d2_o.IsDict())
	{
		printf2("It's a dict !\n");
		BSONDict d2 = d2_o.AsDict();

		CTIME_STRING_HASH(IP, "ip");

		if (exists_byhash(d2, IP_hash))
		{
			printf2("YEAH\n");
			string ip = get_byhash(d2, IP_hash)->AsString();
			printf2("IP: %s\n", ip.c_str());
		}
		else
		{
			printf2("Oh no !\n");
		}

		if (d2.exists("ip") && d2.exists("port"))
		{
			printf2("All fields exists\n");
			string ip = d2["ip"]->AsString();
			int port = d2["port"]->AsInteger();

			printf2("IP: %s, port: %d\n", ip.c_str(), port);
			//printf2("port: %d\n", port);
		}
		else
		{
			printf2("error\n");
		}
	}
	else
	{
		printf2("Not a dict :(\n");
	}
	

	printf2("\nDone\n");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#pragma once
#ifndef __BSON_HEADER
#define __BSON_HEADER

#include "NoCRT.h"
#include "NoCRT_string.h"
#include "NoCRT_list.h"
#include "NoCRT_map.h"
#include "obfuscation.h"

//#define BSON_HASH_SEED     0x47362036
// MurmurOAAT_32
//unsigned int bson_string_hash(const char* str, unsigned int h);

class BSONObject;
typedef list<BSONObject*> BSONArray;
typedef map<string, BSONObject*> BSONDict;


BSONObject* get_byhash(BSONDict dict, unsigned int string_hash);
bool exists_byhash(BSONDict dict, unsigned int string_hash);


#define BSONType_null 1
#define BSONType_boolean 2
#define BSONType_integer 3
#define BSONType_string 4
#define BSONType_array 5
#define BSONType_dict 6

/*
Code exemple:

BSONArray l1 = BSONArray();
	l1.insert(new BSONObject(false));
	l1.insert(new BSONObject(42));
	l1.insert(new BSONObject(string("test")));

	BSONDict d1 = BSONDict();
	d1["test1"] = new BSONObject(false);
	d1["test2"] = new BSONObject(42);
	d1["test3"] = new BSONObject(string("test"));
	d1["list"] = new BSONObject(l1);

	BSONObject* d1_o = new BSONObject(d1);
	printf2("%s\n", d1_o->to_string().get());

	string buffer = d1_o->create_structure();
	printf2("Buffer size: %d\n", buffer.length());

	pretty_print(buffer.get(), buffer.length());
	printf2("\n\n");

	printf2("======================\n");
	BSONObject* parsed = new BSONObject();
	parsed->parse(buffer.get());

	printf2("%s\n", parsed->to_string().get());

	string buffer2 = parsed->create_structure();
	printf2("Buffer size: %d\n", buffer2.length());

	pretty_print(buffer2.get(), buffer2.length());
	printf2("\n\n");

	printf2("d1\n");
	delete d1_o;

*/

/*
* Format:
* null -> \x01
* boolean -> \x02\x0X
* integer -> \x03\xXX\xXX\xXX\xXX
* string -> \x04 (size) \xXX\xXX\xXX\xXX (data) hello\x00
* array -> \x05
*	0) (data bool, null, string...)
*	1) (data bool, null, string...)
*	...
*   \x00
* dict -> \x06
*	key1\x00 (data bool, null, string...)
*   key2\x00 (data bool, null, string...)
*   ...
*   \x00
*/



class BSONObject
{
public:
	BSONObject();
	BSONObject(bool boolean);
	BSONObject(int integer);
	BSONObject(const char* str);
	BSONObject(const string &str);
	BSONObject(const BSONArray &array);
	BSONObject(const BSONDict &dict);
	BSONObject(const BSONObject& dict);

	~BSONObject();

	void cleanup();
	string create_structure();
	size_t parse(const char* buffer);

	string to_string();

	bool IsNull();
	bool IsBool();
	bool IsInteger();
	bool IsString();
	bool IsArray();
	bool IsDict();
	unsigned int getType();

	bool AsBoolean();
	int AsInteger();
	const string &AsString();
	const BSONArray &AsArray();
	const BSONDict &AsDict();
private:
	unsigned char type;
	// Values
	bool bool_value = false;
	int integer_value = 0;
	string *string_value = NULL;
	BSONArray *array_value = NULL;
	BSONDict *dict_value = NULL;
};

string uint32_to_string(unsigned int integer);
unsigned int buffer_to_uint32(const char* buffer);

#endif
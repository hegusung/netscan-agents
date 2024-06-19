#pragma once
#ifndef __BSON_HEADER
#define __BSON_HEADER

#include "NoCRT.h"
#include "NoCRT_string.h"
#include "NoCRT_list.h"

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
	d1.set("test1", new BSONObject(false));
	d1.set("test2", new BSONObject(42));
	d1.set("test3", new BSONObject(string("test")));
	d1.set("list", new BSONObject(l1));

	BSONObject* d1_o = new BSONObject(d1);
	printf("%s\n", d1_o->to_string().get());

	string buffer = d1_o->create_structure();
	printf("Buffer size: %d\n", buffer.length());

	pretty_print(buffer.get(), buffer.length());
	printf("\n\n");

	printf("======================\n");
	BSONObject* parsed = new BSONObject();
	parsed->parse(buffer.get());

	printf("%s\n", parsed->to_string().get());

	string buffer2 = parsed->create_structure();
	printf("Buffer size: %d\n", buffer2.length());

	pretty_print(buffer2.get(), buffer2.length());
	printf("\n\n");

	printf("d1\n");
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

class BSONObject;
typedef list<BSONObject*> BSONArray;
class BSONDict;

class BSONObject
{
public:
	BSONObject();
	BSONObject(bool boolean);
	BSONObject(int integer);
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

class BSONKey
{
public:
	BSONKey(string k, BSONObject& o)
	{
		key = k;
		value = new BSONObject(o);
	}
	BSONKey(string k, BSONObject* o)
	{
		key = k;
		value = o;
	}
	~BSONKey()
	{
		delete value;
	}
	string key;
	BSONObject* value;
};

class BSONDict
{
public:
	BSONDict();
	BSONDict(const BSONDict& dict);
	~BSONDict();

	bool exists(string key);
	bool set(string key, BSONObject &object);
	bool set(string key, BSONObject* object);
	bool remove(string key);
	list<BSONKey*> keys;

};

string uint32_to_string(unsigned int integer);
unsigned int buffer_to_uint32(const char* buffer);
void pretty_print(const char* buffer, size_t size);

#endif
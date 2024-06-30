#include "BSON.h"

#include "obfuscation.h"

BSONObject* get_byhash(BSONDict dict, unsigned int str_hash)
{
	BSONDict::iterator l_iterFirst = dict.begin();
	for (; (l_iterFirst != dict.end()); l_iterFirst++)
	{
		unsigned int key_hash = STRING_HASH((*l_iterFirst).first.c_str()); // bson_string_hash((*l_iterFirst).first.c_str(), BSON_HASH_SEED);
		if (key_hash == str_hash)
			return (*l_iterFirst).second;
	}
}

bool exists_byhash(BSONDict dict, unsigned int str_hash)
{
	BSONDict::iterator l_iterFirst = dict.begin();
	for (; (l_iterFirst != dict.end()); l_iterFirst++)
	{
		const char* str = (*l_iterFirst).first.c_str();
		unsigned int key_hash = STRING_HASH((*l_iterFirst).first.c_str());  //bson_string_hash((*l_iterFirst).first.c_str(), BSON_HASH_SEED);
		if (key_hash == str_hash)
			return true;
	}

	return false;
}



BSONObject::BSONObject()
{
	this->type = BSONType_null;
}

BSONObject::BSONObject(bool boolean)
{
	this->type = BSONType_boolean;
	this->bool_value = boolean;
}

BSONObject::BSONObject(int integer)
{
	this->type = BSONType_integer;
	this->integer_value = integer;
}

BSONObject::BSONObject(const char* str)
{
	this->type = BSONType_string;
	this->string_value = new string(string(str));
}

BSONObject::BSONObject(const string &str)
{
	this->type = BSONType_string;
	this->string_value = new string(str);
}

BSONObject::BSONObject(const BSONArray &array)
{
	this->type = BSONType_array;
	this->array_value = new BSONArray(array);	
}

BSONObject::BSONObject(const BSONDict &dict)
{
	this->type = BSONType_dict;
	this->dict_value = new BSONDict(dict);
}

BSONObject::BSONObject(const BSONObject& o)
{
	this->type = o.type;

	if (this->type == BSONType_boolean)
	{
		this->bool_value = o.bool_value;
	}
	else if (this->type == BSONType_integer)
	{
		this->integer_value = o.integer_value;
	}
	else if (this->type == BSONType_string)
	{
		this->string_value = new string(*o.string_value);
	}
	else if (this->type == BSONType_array)
	{
		this->array_value = new BSONArray(*o.array_value);
	}
	else if (this->type == BSONType_dict)
	{
		this->dict_value = new BSONDict(*o.dict_value);
	}
}

BSONObject::~BSONObject()
{
	this->cleanup();
}

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

string BSONObject::create_structure()
{
	size_t size;
	char* data;
	string out;

	if (this->type == BSONType_null)
	{
		size = 1;
		data = (char*)malloc(size);

		data[0] = BSONType_null;

		out = string(data, size);
	}
	else if (this->type == BSONType_boolean)
	{
		size = 1 + 1;
		data = (char*)malloc(size);

		data[0] = BSONType_boolean;
		if (this->bool_value)
			data[1] = 1;
		else
			data[1] = 0;

		out = string(data, size);
	}
	else if (this->type == BSONType_integer)
	{
		size = 1;
		data = (char*)malloc(size);

		data[0] = BSONType_integer;

		out = string(data, size);

		out += uint32_to_string(this->integer_value);
	}
	else if (this->type == BSONType_string)
	{
		size = 1;
		data = (char*)malloc(size);

		data[0] = BSONType_string;

		out = string(data, size);

		out += uint32_to_string(this->string_value->length());
		out += string(this->string_value->get(), this->string_value->length());;
		out += string('\0');
	}
	else if (this->type == BSONType_array)
	{
		size = 1;
		data = (char*)malloc(size);

		data[0] = BSONType_array;

		out = string(data, size);

		for (BSONArray::iterator it = array_value->begin(); it != array_value->end(); ++it) {
			out += (*it)->create_structure();
		}

		out += string('\0');
	}
	else if (this->type == BSONType_dict)
	{
		size = 1;
		data = (char*)malloc(size);

		data[0] = BSONType_dict;

		out = string(data, size);

		for (BSONDict::iterator it = dict_value->begin(); it != dict_value->end(); ++it) {

			out += (*it).first;
			out += string('\0');

			out += (*it).second->create_structure();
		}

		out += string('\0');
	}

	return out;
}

size_t BSONObject::parse(const char* buffer)
{
	if (buffer[0] == BSONType_null)
	{
		this->type = BSONType_null;

		return 1;
	}
	else if (buffer[0] == BSONType_boolean)
	{
		this->type = BSONType_boolean;

		if (buffer[1] == 1)
		{
			this->bool_value = true;
		}
		else
		{
			this->bool_value = false;
		}

		return 2;
	}
	else if (buffer[0] == BSONType_integer)
	{
		this->type = BSONType_integer;

		this->integer_value = buffer_to_uint32(buffer + 1);

		return 5;
	}
	else if (buffer[0] == BSONType_string)
	{
		this->type = BSONType_string;

		this->string_value = new string(buffer + 5, buffer_to_uint32(buffer + 1));

		return 1 + 4 + this->string_value->length() + 1;
	}
	else if (buffer[0] == BSONType_array)
	{
		this->type = BSONType_array;

		size_t offset = 1;

		this->array_value = new BSONArray();

		while ((buffer + offset)[0] != 0)
		{
			BSONObject* obj = new BSONObject();
			offset += obj->parse(buffer + offset);

			this->array_value->insert(obj);
		}

		offset += 1;

		return offset;
	}
	else if (buffer[0] == BSONType_dict)
	{
		this->type = BSONType_dict;

		size_t offset = 1;

		this->dict_value = new BSONDict();

		while ((buffer + offset)[0] != 0)
		{
			string key = string(buffer + offset);

			offset += key.length() + 1;

			BSONObject* obj = new BSONObject();
			offset += obj->parse(buffer + offset);

			this->dict_value->insert(key, obj);
		}

		offset += 1;

		return offset;
	}
	else
	{
		return 0;
	}
}

void BSONObject::cleanup()
{
	this->bool_value = false;
	this->integer_value = 0;
	if (this->string_value != NULL)
	{
		delete this->string_value;
	}
	if (this->array_value != NULL)
	{
		delete this->array_value;
	}
	if (this->dict_value != NULL)
	{
		delete this->dict_value;
	}
}

string BSONObject::to_string()
{
	if (this->type == BSONType_null)
	{
		return "null -> null";
	}
	else if (this->type == BSONType_boolean)
	{
		if (this->bool_value)
		{
			return "boolean -> true";
		}
		else
		{
			return "boolean -> false";
		}
	}
	else if (this->type == BSONType_integer)
	{
		string out = "integer -> ";
		char* int_str = (char*)malloc(10);
		itoa(this->integer_value, int_str, 10);
		
		out += string(int_str);

		free(int_str);

		return out;
	}
	else if (this->type == BSONType_string)
	{
		string out = "string -> ";
		out += string("\"");
		out += *(this->string_value);
		out += string("\"");

		return out;
	}
	else if (this->type == BSONType_array)
	{
		string out = "array -> [";
		for (BSONArray::iterator it = array_value->begin(); it != array_value->end(); ++it) {
			out += (*it)->to_string();
			out += ", ";
		}

		out += "]";
		return out;
	}
	else if (this->type == BSONType_dict)
	{
		string out = "dict -> {";
		for (BSONDict::iterator it = dict_value->begin(); it != dict_value->end(); ++it) {
			out += "\"";
			out += (*it).first;
			out += "\": ";
			out += (*it).second->to_string();
			out += ", ";
		}

		out += "}";
		return out;
	}
}

bool BSONObject::IsNull()
{
	return this->type == BSONType_null;
}

bool BSONObject::IsBool()
{
	return this->type == BSONType_boolean;
}

bool BSONObject::IsInteger()
{
	return this->type == BSONType_integer;
}

bool BSONObject::IsString()
{
	return this->type == BSONType_string;
}

bool BSONObject::IsArray()
{
	return this->type == BSONType_array;
}

bool BSONObject::IsDict()
{
	return this->type == BSONType_dict;
}

unsigned int BSONObject::getType()
{
	return this->type;
}

bool BSONObject::AsBoolean()
{
	return bool_value;
}

int BSONObject::AsInteger()
{
	return integer_value;
}

const string& BSONObject::AsString()
{
	return (*string_value);
}

const BSONArray& BSONObject::AsArray()
{
	return (*array_value);
}

const BSONDict& BSONObject::AsDict()
{
	return (*dict_value);
}


string uint32_to_string(unsigned int integer)
{
	char bytes[4];

	bytes[0] = integer & 0x000000FF;
	bytes[1] = (integer & 0x0000FF00) >> 8;
	bytes[2] = (integer & 0x00FF0000) >> 16;
	bytes[3] = (integer & 0xFF000000) >> 24;

	return string(bytes, 4);
}

unsigned int buffer_to_uint32(const char* buffer)
{
	unsigned int out = 0;

	out += buffer[0];
	out += buffer[1] << 8;
	out += buffer[2] << 16;
	out += buffer[3] << 24;

	return out;
}

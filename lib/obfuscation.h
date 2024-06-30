#pragma once
#ifndef __OBFUSCATION_HEADER
#define __OBFUSCATION_HEADER

/*
* Obfuscate strings and hash strings
* Project : https://github.com/hegusung/netscan-agents
*/

#ifdef __cplusplus
extern "C" {
#endif

// generate a random key (used as initial hash)
/*
#pragma warning( disable : 4307)
constexpr unsigned int RandomCompileTimeSeed(void)
{
	unsigned int value = (unsigned int)(__TIME__[7] * __TIME__[6] * __TIME__[4] * __TIME__[3] * __TIME__[1] * __TIME__[0]);

	return value & 0xffffffff;
};
*/

// Not using __TIME__ because the value changes DURING compile time
constexpr unsigned int g_SEED = 0x12345678;

/*
* Hash strings
*/

// MurmurOAAT_32
constexpr unsigned int string_hash(const char* str, unsigned int h)
{
	// One-byte-at-a-time hash based on Murmur's mix
	// Source: https://github.com/aappleby/smhasher/blob/master/src/Hashes.cpp
	for (; *str; ++str) {
		h ^= *str;
		h *= 0x5bd1e995;
		h ^= h >> 15;
	}
	return h;
}

#define STRING_HASH( STR ) string_hash((const char*) STR, g_SEED)       // Calling MurmurOAAT_32

#define CTIME_API_HASH( API ) constexpr auto API##_hash = string_hash((const char*) #API, g_SEED); // Calling MurmurOAAT_32 at compile time
#define CTIME_STRING_HASH( NAME, STR ) constexpr auto NAME##_hash = string_hash((const char*) STR, g_SEED); // Calling MurmurOAAT_32 at compile time

#ifdef __cplusplus
}
#endif

/*
* Obfuscate Strings
*/

constexpr void cipher(char* data, size_t size, int key)
{
	// Obfuscate with a simple XOR cipher based on key
	for (size_t i = 0; i < size; i++)
	{
		data[i] ^= (char)((key >> ((i % 4) * 8)) & 0xFF);
	}
}

template <size_t N>
class obfuscate_string
{
public:
	constexpr obfuscate_string(const char* data)
	{
		// Copy data
		for (size_t i = 0; i < N; i++)
		{
			m_data[i] = data[i]; // ^ (char)((g_SEED >> ((i % 4) * 8)) & 0xFF);
		}

		// On construction each of the characters in the string is
		// obfuscated with an XOR cipher based on key
		cipher(m_data, N, g_SEED);
	}

	char m_data[N]{};
};

class obfuscated_string
{
public:
	obfuscated_string(const char* data, size_t size, unsigned int seed)
	{
		this->seed = seed;
		this->size = size;
		str = (char*)malloc(size + 1);
		memcpy(str, data, size);
		str[size] = '\0';
	}

	~obfuscated_string()
	{
		memset(str, 0, size);
		free(str);
	}

	char* decrypt()
	{
		cipher(str, size, seed);

		return str;
	}

	char* str;
	size_t size;
	unsigned int seed;
};

#define OBFUSCATE( NAME, STR ) constexpr obfuscate_string<sizeof(STR)> NAME##_obfuscated = obfuscate_string<sizeof(STR)>(STR); \
obfuscated_string NAME = obfuscated_string(NAME##_obfuscated.m_data, sizeof(STR), g_SEED);

#endif
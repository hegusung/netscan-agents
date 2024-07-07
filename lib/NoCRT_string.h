#pragma once
#ifndef __NOCRT_STRING_HEADER
#define __NOCRT_STRING_HEADER

/*
* Helper functions to remove the visual Studio CRT
* Project : https://github.com/hegusung/netscan-agents
*/

#include "NoCRT.h"

class string
{
public:
    static const size_t npos = -1;

    string()
    {
        allocate(1);

        str_size = 0;
        str[0] = 0;
    }

    string(const char character)
    {
        allocate(2);

        this->str_size = 1;
        str[0] = character;
        str[str_size] = 0;
    }

    string(const char* buffer)
    {
        allocate(strlen(buffer));

        str_size = strlen(buffer);
        memcpy(str, buffer, str_size);
        str[str_size] = 0;
    }

    string(const char* buffer, size_t str_size)
    {
        allocate(str_size);

        this->str_size = str_size;
        memcpy(str, buffer, str_size);
        str[str_size] = 0;
    }

    string(const string& buffer)
    {
        allocate(buffer.str_size);

        str_size = buffer.str_size;
        memcpy(str, buffer.str, buffer.str_size);
        str[str_size] = 0;
    }

    string(size_t str_size, char c)
    {
        allocate(str_size);

        this->str_size = str_size;
        memset(str, c, str_size);
        str[str_size] = 0;
    }

    ~string()
    {
        if (str != NULL)
        {
            memset(str, 0, str_size);
            free(str);
            str = NULL;
            str_size = 0;
        }

    }

public:
    string& operator=(const char* buffer)
    {
        if (str != NULL)
        {
            memset(str, 0, str_size);
            free(str);
            str = NULL;
            str_size = 0;
        }

        allocate(strlen(buffer));

        str_size = strlen(buffer);
        memcpy(str, buffer, str_size);
        str[str_size] = 0;

        return *this;
    }

    string& operator=(const string& buffer)
    {
        if (str != NULL)
        {
            memset(str, 0, str_size);
            free(str);
            str = NULL;
            str_size = 0;
        }

        allocate(buffer.str_size);

        str_size = buffer.str_size;
        memcpy(str, buffer.str, str_size);
        str[str_size] = 0;

        return *this;
    }

    string operator+(const char* buffer)
    {
        string out = string(*this);
        out += buffer;

        return out;
    }

    string operator+(const string& buffer)
    {
        string out = string(*this);
        out += buffer;

        return out;
    }

    void operator+=(char buffer)
    {
        allocate(str_size + 1);

        str[str_size] = buffer;
        str[str_size + 1] = '\0';

        str_size += 1;
    }

    void operator+=(const char* buffer)
    {
        allocate(str_size + strlen(buffer));

        memcpy(str + str_size, buffer, strlen(buffer));

        str_size = str_size + strlen(buffer);
        str[str_size] = '\0';
    }

    void operator+=(const string& buffer)
    {
        allocate(str_size + buffer.str_size);

        memcpy(str + str_size, buffer.c_str(), buffer.str_size);

        str_size = str_size + buffer.str_size;
        str[str_size] = '\0';
    }

    bool operator==(const char* buffer) const
    {
        if (str_size != strlen(buffer))
            return false;

        for (int a = 0; a < str_size; ++a)
        {
            if (str[a] != buffer[a])
                return false;
        }

        return true;
    }

    bool operator==(const string& buffer) const
    {
        return operator==(buffer.str);
    }

    bool operator!=(const char* buffer) const
    {
        return !operator==(buffer);
    }

    bool operator!=(const string& buffer) const
    {
        return !operator==(buffer.str);
    }

    char operator[](int index) const
    {
        if (index < 0 || index >= str_size)
            return -1;

        return str[index];
    }


public:
    size_t length() const
    {
        return str_size;
    }

    size_t size() const
    {
        return this->length();
    }

    int compare(const char* cmp_str) const
    {
        return strcmp(str, cmp_str);
    }



    // Function to find the first occurrence of a character
    size_t find(char c, size_t pos = 0) const {
        if (pos >= str_size) {
            return npos;
        }

        for (size_t i = pos; i < str_size; ++i) {
            if (str[i] == c) {
                return i;
            }
        }

        return npos;
    }

    size_t empty() const
    {
        return this->length() == 0;
    }

    // Function to find the last occurrence of a substring
    size_t rfind(const string& substr, size_t pos = string::npos) const {
        if (substr.empty() || this->empty()) return string::npos;

        // If pos is greater than the str_size of the string, search from the end
        if (pos > str_size) pos = str_size;

        // Traverse the main string in reverse starting from 'pos'
        for (size_t i = pos; i >= 0; i--) {

            // Check if substring matches
            if (this->substr(i, substr.size()) == substr) {
                return i;
            }

            if (i == 0)
                break;
        }

        return string::npos;
    }


    // Function to create a substring
    string substr(size_t pos, size_t len = npos) const {
        if (pos > str_size) {
            return string("");
        }

        if (len == npos || pos + len > str_size) {
            len = str_size - pos;
        }

        return string(str + pos, len);
    }

    const char* get() const
    {
        return str;
    }

    const char* c_str() const
    {
        return str;
    }

private:

    void allocate(size_t new_size)
    {
        if (str != NULL && new_size < allocated_size)
            return;

        // Allocate by block of 1024
        allocated_size = ((new_size / 1024) + 1) * 1024;

        char* temp = (char*)malloc(allocated_size + 1);

        if (str != NULL)
        {
            memcpy(temp, str, str_size);

            memset(str, 0, str_size);
            free(str);
        }

        str = temp;
        str[str_size] = '\0';

        return;
    }

    size_t str_size = 0;
    size_t allocated_size;
    char* str = NULL;
};

#endif

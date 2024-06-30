#pragma once

/*
* Helper functions to remove the visual Studio CRT
* Project : https://github.com/hegusung/netscan-agents
*/


#ifndef __NOCRT_STRING_HEADER
#define __NOCRT_STRING_HEADER

#include "NoCRT.h"

class string
{
public:
    string()
    {
        size = 0;
        str = (char*)malloc(1);
        str[0] = 0;
    }

    string(const char character)
    {
        this->size = 1;
        char* new_str = (char*)malloc(size + 1);
        new_str[0] = character;
        new_str[size] = 0;

        str = new_str;
    }

    string(const char* buffer)
    {
        size = strlen(buffer);
        str = (char*)malloc(size + 1);
        memcpy(str, buffer, size);
        str[size] = 0;
    }

    string(const char* buffer, size_t size)
    {
        this->size = size;
        str = (char*)malloc(size + 1);
        memcpy(str, buffer, size);
        str[size] = 0;
    }

    string(const string& buffer)
    {
        size = buffer.size;
        str = (char*)malloc(size + 1);
        memcpy(str, buffer.str, buffer.size);
        str[size] = 0;
    }

    ~string()
    {
        memset(str, 0, size);
        free(str);
    }

public:
    string& operator=(const char* buffer)
    {
        memset(str, 0, size);
        free(str);

        size = strlen(buffer);
        str = (char*)malloc(size + 1);
        memcpy(str, buffer, size);
        str[size] = 0;

        return *this;
    }

    string& operator=(const string& buffer)
    {
        memset(str, 0, size);
        free(str);

        size = buffer.size;
        str = (char*)malloc(size + 1);
        memcpy(str, buffer.str, size);
        str[size] = 0;

        return *this;
    }

    void operator+=(char buffer)
    {
        char* temp = (char*)malloc(size + 2);
        memcpy(temp, str, size);

        temp[size] = buffer;
        temp[size + 1] = '\0';

        memset(str, 0, size);
        free(str);

        size += 1;
        str = temp;
    }

    void operator+=(const char* buffer)
    {
        size_t new_size = size + strlen(buffer);

        char* temp = (char*)malloc(new_size + 1);

        memcpy(temp, str, size);
        memcpy(temp + size, buffer, strlen(buffer));
        temp[new_size] = 0;

        memset(str, 0, size);
        free(str);

        size = new_size;
        str = temp;
    }

    void operator+=(const string& buffer)
    {
        size_t new_size = size + buffer.size;

        char* temp = (char*)malloc(new_size + 1);

        memcpy(temp, str, size);
        memcpy(temp + size, buffer.str, buffer.size);
        temp[new_size] = 0;

        memset(str, 0, size);
        free(str);

        size = new_size;
        str = temp;
    }

    bool operator==(const char* buffer) const
    {
        if (size != strlen(buffer))
            return false;

        for (int a = 0; a < size; ++a)
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
        if (index < 0 || index >= size)
            return -1;

        return str[index];
    }

public:
    size_t length() const
    {
        return size;
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
    size_t size;
    char* str;
};

#endif
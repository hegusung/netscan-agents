#pragma once
#ifndef __NOCRT_WSTRING_HEADER
#define __NOCRT_WSTRING_HEADER

/*
* Helper functions to remove the visual Studio CRT
* Project : https://github.com/hegusung/netscan-agents
*/

#include "NoCRT.h"

class wstring
{
public:
    wstring()
    {
        allocate(1);

        str_size = 0;
        str[0] = 0;
    }

    wstring(const wchar_t character)
    {
        allocate(2);

        this->str_size = 1;
        str[0] = character;
        str[str_size] = 0;
    }

    wstring(const wchar_t* buffer)
    {
        allocate(wcslen(buffer));

        str_size = wcslen(buffer);
        memcpy(str, buffer, str_size * sizeof(wchar_t));
        str[str_size] = 0;
    }

    wstring(const wchar_t* buffer, size_t str_size)
    {
        allocate(str_size);

        this->str_size = str_size;
        memcpy(str, buffer, str_size * sizeof(wchar_t));
        str[str_size] = 0;
    }

    wstring(const wstring& buffer)
    {
        allocate(buffer.str_size);

        str_size = buffer.str_size;
        memcpy(str, buffer.str, buffer.str_size * sizeof(wchar_t));
        str[str_size] = 0;
    }

    wstring(size_t str_size, wchar_t c)
    {
        allocate(str_size);

        for (int i = 0; i < str_size; i++)
            str[i] = c;

        str[str_size] = 0;

        this->str_size = str_size;
    }

    ~wstring()
    {
        if (str != NULL)
        {
            memset(str, 0, str_size * sizeof(wchar_t));
            free(str);
            str = NULL;
            str_size = 0;
        }
    }

public:
    wstring& operator=(const wchar_t* buffer)
    {
        if (str != NULL)
        {
            memset(str, 0, str_size * sizeof(wchar_t));
            free(str);
            str = NULL;
            str_size = 0;
        }

        allocate(wcslen(buffer));

        str_size = wcslen(buffer);
        memcpy(str, buffer, str_size * sizeof(wchar_t));
        str[str_size] = 0;

        return *this;
    }

    wstring& operator=(const wstring& buffer)
    {
        if (str != NULL)
        {
            memset(str, 0, str_size * sizeof(wchar_t));
            free(str);
            str = NULL;
            str_size = 0;
        };

        allocate(buffer.str_size);

        str_size = buffer.str_size;
        memcpy(str, buffer.str, str_size * sizeof(wchar_t));
        str[str_size] = 0;

        return *this;
    }

    wstring operator+(const wchar_t* buffer)
    {
        wstring out = wstring(*this);
        out += buffer;

        return out;
    }

    wstring operator+(const wstring& buffer)
    {
        wstring out = wstring(*this);
        out += buffer;

        return out;
    }

    void operator+=(wchar_t buffer)
    {
        allocate(str_size + 1);

        str[str_size] = buffer;
        str[str_size + 1] = 0;

        str_size += 1;
    }

    void operator+=(const wchar_t* buffer)
    {
        allocate(str_size + wcslen(buffer));

        memcpy(str + str_size, buffer, wcslen(buffer) * sizeof(wchar_t));

        str_size = str_size + wcslen(buffer);
        str[str_size] = '\0';
    }

    void operator+=(const wstring& buffer)
    {
        allocate(str_size + buffer.str_size);

        memcpy(str + str_size, buffer.c_str(), buffer.str_size * sizeof(wchar_t));

        str_size = str_size + buffer.str_size;
        str[str_size] = '\0';
    }

    bool operator==(const wchar_t* buffer) const
    {
        if (str_size != wcslen(buffer))
            return false;

        for (int a = 0; a < str_size; ++a)
        {
            if (str[a] != buffer[a])
                return false;
        }

        return true;
    }

    bool operator==(const wstring& buffer) const
    {
        return operator==(buffer.str);
    }

    bool operator!=(const wchar_t* buffer) const
    {
        return !operator==(buffer);
    }

    bool operator!=(const wstring& buffer) const
    {
        return !operator==(buffer.str);
    }

    wchar_t operator[](int index) const
    {
        if (index < 0 || index >= str_size)
            return -1;

        return str[index];
    }

public:
    void reserve() {}

    void print() 
    {
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), str, str_size, NULL, NULL);
    }

    size_t length() const
    {
        return str_size;
    }

    int compare(wchar_t* cmp_str) const
    {
        return wcscmp(str, cmp_str);
    }

    const wchar_t* get() const
    {
        return str;
    }

    const wchar_t* c_str() const
    {
        return str;
    }

private:

    void allocate(size_t new_str_size)
    {
        if (str != NULL && new_str_size < allocated_str_size)
        {
            return;
        }

        // Allocate by block of 1024
        allocated_str_size = ((new_str_size / 1024) + 1) * 1024;

        wchar_t* temp = (wchar_t*)malloc((allocated_str_size + 1) * sizeof(wchar_t));

        if (str != NULL)
        {
            memcpy(temp, str, str_size * sizeof(wchar_t));
            memset(str, 0, str_size * sizeof(wchar_t));
            free(str);
        }

        str = temp;
        str[str_size] = '\0';

        return;
    }

    size_t str_size = 0;
    size_t allocated_str_size;
    wchar_t* str = NULL; 
};

#endif

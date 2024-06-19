#pragma once
#ifndef COM_NAMEDPIPE_H_INCLUDED
#define COM_NAMEDPIPE_H_INCLUDED

#include <windows.h>
//#include "communication.h"
#include "../lib/NoCRT.h"
#include "../lib/NoCRT_list.h"
#include "../lib/NoCRT_string.h"

#define PIPE_TIMEOUT 5*60*1000
#define PIPE_SIZE 2048

class NamedPipe
{
public:
    NamedPipe(const char* pipe_name);
    ~NamedPipe();
    int initialize();
    int create_named_pipe();
    int close_named_pipe();
    int com_loop();
    // attributes
    char* pipe_path;
    HANDLE pipe_handle;
    bool connected;
    SECURITY_ATTRIBUTES security_attributes;
    SECURITY_DESCRIPTOR security_descriptor;
};

#endif // COM_NAMEDPIPE_H_INCLUDED

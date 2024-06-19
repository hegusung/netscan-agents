#pragma once
#ifndef COMMUNICATION_H_INCLUDED
#define COMMUNICATION_H_INCLUDED

#include "../lib/NoCRT.h"
#include "../lib/NoCRT_list.h"
#include "../lib/NoCRT_string.h"

#include "../lib/worker.h";

#include "com_namedpipe.h"


/*
* C2 Queries:
* - get name
* - get actions
* - set action as retrieved
* - post result
*/
#define GET_NAME 1
#define GET_ACTIONS 2
#define ACTION_RETRIEVED 3
#define POST_RESULT 4

class Action
{
public:
    Action(string module, string function, list<string> args);
private:
    string module;
    string function;
    list<string> args;
};

class Query
{
public:
    Query(DWORD query_type, DWORD query_id, string query_data);
private:
    DWORD query_type;
    DWORD query_id;
    string query_data;
    list<Action>* action_list;
};

class Communication
{
public:
    Communication(void* communication_object);
    ~Communication();
private:
    NamedPipe* com_object;
};

#endif // COMMUNICATION_H_INCLUDED
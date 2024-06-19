#pragma once
#ifndef WORKER_H_INCLUDED
#define WORKER_H_INCLUDED

#include <Windows.h>
#include "../lib/NoCRT.h"
#include "../lib/NoCRT_list.h"
#include "../lib/NoCRT_string.h"
#include "../lib/BSON.h"

class Action
{
public:
	Action();
private:

};

class Worker
{
public:
	Worker();
	void process_buffer(string buffer);
	void start_worker();
	void worker_loop();
private:
	list<Action*> action_list;
};

DWORD WINAPI WorkerThread(LPVOID lpParam);

#endif
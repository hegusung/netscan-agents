#pragma once
#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

#include "../lib/NoCRT.h"
#include "../lib/NoCRT_list.h"
#include "../lib/NoCRT_string.h"

class Agent
{
public:
	Agent(string config);
	void get_name_action();
private:
	string name;
};


#endif
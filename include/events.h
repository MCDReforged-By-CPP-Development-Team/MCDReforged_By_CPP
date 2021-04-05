#pragma once

#include"globaldef.h"
#include"debugprint.h"

#include<thread>
#include<vector>

#define BLOCK_GLOBAL 0
#define BLOCK_CPP_PLUGINS 1
#define BLOCK_PYTHON_PLUGIN 2

using namespace std;

struct MCDREvent {

};
typedef MCDREvent* PMCDREvent;

vector<MCDREvent> EventQueue;

int Thread_DispatchEvent();
int StartDispatchThread();
int GenerateEvent(PMCDREvent event, unsigned int numbers = 1);
int BlockEvent(PMCDREvent event, int block = BLOCK_GLOBAL);
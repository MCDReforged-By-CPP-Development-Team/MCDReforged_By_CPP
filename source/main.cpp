﻿
#include"systemfun.h"
#include"output.h"
#include"cfgfile.h"
Settings set;

int main(int argc, char** argv) {
	WelcomeMessage();
	Initialize();
	RunServer();
	DealWithUserInput();
	return Finalize();
}
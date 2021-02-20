
#include"systemfun.h"
#include"output.h"
#include"cfgfile.h"
#include"processinput.h"
Settings set;

int main(int argc, char** argv) {
	WelcomeMessage();
	Initialize();
	return Finalize();
}
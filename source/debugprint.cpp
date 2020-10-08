#include"debugprint.h"

int stdfuncallconv DebugPrint(const char* outstr) {
	cout << DEBUGPRINTSTR << outstr << '\n';
	fflush(stdout);
	return 0;
}

int stdfuncallconv DebugPrint(string* outstr) {
	cout << DEBUGPRINTSTR << outstr << '\n';
	fflush(stdout);
	return 0;
}

int stdfuncallconv DebugPrint(int outstr) {
	cout << DEBUGPRINTSTR << outstr << '\n';
	fflush(stdout);
	return 0;
}

int stdfuncallconv DebugPrint(double outstr) {
	cout << DEBUGPRINTSTR << outstr << '\n';
	fflush(stdout);
	return 0;
}
#include"debugprint.h"

int stdfuncallconv DebugPrint(const char* outstr) {
#ifdef DEBUG_FUNC_ENABLE
	time_t t = time(0);
	char time[64];
	strftime(time, sizeof(time), "%Y-%m-%d-%H-%M-%S", localtime(&t));
	cout << "[" << time << "]" << DEBUGPRINTSTR << outstr << '\n';
	fflush(stdout);
	return 0;
#else
	return 0;
#endif
}

int stdfuncallconv DebugPrint(string outstr) {
#ifdef DEBUG_FUNC_ENABLE
	time_t t = time(0);
	char time[64];
	strftime(time, sizeof(time), "%Y-%m-%d-%H-%M-%S", localtime(&t));
	cout << "[" << time << "]" << DEBUGPRINTSTR << outstr << '\n';
	fflush(stdout);
	return 0;
#else
	return 0;
#endif
}

int stdfuncallconv DebugPrint(int outstr) {
#ifdef DEBUG_FUNC_ENABLE
	time_t t = time(0);
	char time[64];
	strftime(time, sizeof(time), "%Y-%m-%d-%H-%M-%S", localtime(&t));
	cout << "[" << time << "]" << DEBUGPRINTSTR << outstr << '\n';
	fflush(stdout);
	return 0;
#else
	return 0;
#endif
}

int stdfuncallconv DebugPrint(double outstr) {
#ifdef DEBUG_FUNC_ENABLE
	time_t t = time(0);
	char time[64];
	strftime(time, sizeof(time), "%Y-%m-%d-%H-%M-%S", localtime(&t));
	cout << "[" << time << "]" << DEBUGPRINTSTR << outstr << '\n';
	fflush(stdout);
	return 0;
#else
	return 0;
#endif
}
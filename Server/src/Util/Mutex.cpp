#ifndef _WIN32
	#include "MutexWin32.cpp"
#elif __linux__
	#include "MutexLinux.cpp"
#endif
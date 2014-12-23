#ifdef _WIN32
	#include "MutexWin32.cpp"
#elif __linux__ || __APPLE__
	#include "MutexLinux.cpp"
#endif

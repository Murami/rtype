#ifdef _WIN32
	#include "MutexWin32.hh"
#elif __linux__ || __APPLE__
	#include "MutexLinux.hh"
#endif

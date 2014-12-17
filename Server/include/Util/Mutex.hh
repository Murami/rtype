#ifdef _WIN32
	#include "MutexWin32.hh"
#elif __linux__
	#include "MutexLinux.hh"
#endif

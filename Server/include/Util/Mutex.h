#ifdef _WIN32
	#include "MutexWin32.h"
#elif __linux__
	#include "MutexLinux.h"
#endif
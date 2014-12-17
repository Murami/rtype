#ifdef _WIN32
# include "ThreadWin32.cpp"
#elif __linux__
# include "ThreadLinux.cpp"
#endif

#ifdef _WIN32
# include "ThreadWin32.hpp"
#elif __linux__ || __APPLE__
# include "ThreadLinux.hpp"
#endif

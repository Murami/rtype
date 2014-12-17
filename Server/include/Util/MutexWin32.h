#ifndef UTIL_MUTEX
#define UTIL_MUTEX

#include <windows.h>

namespace Util
{
	class Mutex
	{
	private:
		CRITICAL_SECTION	_section;

	public:
		Mutex();
		~Mutex();

		void	lock();
		bool	trylock();
		void	unlock();
	};
};

#endif /* UTIL_MUTEX */
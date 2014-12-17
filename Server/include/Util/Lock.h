#pragma once

#include "Mutex.h"

namespace Util
{
	class Lock
	{
		Util::Mutex& _mutex;

	public:
		Lock(Util::Mutex& mutex);
		~Lock();
	};
}
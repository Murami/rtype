#include "Util/Thread.hpp"

template<>
DWORD __stdcall launch_thread<void>(LPVOID param)
{
  Thread<void>* thread = reinterpret_cast<Thread<void>*>(param);
  return (thread->run());
}

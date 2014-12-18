#ifdef _WIN32
#include "Util/Thread.hpp"

namespace Util
{
template<>
DWORD __stdcall launch_thread<void>(LPVOID param)
{
  Thread<void>* thread = reinterpret_cast<Thread<void>*>(param);
  return (thread->run());
}
}
#endif

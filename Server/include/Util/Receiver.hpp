#ifndef UTIL_RECEIVER
#define UTIL_RECEIVER

namespace Util
{
  template<class ReceiverT, class Emitter, class Msg>
  class Receiver
  {
  public:
    virtual ~Receiver() {}

    void		dispatch(const Emitter& emitter, const Msg& msg)
    {
      msg.dispatch(emitter, static_cast<ReceiverT&>(*this));
    }
};

#endif /* UTIL_RECEIVER */

#ifndef UTIL_MSG
#define UTIL_MSG

namespace Util
{
  template<class MsgT, class Emitter, class Receiver>
  class Msg
  {
  public:
    Msg();
    virtual ~Msg();

    void	dispatch(const Emitter& emitter, Receiver& receiver)
    {
      receiver.receive(emmiter, static_cast<MsgT&>(*this));
    }
  };
};

#endif /* UTIL_MSG */

#ifndef ACCEPTOR_OBSERVER_HH
# define ACCEPTOR_OBSERVER_HH

namespace Network
{

  class Acceptor;

  class AcceptorObserver
  {
  public:
    virtual void onAccept(Acceptor *) = 0;
  };

} /* namespace Network */

#endif /* ACCEPTOR_OBSERVER_HH */

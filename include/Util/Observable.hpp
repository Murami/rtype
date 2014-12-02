#ifndef UTIL_OBSERVABLE
#define UTIL_OBSERVABLE

#include <list>

namespace Util
{
  template<class T, class MsgT>
  class Observer;

  template<class T, class MsgT = void*>
  class Observable
  {
  private:
    typedef std::list<Observer<T, MsgT>* >	ObserversList;

    ObserversList	_observers;
    bool		_changed;

  public:
    Observable();
    virtual ~Observable();

    void	addObserver(Observer<T, MsgT>& observer);
    void	deleteObserver(Observer<T, MsgT>& observer);

    void	setChanged();
    bool	hasChanged() const;

    void	notifyObservers(const MsgT& msg);
  };
};

#include "Util/Observable.tpp"

#endif /* UTIL_OBSERVABLE */

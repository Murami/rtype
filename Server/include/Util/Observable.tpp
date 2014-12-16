#ifdef UTIL_OBSERVABLE

#ifndef UTIL_OBSERVABLE_TPP
#define UTIL_OBSERVABLE_TPP

#include "Observer.hpp"

namespace Util
{
  template<class T, class MsgT>
  Observable<T, MsgT>::Observable()
  {
  }

  template<class T, class MsgT>
  Observable<T, MsgT>::~Observable()
  {
  }

  template<class T, class MsgT>
  void	Observable<T, MsgT>::addObserver(Observer<T, MsgT>& observer)
  {
    if (_observers.find(&observer) != _observers.end())
      _observers.push_back(&observer);
  }

  template<class T, class MsgT>
  void	Observable<T, MsgT>::deleteObserver(Observer<T, MsgT>& observer)
  {
    _observers.remove(&observer);
  }

  template<class T, class MsgT>
  void	Observable<T, MsgT>::setChanged()
  {
    _changed = true;
  }

  template<class T, class MsgT>
  bool	Observable<T, MsgT>::hasChanged() const
  {
    return (_changed);
  }

  template<class T, class MsgT>
  void	Observable<T, MsgT>::notifyObservers(const MsgT& msg)
  {
    typename ObserversList::iterator	it;

    it = _observers.begin();
    while (it != _observers.end())
      {
	Observer<T, MsgT>& observer = *(*it);

	it++;
	observer.update(*static_cast<T*>(this), msg);
      }
  }
};

#endif /* UTIL_OBSERVABLE_TPP */

#endif /* UTIL_OBSERVABLE */

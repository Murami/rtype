//
//  Observable.h
//  TestSFML
//
//  Created by Charles Fournier on 02/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef TestSFML_GameObservable_h
# define TestSFML_GameObservable_h

# include <set>
# include "IGameObserver.hh"

class GameObservable {
public:

  void	updateSpawn() const
  {
    for (std::set<IGameObserver *>::const_iterator it = _listObservers.begin(); it != _listObservers.end(); it++)
      (*it)->updateSpawnList();
  }
  
  void notify(size_t mask) const
  {
    for (std::set<IGameObserver *>::const_iterator it = _listObservers.begin(); it != _listObservers.end(); it++)
      (*it)->update(mask);
  }
  
  void onExit()
  {
    for (std::set<IGameObserver *>::const_iterator it = _listObservers.begin(); it != _listObservers.end(); it++)
    (*it)->onExit();
  }
  
  void addObserver(IGameObserver *observer)
  {
    _listObservers.insert(observer);
  }
  
  void removeObserver(IGameObserver *observer)
  {
    _listObservers.erase(observer);
  }
  
private:
    std::set<IGameObserver *> _listObservers;

};

#endif

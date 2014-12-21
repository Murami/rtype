//
//  MenuObservable.h
//  TestSFML
//
//  Created by Charles Fournier on 02/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef TestSFML_Observable_h
#define TestSFML_Observable_h

#include <set>
#include "IMenuObserver.hh"

class	MenuObservable
{
public:
    
  void notify(RtypeEvent::eButton idCallback) const
    {
        for (std::set<IMenuObserver *>::const_iterator it = _list_observers.begin(); it != _list_observers.end(); it++)
            (*it)->update(idCallback);
    }
    
    void addObserver(IMenuObserver *observer)
    {
        _list_observers.insert(observer);
    }
    
    void removeObserver(IMenuObserver *observer)
    {
        _list_observers.erase(observer);
    }
    
private:
    std::set<IMenuObserver *> _list_observers;
    
};

#endif

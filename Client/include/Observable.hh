//
//  Observable.h
//  TestSFML
//
//  Created by Charles Fournier on 02/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef TestSFML_Observable_h
#define TestSFML_Observable_h

#include <set>
#include "IObserver.hh"

class	Observable
{
public:
    
  void notify(RtypeEvent::eButton idCallback) const
    {
        for (std::set<IObserver *>::const_iterator it = _list_observers.begin(); it != _list_observers.end(); it++)
            (*it)->update(idCallback);
    }
    
    void addObserver(IObserver *observer)
    {
        _list_observers.insert(observer);
    }
    
    void removeObserver(IObserver *observer)
    {
        _list_observers.erase(observer);
    }
    
private:
    std::set<IObserver *> _list_observers;
    
};

#endif

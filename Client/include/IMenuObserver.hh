//
//  IMenuObserver.h
//  TestSFML
//
//  Created by Charles Fournier on 02/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef TestSFML_IMenuObserver_h
# define TestSFML_IMenuObserver_h

# include "MenuEnum.hh"

class	IMenuObserver {
public:
  virtual void update(RtypeEvent::eButton idCallback) = 0;

 public:
    virtual ~IMenuObserver() {}
};

#endif

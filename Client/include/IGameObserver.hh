//
//  IObserver.h
//  TestSFML
//
//  Created by Charles Fournier on 02/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef TestSFML_IGameObserver_h
# define TestSFML_IGameObserver_h

class IGameObserver {
public:
  virtual void update() = 0;

 public:
    virtual ~IGameObserver() {}
};

#endif
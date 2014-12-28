//
//  AObject.cpp
//  RType
//
//  Created by Charles Fournier on 10/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "AObject.hh"

AObject::AObject()
{ }

AObject::~AObject()
{ }

void AObject::update(const sf::Vector2<float>)
{ }

void AObject::updateAnim()
{ }

void AObject::render(sf::RenderWindow &window)
{
    window.draw(_sprite);
}

sf::Vector2<float>  AObject::getPosition() const
{
    return _sprite.getPosition();
}

void AObject::setPosition(sf::Vector2<float> position)
{
  _sprite.setPosition(position.x - _sprite.getLocalBounds().width / 2, position.y - _sprite.getLocalBounds().height / 2);
}

sf::Vector2<float>	AObject::getSpeed() const
{
  return (_speed);
}

void		AObject::setSpeed(sf::Vector2<float> speed)
{
  _speed = speed;
}

bool&		AObject::networkUpdated()
{
  return (_networkUpdated);
}

void		AObject::playDeathSound() const
{}

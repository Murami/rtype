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
    _sprite.setPosition(position);
}

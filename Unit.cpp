//
// Created by trykr on 12.10.2020.
//

#include "Unit.h"

Unit::Unit(const std::string& texturePath,sf::Vector2f sizeUnit, float mass,
           sf::Vector2u imageCount, float switchTime, float speed, sf::Font* font, sf::Color color)
           : Entity(texturePath, sizeUnit, mass),
           animation(getBody().getTexture()->getSize(), imageCount, switchTime),
           speed(speed)
{
    state = UnitState::idle;
    isFaceRight = true;

    if (!font->loadFromFile("arial.ttf"))
    {
        throw std::runtime_error("Cannot find font"); //Throw exception if cannot find font
    }

    coords.setFont(*font);
    coords.setFillColor(sf::Color::Yellow);
    coords.setCharacterSize(24);
    coords.setStyle(sf::Text::Bold);
}

Unit::~Unit()
{

}

void Unit::idle(float deltaTime)
{
    if (state != UnitState::dead)
    {
        state = UnitState::idle;
        clearMomentum();
    }
}

void Unit::walk(float deltaTime, bool isGoingRight)
{
    if (deltaTime > 1)
        return;
    sf::Vector2f movement(0,0);
    if(isGoingRight)
    {
        isFaceRight = true;
        movement.x += speed * deltaTime;
    }
    else
    {
        isFaceRight = false;
        movement.x -= speed * deltaTime;
    }
    clearMomentum();
    addVectorToMomentum(movement);
    state = UnitState::walking;
}



void Unit::draw(sf::RenderWindow& window, float deltaTime)
{
    coords.setPosition(getBody().getPosition().x, getBody().getPosition().y - 100);
    coords.setString(std::to_string(getBody().getPosition().x) + ' ' + std::to_string(getBody().getPosition().y));
    animation.Update(static_cast<unsigned int>(state) % 9, deltaTime, isFaceRight);
    setTextureRect(animation.getUVRect());
    window.draw(coords);
    drawBody(window);
}

void Unit::setIsFaceRight(bool isFaceRight)
{
    this->isFaceRight = isFaceRight;
}

bool Unit::getIsFaceRight() {
    return isFaceRight;
}


UnitState Unit::getState() {
    return state;
}

void Unit::makeUnitOutOfBounds()
{
    state = UnitState::dead;
    isOutOfBounds = true;
    setPosition(sf::Vector2f(100,100));
}

bool Unit::getIsOutOfBounds() {
    return isOutOfBounds;
}

void Unit::jumpForward()
{
    sf::Vector2f movement;
    if (isFaceRight)
        movement = sf::Vector2f(12, -6);
    else
        movement = sf::Vector2f(-12, -6);
    addVectorToMomentum(movement);
}

void Unit::jumpBackwards()
{
    sf::Vector2f movement;
    if (isFaceRight)
        movement = sf::Vector2f(-6, -12);
    else
        movement = sf::Vector2f(6, -12);
    addVectorToMomentum(movement);
}

sf::Vector2f Unit::open()
{
    return getPosition();
}

bool Unit::getHasKey() {
    return hasKey;
}

bool Unit::giveKey() {
    hasKey = true;
}



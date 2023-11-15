#include "Note.hpp"

Note::Note(float noteSpeed, int i) : shape(sf::Vector2f(WIDTH / 5, 15)), hit(false), speed(noteSpeed), i(i)
{
    shape.setFillColor(sf::Color::Green);
	init(i);
}

void Note::update(float deltaTime) 
{
    shape.move(0, speed * deltaTime);
}

void Note::init(int i)
{
    shape.setPosition((i * WIDTH / 5), 0);
    hit = false;
}

bool Note::isBottom(float bottom) 
{
  	return shape.getPosition().y > bottom;
}

Note::~Note(){}


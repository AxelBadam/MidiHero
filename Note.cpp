#include "Note.hpp"


Note::Note(float noteSpeed, int i) : shape(sf::Vector2f(WIDTH / 5, 10)), hit(false), speed(noteSpeed), i(i)
{
    shape.setFillColor(sf::Color::Green);
	reset(i);
}

void Note::update(float deltaTime) 
{
    shape.move(0, speed * deltaTime);
}

void Note::reset(int i)
{
    shape.setPosition((i * WIDTH / 5), (HEIGHT / 5) - 100); // this pos should probly be at the top
    hit = false;
}

bool Note::isBottom(float bottom) 
{
  	return shape.getPosition().y > bottom;
}

Note::~Note(){}


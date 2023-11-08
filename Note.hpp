#ifndef __NOTE_HPP__
#define __NOTE_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

#define HEIGHT 600
#define WIDTH 800
#define SPEED 416.67f

class Note {
public:
	Note(float noteSpeed, int i);
    ~Note();


	float time;
	float duration;

	void update(float deltaTime);
	void reset(int i);
	bool isBottom(float bottom);
	sf::RectangleShape shape;
    bool 	hit;
    float 	speed;
	int 	i;

private:
    
};

#endif

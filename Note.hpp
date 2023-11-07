#ifndef __NOTE_HPP__
#define __NOTE_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "midifile/include/Binasc.h"
#include "midifile/include/MidiEvent.h"
#include "midifile/include/MidiEventList.h"
#include "midifile/include/MidiFile.h"
#include "midifile/include/MidiMessage.h"
#include "midifile/include/Options.h"
#include <cmath>

#define HEIGHT 600
#define WIDTH 800

class Note {
public:
	Note(float noteSpeed, int i);
    ~Note();

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

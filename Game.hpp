#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Note.hpp"
#include "midifile/include/Binasc.h"
#include "midifile/include/MidiEvent.h"
#include "midifile/include/MidiEventList.h"
#include "midifile/include/MidiFile.h"
#include "midifile/include/MidiMessage.h"
#include "midifile/include/Options.h"
#include <string.h>

#define HEIGHT 600
#define WIDTH 800
#define SPEED 416.67f


class Game {
public:
	Game();
	~Game();
	void gameLoop();
	void init();
	void handleKeyPresses(float hitLineY);
	void convertMidiToNotes(const std::string& midiFilePath);
private:
	int range;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    void processEvents();
	float deltaTime;
	sf::Music music;
	sf::Font font;
	sf::Text scoreText;
	sf::RenderWindow window;
	std::vector<sf::RectangleShape> zones;
	std::vector<Note> notes;
    
	void render();

	//void update(sf::Time deltaTime);
	/*GameStateManager stateManager;
    AssetManager assetManager;
    AudioManager audioManager;
    UIManager uiManager;*/
};

std::vector<sf::RectangleShape> fillZones( sf::RenderWindow &window);
std::vector<Note> fillVector();



// void Note::update(float deltaTime, float currentTime) 
// {
//     // Check if the current time in the song has reached the time for this note to start falling
//     if (!hit && currentTime >= time) 
// 	{
//         // Calculate how far the note should have fallen based on the duration it's been falling
//         float fallDuration = currentTime - time;
//         float fallDistance = speed * fallDuration; // Assuming speed is in pixels per second

//         // Update the position of the note to fall down the screen
//         shape.setPosition(shape.getPosition().x, 0 + fallDistance);

//         // Check if the note has reached the bottom or passed the hit line
//         if (isBottom(HEIGHT - 100)) {
//             // Handle the note if it reaches the bottom without being hit
//             reset(i); // Resets the note or handles it as a miss
//         }
//     }
// }
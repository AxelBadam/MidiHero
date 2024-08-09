#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
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
	void init(char *pathToMp3);
	void analyzeMidi(const std::string& midiFilePath);

private:
	void handleKeyPresses(float hitLineY);
	void getRange(smf::MidiFile &midifile);
	void laneConfig(smf::MidiFile &midifile, int lowestNote);
	void pushNoteToArray(smf::MidiFile &midifile, int lane, int event);
	void render();
	void processEvents();
	int range;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
	float deltaTime;
	sf::Music music;
	sf::Font font;
	sf::Text scoreText;
	sf::RenderWindow window;
	std::vector<sf::RectangleShape> zones;
	std::vector<Note> notes;
	std::vector<sf::RectangleShape> laneOverlays;
    std::vector<float> laneFlashTimers;
    const float flashDuration = 0.1f;
};

std::vector<sf::RectangleShape> fillZones( sf::RenderWindow &window);

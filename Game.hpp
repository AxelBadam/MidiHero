#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Note.hpp"


class Game {
public:
	Game();
	~Game();
	void gameLoop();
	void init();
	void handleKeyPresses(std::vector<Note> &notes, float hitLineY);
private:
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
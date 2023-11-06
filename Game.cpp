#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int score = 0;

Game::Game() {}

Game::~Game() {}

void Game::handleKeyPresses(std::vector<Note> &notes, float hitLineY) 
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && !notes[0].hit) 
	{
        if (std::fabs(notes[0].shape.getPosition().y - hitLineY) < 10) 
		{
            notes[0].hit = true;
            score++;
            notes[0].reset(notes[0].i);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && !notes[0].hit) 
	{
        if (std::fabs(notes[1].shape.getPosition().y - hitLineY) < 10) 
		{
            notes[1].hit = true;
           	score++;
            notes[1].reset(notes[1].i);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && !notes[0].hit) 
	{
        if (std::fabs(notes[2].shape.getPosition().y - hitLineY) < 10) 
		{
            notes[2].hit = true;
            score++;
            notes[2].reset(notes[2].i);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && !notes[0].hit) 
	{
        if (std::fabs(notes[3].shape.getPosition().y - hitLineY) < 10) 
		{
            notes[3].hit = true;
            score++;
            notes[3].reset(notes[3].i);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && !notes[0].hit) 
	{
        if (std::fabs(notes[4].shape.getPosition().y - hitLineY) < 10) 
		{
            notes[4].hit = true;
            score++;
            notes[4].reset(notes[4].i);
        }
    }				
}

std::vector<sf::RectangleShape> fillZones( sf::RenderWindow &window)
{
	std::vector<sf::RectangleShape> zones;
	for (int i = 0; i < 5; ++i)
	{
		zones.emplace_back(sf::Vector2f(window.getSize().x / 5, 5));
		zones.back().setPosition(i * (window.getSize().x / 5), window.getSize().y - 100);
		zones.back().setFillColor(sf::Color(100, 200, 100));
	}
	return zones;
}

std::vector<Note> fillVector()
{
	std::vector<Note> notes;
	notes.emplace_back(416.67f, 0);
	notes.emplace_back(416.67f, 1);
	notes.emplace_back(416.67f, 2);
	notes.emplace_back(416.67f, 3);
	notes.emplace_back(416.67f, 4);
	return notes;
}

void Game::init()
{
	window.create(sf::VideoMode(800, 600), "SFML Rhythm Game");
	zones = fillZones(window);
	notes = fillVector();
	
    if (!music.openFromFile("/Users/atuliara/Desktop/Tengri - Transcendence.mp3"))
        exit(-1);

    if (!font.loadFromFile("/Users/atuliara/Desktop/Teko/Teko-VariableFont_wght.ttf"))
        exit(-1);

    scoreText.setFont(font);
    scoreText.setCharacterSize(24); // in pixels
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, window.getSize().y - 40);

}

void Game::processEvents() 
{
    sf::Event event;
    while (window.pollEvent(event)) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			exit (0);
   		if (event.type == sf::Event::Closed)
              window.close();
    }
    for (auto &note : notes) 
	{
        note.update(deltaTime);
    	if (note.isBottom(window.getSize().y) && !note.hit) 
    	     note.reset(note.i);
   	}
}

void Game::render() 
{
    window.clear();
	for (auto &zone : zones) 
	{
		window.draw(zone); // Draw the zones
	}
	for (auto &note : notes) 
	{
		window.draw(note.shape); // Draw the notes
	}
	scoreText.setString("Score: " + std::to_string(score));
	window.draw(scoreText);
    window.display();
}


void Game::gameLoop()
{
	sf::Clock clock; // Starts the clock
	music.play();
    while (window.isOpen()) 
	{
        deltaTime = clock.restart().asSeconds();
		processEvents();
		handleKeyPresses(notes, window.getSize().y - 100);	
		render();
	}	
}

#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace smf;

int score = 0;

Game::Game() {}

Game::~Game() {}

void Game::handleKeyPresses(float hitLineY)
{
	for (int i = 0; i < notes.size(); i++)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && !notes[i].hit) 
		{
			if (std::fabs(notes[i].shape.getPosition().y - hitLineY) < 10) 
			{
				notes[i].hit = true;
				score++;
				notes[i].~Note();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && !notes[i].hit)
		{
			if (std::fabs(notes[i].shape.getPosition().y - hitLineY) < 10) 
			{
				notes[i].hit = true;
				score++;
				notes[i].~Note();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && !notes[i].hit)
		{
			if (std::fabs(notes[i].shape.getPosition().y - hitLineY) < 10) 
			{
				notes[i].hit = true;
				score++;
				notes[i].~Note();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && !notes[i].hit) 
		{
			if (std::fabs(notes[i].shape.getPosition().y - hitLineY) < 10) 
			{
				notes[i].hit = true;
				score++;
				notes[i].~Note();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && !notes[i].hit)
		{
			if (std::fabs(notes[i].shape.getPosition().y - hitLineY) < 10)
			{
				notes[i].hit = true;
				score++;
				notes[i].~Note();
			}
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

// std::vector<Note> fillVector()
// {
// 	std::vector<Note> notes;
// 	notes.emplace_back(416.67f, 0);
// 	notes.emplace_back(416.67f, 1);
// 	notes.emplace_back(416.67f, 2);
// 	notes.emplace_back(416.67f, 3);
// 	notes.emplace_back(416.67f, 4);
// 	return notes;
// }

void Game::convertMidiToNotes(const string& midiFilePath)
{
    MidiFile midifile;
    midifile.read(midiFilePath);
    midifile.doTimeAnalysis();
    midifile.linkNotePairs();
	float fallTime = (HEIGHT - 100) / SPEED;
	int lowestNote = 127;
	int highestNote = 0;

 	for (int event = 0; event < midifile[1].size(); ++event)
	{
		if (midifile[1][event].isNoteOn())
		{
			int noteNumber = midifile[1][event][1]; // Note number is the second byte
        	if (noteNumber < lowestNote) 
            	lowestNote = noteNumber;
        	if (noteNumber > highestNote) 
            	highestNote = noteNumber;

		}

	}
	range = highestNote - lowestNote;
	int rangeDiv1 = lowestNote + range / 5;
	int rangeDiv2 = lowestNote + ((range / 5) * 2);
	int rangeDiv3 = lowestNote + ((range / 5) * 3);
	int rangeDiv4 = lowestNote + ((range / 5) * 4);
	cout << range << std::endl;

	int lane = 0;
    for (int event = 0; event < midifile[1].size(); ++event) 
	{
		
        if (midifile[1][event].isNoteOn())
		{
			int noteNumber = midifile[1][event][1];
			if (noteNumber > rangeDiv1 && noteNumber < rangeDiv2)
				lane = 1;
			if (noteNumber > rangeDiv2 && noteNumber < rangeDiv3)
				lane = 2;
			if (noteNumber > rangeDiv3 && noteNumber < rangeDiv4)
				lane = 3;
			if (noteNumber > rangeDiv4)
				lane = 4;
			
            Note n(SPEED, lane);
            n.time = midifile[1][event].seconds - 5.9;
            //n.duration = midifile[1][event].getDurationInSeconds();
            notes.push_back(n);
			std::cout << n.time << std::endl;
        }
    }
}

void Game::init()
{
	window.create(sf::VideoMode(800, 600), "SFML Rhythm Game");
	zones = fillZones(window);

	// if (!backgroundTexture.loadFromFile("/Users/atuliara/reorg/BG.png")) {
    //     exit (-1);
    // }
    // backgroundSprite.setTexture(backgroundTexture);
    // backgroundSprite.setScale(
    //     float(window.getSize().x) / backgroundTexture.getSize().x,
    //     float(window.getSize().y) / backgroundTexture.getSize().y
    // );

    if (!music.openFromFile("/Users/atuliara/reorg/Never-Gonna-Give-You-Up-2.mp3"))
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
   		if (event.type == sf::Event::Closed)
              window.close();
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		exit (0);
	
    for (auto &note : notes)
	{
		float currentTime = music.getPlayingOffset().asSeconds();
		if (currentTime >= note.time)
        	note.update(deltaTime);
		
   	}
}

void Game::render() 
{
	float currentTime;
    window.clear();
	//window.draw(backgroundSprite);
	for (auto &zone : zones)
	{
		window.draw(zone);
	}
	for (auto &note : notes)
	{
		currentTime = music.getPlayingOffset().asSeconds();
		if (currentTime >= note.time)
			window.draw(note.shape);
	}
	scoreText.setString("Score: " + std::to_string(score));
	window.draw(scoreText);
    window.display();
}

void Game::gameLoop()
{
	sf::Clock clock;
	music.play();

    while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		processEvents();
		handleKeyPresses(window.getSize().y - 100);	
		render();
	}	
}

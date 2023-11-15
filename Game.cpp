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
	for (int i = 0; i < notes.size();)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && !notes[i].hit) 
		{
			laneOverlays[0].setFillColor(sf::Color(255, 255, 255, 128));
        	laneFlashTimers[0] = flashDuration;
			if (std::fabs(notes[i].shape.getPosition().y - hitLineY) < 10) 
			{
				notes[i].hit = true;
				score++;
				notes.erase(notes.begin() + i);

			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && !notes[i].hit)
		{
			laneOverlays[1].setFillColor(sf::Color(255, 255, 255, 128));
        	laneFlashTimers[1] = flashDuration;
			if (std::fabs(notes[i].shape.getPosition().y - hitLineY) < 10) 
			{
				notes[i].hit = true;
				score++;
				notes.erase(notes.begin() + i);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && !notes[i].hit)
		{
			laneOverlays[2].setFillColor(sf::Color(255, 255, 255, 128));
        	laneFlashTimers[2] = flashDuration;
			if (std::fabs(notes[i].shape.getPosition().y - hitLineY) < 10) 
			{
				notes[i].hit = true;
				score++;
				notes.erase(notes.begin() + i);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && !notes[i].hit) 
		{
			laneOverlays[3].setFillColor(sf::Color(255, 255, 255, 128));
        	laneFlashTimers[3] = flashDuration;
			if (std::fabs(notes[i].shape.getPosition().y - hitLineY) < 10) 
			{
				notes[i].hit = true;
				score++;
				notes.erase(notes.begin() + i);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && !notes[i].hit)
		{
			laneOverlays[4].setFillColor(sf::Color(255, 255, 255, 128));
        	laneFlashTimers[4] = flashDuration;
			if (std::fabs(notes[i].shape.getPosition().y - hitLineY) < 10)
			{
				notes[i].hit = true;
				score++;
				notes.erase(notes.begin() + i);
			}
    	}	
		i++;
	}			
}

std::vector<sf::RectangleShape> fillZones(sf::RenderWindow &window)
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

void Game::pushNoteToArray(MidiFile &midifile, int lane, int event)
{
	float fallTime = 3.7f;

    Note n(SPEED, lane);
    n.time = midifile[1][event].seconds - fallTime;
    notes.push_back(n);
}

void Game::laneConfig(MidiFile &midifile, int lowestNote)
{
	int rangeDiv1 = lowestNote + range / 5;
	int rangeDiv2 = lowestNote + ((range / 5) * 2);
	int rangeDiv3 = lowestNote + ((range / 5) * 3);
	int rangeDiv4 = lowestNote + ((range / 5) * 4);
	int lane = 0;

    for (int event = 0; event < midifile[1].size(); ++event) 
	{	
        if (midifile[1][event].isNoteOn())
		{
			int noteNumber = midifile[1][event][1];
			if (noteNumber > rangeDiv1 && noteNumber < rangeDiv2)
				lane = 1;
			else if (noteNumber > rangeDiv2 && noteNumber < rangeDiv3)
				lane = 2;
			else if (noteNumber > rangeDiv3 && noteNumber < rangeDiv4)
				lane = 3;
			else if (noteNumber > rangeDiv4)
				lane = 4;
			pushNoteToArray(midifile, lane, event);
        }
    }
}

void Game::getRange(MidiFile &midifile)
{
	int lowestNote = 127;
	int highestNote = 0;

 	for (int event = 0; event < midifile[1].size(); ++event)
	{
		if (midifile[1][event].isNoteOn())
		{
			int noteNumber = midifile[1][event][1];
        	if (noteNumber < lowestNote) 
            	lowestNote = noteNumber;
        	if (noteNumber > highestNote) 
            	highestNote = noteNumber;
		}
	}
	range = highestNote - lowestNote;
	laneConfig(midifile, lowestNote);
}

void Game::analyzeMidi(const string& midiFilePath)
{
    MidiFile midifile;
    midifile.read(midiFilePath);
    midifile.doTimeAnalysis();
    midifile.linkNotePairs();
	getRange(midifile);
}

void Game::init(char *pathToMp3)
{
	window.create(sf::VideoMode(800, 600), "MidiHero");
	zones = fillZones(window);

    if (!music.openFromFile(pathToMp3))
        exit(-1);
    if (!font.loadFromFile("./Teko/Teko-VariableFont_wght.ttf"))
        exit(-1);

	for (int i = 0; i < 5; ++i) 
	{
        sf::RectangleShape overlay(sf::Vector2f(WIDTH / 5, HEIGHT));
        overlay.setPosition(i * WIDTH / 5, 0);
        overlay.setFillColor(sf::Color::Transparent);
        laneOverlays.push_back(overlay);
        laneFlashTimers.push_back(0.0f);
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, window.getSize().y - 40);
}

void Game::processEvents() 
{
	float currentTime;
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
		currentTime = music.getPlayingOffset().asSeconds();
		if (currentTime >= note.time)
        	note.update(deltaTime);
   	}
	for (int i = 0; i < laneFlashTimers.size(); ++i) 
	{
        if (laneFlashTimers[i] > 0) 
		{
            laneFlashTimers[i] -= deltaTime;
            if (laneFlashTimers[i] <= 0)
                laneOverlays[i].setFillColor(sf::Color::Transparent);
        }
    }	
}

void Game::render() 
{
	float currentTime;
    window.clear();
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
	for (auto& overlay : laneOverlays) 
	{
        window.draw(overlay);
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
		if (music.getStatus() == sf::SoundSource::Stopped)
			exit (0);
		deltaTime = clock.restart().asSeconds();
		handleKeyPresses(window.getSize().y - 100);	
		processEvents();
		render();
	}	
}

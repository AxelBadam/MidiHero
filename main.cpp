#include "Note.hpp"
#include "Game.hpp"

int main(int argc, char** argv)
{
	Game game;

	if (argc != 3)
	{
		std::cout << "Usage: ./MidiHero <path to midi> <path to mp3>\n";
		exit (1);
	}
	game.analyzeMidi(argv[1]);
	game.init(argv[2]);
	game.gameLoop();
    return 0;
}




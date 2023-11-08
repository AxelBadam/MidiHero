#include "Note.hpp"
#include "Game.hpp"

int main(int argc, char** argv)
{

	Game game;
	game.convertMidiToNotes(argv[1]);
	game.init();
	game.gameLoop();
    return 0;
}




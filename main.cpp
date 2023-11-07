#include "Note.hpp"
#include "Game.hpp"

using namespace std;
using namespace smf;

void processMidi(int argc, char **argv)
{
	Options options;
   	options.process(argc, argv);
   	MidiFile midifile;
   	if (options.getArgCount() == 0) midifile.read(cin);
   	else midifile.read(options.getArg(1));
   	midifile.doTimeAnalysis();
   	midifile.linkNotePairs();

   	int tracks = midifile.getTrackCount();
   	cout << "TPQ: " << midifile.getTicksPerQuarterNote() << endl;
   	if (tracks > 1) cout << "TRACKS: " << tracks << endl;
   	for (int track=0; track<tracks; track++) 
	{
      if (tracks > 1) cout << "\nTrack " << track << endl;
      cout << "Tick\tSeconds\tDur\tMessage" << endl;
      for (int event=0; event<midifile[track].size(); event++) 
	  {
         cout << dec << midifile[track][event].tick;
         cout << '\t' << dec << midifile[track][event].seconds;
         cout << '\t';
         if (midifile[track][event].isNoteOn())
            cout << midifile[track][event].getDurationInSeconds();
         cout << '\t' << hex;
         for (int i=0; i <midifile[track][event].size(); i++)
            cout << (int)midifile[track][event][i] << ' ';
         cout << endl;
      }
   }
}

int main(int argc, char** argv)
{
	processMidi(argc, argv);



	Game game;

	game.init();
	game.gameLoop();
    return 0;
}




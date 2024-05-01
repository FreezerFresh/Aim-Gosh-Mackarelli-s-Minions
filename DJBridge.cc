#include "AudioClip.h"
#include <iostream>
#include <fstream>
#include "Bridges.h"
#include <math.h>

using namespace std;
using namespace bridges;

int main() {
	Bridges bridges = Bridges(749, "JeffiestJeff", "916695726376");
	bridges.setTitle("Music");
	bridges.setDescription("Putting Music In");

	AudioClip Song = AudioClip("SoundFile.mp3");

	bridges.setDataStructure(Song);
	bridges.visualize();

	return 0;
}

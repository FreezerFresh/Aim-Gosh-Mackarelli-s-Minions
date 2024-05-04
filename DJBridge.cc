#include "AudioClip.h"
#include <iostream>
#include <fstream>
#include "Bridges.h"
#include "Color.h"
#include "ColorGrid.h"
#include <math.h>

using namespace std;
using namespace bridges;
/*
AudioClip mixClips(const AudioClip& ac1, const AudioClip& ac2, float duration) {
	if (ac1.getSampleRate() != ac2.getSampleRate()) {
		throw "can't mix audio clips of varying rates";
	}
	int RATE = ac1.getSampleRate();
	int Count = RATE * duration;

	AudioClip acMix = AudioClip(Count, 1, ac1.getSampleBits(), RATE);

	for (int i = 0; i < acMix.getSampleCount(); i++) {
		int samp1 = ac1.getSample(0, i);
		int samp2 = ac1.getSample(0, i);
		acMix.setSample(0, i, (samp1 + samp2) / 2);
	}
	return acMix;
}
*/
int main() {
	Bridges bridges = Bridges(749, "JeffiestJeff", "916695726376");
	bridges.setTitle("Music");
	bridges.setDescription("Putting Music In");

	ColorGrid cg = ColorGrid(1080, 1920);

	Color color(0.5f, 0.5f, 0.5f);
	for (int row = 0; row < cg.getHeight(); row++) {
		for (int col = 0; col < cg.getWidth(); col++) {
			cg.set(row, col, color);
		}
	}

	AudioClip Song = AudioClip("BattleTheme.wav");

	bridges.setDataStructure(Song);
	//bridges.visualize();

	bridges.setDataStructure(cg);
	bridges.visualize();

	return 0;
}

#include "AudioClip.h"
#include <iostream>
#include <fstream>
#include "Bridges.h"
#include "Color.h"
#include "ColorGrid.h"
#include <math.h>

#include <gtest/gtest.h>
// testing by Juvraj Shergill

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

	AudioClip Song = AudioClip("BattleTheme1.wav"); //This is for battle
	AudioClip Song2 = AudioClip("Overworld1.wav"); //This is for overworld

	cout << "Enter 'battle' to play the battle theme or 'overworld' to play the overworld theme" << endl;
	string input;
	cin >> input;

	if (input == "battle") {
		bridges.setDataStructure(Song); //This plays battle
	} else if (input == "overworld") {
		bridges.setDataStructure(Song2); //This plays overworld
	} else {
		cout << "BAD INPUT" << endl;
		return 1;
	}

	bridges.visualize();

	return 0;
}

TEST(BridgesTest, Set_TitleAndDescription) {
    bridges.setTitle("Music");
    bridges.setDescription("Putting Music In");

    EXPECT_EQ("Music", bridges.getTitle());
    EXPECT_EQ("Putting Music In", bridges.getDescription());
}



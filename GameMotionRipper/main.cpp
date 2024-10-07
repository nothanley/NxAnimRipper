// GameMotionRipper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <nxripper.h>
#include <nxripfile.h>

#define ENTRANCE_RIG_OFFSET 0x3344C66C0 // Assumes using character slot XXX (John Cena)
#define MATCH_RIG_OFFSET    0x3344CC020 // Assumes using character slot 100 (The Rock)
#define CAE_RIG_OFFSET      0x3344C2430 // Assumes using character slot XXX (ADR)

int main()
{
	int boneCount  = 90;
	CNXRipper ripper;
	ripper.setRipDuration(30000); // 10 seconds (10000 milliseconds)
	ripper.setTickRate(90);       // frames per second

	if (ripper.linkProcess("WWE 2K14"))
	{
		ripper.setManualTargets(MATCH_RIG_OFFSET, boneCount);
		ripper.run();
		printf("\n[MAIN] Ripper completed with %d frames\n", ripper.frames().size());
	}

	if (!ripper.empty())
	{
		CNXRipFile ripFile;
		ripFile.setFrames(&ripper.frames());
		ripFile.saveToFile("C:/Users/wauke/Desktop/ANIM_FILE_DEV");
	}

	printf("\n[MAIN] Operation completed");
}



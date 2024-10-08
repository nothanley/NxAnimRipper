// GameMotionRipper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <nxgamerip>


void run_debug_ripper()
{
	int boneCount = 140;
	CNXRipper ripper;
	auto& config = ripper.config();

	if (ripper.linkProcess(SVR09))
	{
		config->setRipDuration(30000);           // 10 seconds (10000 milliseconds)
		config->setTickRate(90);                 // frames per second
		config->addTrack(SVR09_CAE_RIG_OFFSET, boneCount);

		ripper.run();
		printf("\n[MAIN] Ripper completed with %d frames\n", ripper.frames().size());
	}

	if (!ripper.empty())
	{
		CNXRipFile ripFile(&ripper);
		ripFile.setFrames(&ripper.frames());
		ripFile.saveToFile("C:/Users/wauke/Desktop/ANIM_FILE_DEV");
	}

	printf("\n[MAIN] Operation completed");
}

void run_preset_grabber()
{
	auto debugLib = CNXRipperLib::fromDevPresets();



}

int main()
{
	//run_debug_ripper();

	run_preset_grabber();

	return 0;
}



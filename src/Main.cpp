#include "Game.h"
#include "Platform/Platform.hpp"
#include <chrono>
using namespace std::chrono;
#include <iostream>
using namespace std;

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "done with this game " << std::endl;
#endif
	// start of time estimation
	auto start = high_resolution_clock::now();

	Game game;
	game.Run();
	// end of time estimation
	auto stop = high_resolution_clock::now();
	//calaulate the dauaration of the program in seconds
	auto duration = duration_cast<seconds>(stop - start);

	cout << "time of the program in seconds " << duration.count() << " :second" << endl;

	return 0;
}

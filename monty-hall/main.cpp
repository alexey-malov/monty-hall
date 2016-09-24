#include <iostream>
#include <random>
#include <chrono>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	mt19937 rndGen(static_cast<unsigned>(chrono::steady_clock::now().time_since_epoch().count()));
	uniform_int_distribution<> distr(0, 2);
	const int NUM_GAMES = 1'000'000;
	int numWins = 0;

	const bool changeDecision = (argc == 2) && (string(argv[1]) == "change");
	for (int i = 0; i < NUM_GAMES; ++i)
	{
		const int prizeDoor = distr(rndGen);
		int choiceDoor = distr(rndGen);
		const int falseDoors[2] = {
			(prizeDoor + 1) % 3,
			(prizeDoor + 2) % 3
		};
		const int openedDoor = (falseDoors[0] == choiceDoor) ? falseDoors[1] : falseDoors[0];
		
		if (changeDecision)
		{
			// выбираем закрытую дверь, отличную от первоначально выбранной
			choiceDoor = ((choiceDoor + 1) % 3 == openedDoor)
				? (choiceDoor + 2) % 3
				: (choiceDoor + 1) % 3;
		}
		if (choiceDoor == prizeDoor)
		{
			++numWins;
		}
	}
	cout << numWins << ", " << ((double)numWins / NUM_GAMES) * 100 << "%" << endl;
}
#include "gameEngine.h"

using namespace std;

/*
* ZADANIA DO ZROBIENIA:
* - CO ZROBIÆ ¯EBY Z PIENIÊDZMI, NP BY SPRAWDZIÆ CZY STAÆ DAN¥ OSOBE BY IŒÆ DO SKLEPU
* I SOBIE KUPIÆ JEDZENIE. 
* -	PROBLEM Z PRZEKAZYWANIEM OBIEKTÓW MIÊDZY PLIKAMI CPP
* 
* 
* Przyda³oby siê zaj¹æ widocznoœci¹ niektórych pól albo metod :D
*/

int main(int argc, char* argv[])
{
	
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	int inter = 1;

	gameEngine nowg;
	cout << "Start" << endl;
	
	nowg.init("Tyty", 640, 480); // <------

	while (nowg.isRunning())
	{
		frameStart = SDL_GetTicks();

		nowg.handleEvent();
		nowg.update();
		if (inter == 5) // standardowo 30 
		{
			nowg.life();
			nowg.getInfo();
			inter = 0;
		}
		nowg.render();
		inter++;

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < frameDelay)
		{
			SDL_Delay(frameDelay - frameTime);
		}
		
	}

	cout << "Koniec" << endl;
	nowg.close(); // <------
	
	return 0;
}
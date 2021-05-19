#include "gameEngine.h"

using namespace std;

/*
* ZADANIA DO ZROBIENIA:
* - CO ZROBI� �EBY Z PIENI�DZMI, NP BY SPRAWDZI� CZY STA� DAN� OSOBE BY I�� DO SKLEPU
* I SOBIE KUPI� JEDZENIE. 
* -	PROBLEM Z PRZEKAZYWANIEM OBIEKT�W MI�DZY PLIKAMI CPP
* 
* 
* Przyda�oby si� zaj�� widoczno�ci� niekt�rych p�l albo metod :D
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
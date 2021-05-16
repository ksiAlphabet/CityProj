#include "gameEngine.h"

using namespace std;

/*
* ZADANIA DO ZROBIENIA:
* - CO ZROBIÆ ¯EBY Z PIENIÊDZMI, NP BY SPRAWDZIÆ CZY STAÆ DAN¥ OSOBE BY IŒÆ DO SKLEPU
* I SOBIE KUPIÆ JEDZENIE. 
* - BIBKA POWITALNA DLA NOWEGO CONTRIBUTORA - SPOKO
*/

int main(int argc, char* argv[])
{
	/*Shop shop(nullptr, 0, 0, 0, 0, 10, 1000, 400);
	House house(nullptr, 0, 0 , 0 ,0 , 10);
	Person man(nullptr, 0, 0, 0, 0, 10, "Wojtek");*/
	
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
	
	//for (int i = 0; i < 1000; i++)
	//{
	//	/*if (man.eating < 3000) {
	//		if (!shop.buyFood(man))
	//			cout << "Cos nie tak, malo kasy: " << man.budget << endl;
	//	}

	//	man.update();

	//	if (i % 100 == 0)
	//	{
	//		cout << endl << "--------------------------------" << endl;
	//		cout << "Sen[" << i << "] : " << man.sleeping << endl;
	//		cout << "Jedzenie[" << i << "] : " << man.eating << endl;
	//		cout << "--------------------------------" << endl << endl;
	//	}



	//	if (i == 600)
	//	{
	//		cout << "Tyle oooo tyle sleepingu: " << man.sleeping << endl;
	//		house.SleepTime(man);
	//	}*/
	//}
	return 0;
}
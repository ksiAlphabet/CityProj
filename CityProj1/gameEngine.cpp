#include "gameEngine.h"
#include "Person.h"
#include "Place.h"
#include <iostream>

Person* man = nullptr;
Shop* shop = nullptr;
House* house = nullptr;
//MyPlace* myplace = nullptr;

ActionPerson* hugary = nullptr;
ActionPerson* slep = nullptr;
ActionPerson* standing = nullptr;



gameObject::~gameObject() 
{ 
	clearObject();
	//SDL_DestroyTexture(mTexture);
}

bool gameEngine::init(std::string title, int width, int height)
{
	this->width = width;
	this->height = height;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "ERROR_INIT: " << SDL_GetError() << std::endl;
		run = false;
	}
	else
	{
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (!window)
		{
			std::cout << "ERROR_CREATE_WINDOW: " << SDL_GetError() << std::endl;
			run = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
			if (!renderer)
			{
				std::cout << "ERROR_CREATE_RENDERER: " << SDL_GetError() << std::endl;
				run = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0x1f, 0x1f, 0x1f, 0xFF);

				if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
					std::cout << "ERROR_INIT_IMG: " << IMG_GetError() << std::endl;
					run = false;
				}
				else
				{
					if (!loadData())
						run = false;

				}
			}
		}
	}
	return run;
}

bool gameEngine::loadData()
{
	man = new (std::nothrow)  Person(renderer, width / 2, height /2, 10, "Jan");
	if (!man) return false;
	if (!man->FromFile("man.png")) return false;

	shop = new (std::nothrow) Shop(renderer, 45, 50, 10, 1000, 1000); // ostatni¹ wartoœæ powinno daæ siê na 4000 albo 5000
	if (!shop) {
		return false;
	}
	if (!shop->FromFile("shop.png")) return false;
	shop->changeSizeOfTexture(2, 2);
	//man->addShop(shop);

	house = new (std::nothrow) House(renderer, width - 220, 70, 10);
	if (!house) {
		return false;
	}
	if (!house->FromFile("house.png")) return false;
	house->changeSizeOfTexture(60, 20, false);

	/*myplace = new (std::nothrow) MyPlace(nullptr, width / 2, height / 2);
	if (!myplace) {
		return false;
	}*/


	int tx, ty;
	shop->getCenter(tx, ty);
	hugary = new (std::nothrow) ActionPerson(shop, tx, ty, 20, "shop");
	if (!hugary) {
		return false;
	}
	hugary->costOfAction = shop->costShop();

	house->getCenter(tx, ty);
	slep = new (std::nothrow) ActionPerson(house, tx, ty, 30, "house");
	if (!slep) {
		return false;
	}

	standing = new (std::nothrow) ActionPerson(nullptr, width / 2, height / 2, 10, "standing");
	if (!standing) {
		return false;
	}

	ActionPerson* actions[3] = { standing, slep, hugary };
	man->addBaseAction(actions);
	return true;
}

void gameEngine::getInfo()
{
	static unsigned i = 0;
	int iter;
	if (man && shop && house)
	{
		system("cls");
		std::cout << std::endl << "--------------------------------" << std::endl;
		std::cout << "Money[" << i << "] : " << man->budget << std::endl;
		std::cout << "Health[" << i << "] : " << man->health << std::endl;
		std::cout << "--------------------------------" << std::endl;
		std::cout << "Sen[" << i << "] : " << man->sleeping << " :  " << man->makeDecisionSleeping << std::endl;
		std::cout << "Jedzenie[" << i << "] : " << man->eating  << " :  " << man->makeDecisionEating << std::endl;
		std::cout << "--------------------------------" << std::endl;
		std::cout << "X[" << i << "] : " << man->x << std::endl;
		std::cout << "Y[" << i << "] : " << man->y << std::endl;
		std::cout << "ooooooooooooooooooooooooooooooooo:  "<< !man->canMove << std::endl;
		std::cout << "Xa[" << i << "] : " << man->xa << std::endl;
		std::cout << "Ya[" << i << "] : " << man->ya << std::endl;
		std::cout << "Mx[" << i << "] : " << man->movingx << std::endl;
		std::cout << "My[" << i << "] : " << man->movingy << std::endl;
		std::cout << "ooooooooooooooooooooooooooooooooo:  " << std::endl;
		std::cout << "DestIter[" << i << "] : "; 
		iter = man->currentTask ? man->currentTask->timeToEnd : 0;
		std::cout<< iter << std::endl;
		std::cout << "CanIMakeNewAction[" << i << "] : " << (man->currentTask == nullptr) << std::endl;
		std::cout << "--------------------------------" << std::endl << std::endl;
		i++;
	}

}

void gameEngine::close()
{
	delete standing;
	delete slep;
	delete hugary;
	/*delete myplace;*/
	delete house;
	delete shop;
	delete man;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();
}

void gameEngine::handleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			run = false;
		}
	}

}

void gameEngine::render()
{
	SDL_RenderClear(renderer);
	man->render();
	shop->render();
	house->render();
	SDL_RenderPresent(renderer);
}

void gameEngine::update()
{
	man->move();
}

void gameEngine::life()
{
	man->update();
	shop->update();
	house->update();
}


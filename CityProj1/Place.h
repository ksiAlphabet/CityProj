#include "gameEngine.h"
#include "Person.h"
#pragma once


/*
* Update() oraz action() bêdzie mo¿na przenieœæ do protected
* poniewa¿ obs³uga tych funkcji bêdzie siê dzia³a popraz klase ActionPerson
*/

class Place : public gameObject
{
	unsigned slots;
	unsigned freeSlots;
public:
	Place(SDL_Renderer* renderer, int x, int y, unsigned slots): gameObject(renderer, x, y), slots(slots), freeSlots(0) {}

	virtual void action(Person& person) = 0; // odpowiada za funkcjonalnoœæ nadego miejsca
	virtual void update() = 0; // odpowiada za update sanu obiektu podczas trwania gry. Np jeœli jakiœ obiekt to magazyn mo¿e zmiêkszyæ albo zmiejszyæ
							   // iloœæ towarów jakie przechowuje 
};


class Shop : public Place
{
	int costs; // cena posi³ku
	unsigned food; // okreœla ile jedzenia siê do staje po danej cenie
public:
	Shop(SDL_Renderer* renderer, int x, int y, unsigned slots, int costs, unsigned food) :
		Place(renderer, x, y, slots), costs(costs), food(food) { }

	virtual void action(Person& person) override;
	virtual void update() override {}
	unsigned costShop() const { return costs; }
};

class House : public Place
{
public:
	House(SDL_Renderer* renderer, int x, int y, unsigned slots) : Place(renderer, x, y, slots) {}

	virtual void action(Person& person) override;
	virtual void update() override {}
};


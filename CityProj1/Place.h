#include "gameEngine.h"
#include "Person.h"
#pragma once


/*
* Update() oraz action() b�dzie mo�na przenie�� do protected
* poniewa� obs�uga tych funkcji b�dzie si� dzia�a popraz klase ActionPerson
*/

class Place : public gameObject
{
	unsigned slots;
	unsigned freeSlots;
public:
	Place(SDL_Renderer* renderer, int x, int y, unsigned slots): gameObject(renderer, x, y), slots(slots), freeSlots(0) {}

	virtual void action(Person& person) = 0; // odpowiada za funkcjonalno�� nadego miejsca
	virtual void update() = 0; // odpowiada za update sanu obiektu podczas trwania gry. Np je�li jaki� obiekt to magazyn mo�e zmi�kszy� albo zmiejszy�
							   // ilo�� towar�w jakie przechowuje 
};


class Shop : public Place
{
	int costs; // cena posi�ku
	unsigned food; // okre�la ile jedzenia si� do staje po danej cenie
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


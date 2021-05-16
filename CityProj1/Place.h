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

	virtual void action(Person& person) = 0;
	/*virtual void decsion(Person& person) const = 0;*/ // chyba nie potrzebna
	virtual void update() = 0;
};


class Shop : public Place
{
	int costs;
	unsigned food;
public:
	Shop(SDL_Renderer* renderer, int x, int y, unsigned slots, int costs, unsigned food) :
		Place(renderer, x, y, slots), costs(costs), food(food) { }

	/*bool buyFood(Person& buyer);*/
	virtual void action(Person& person) override;
	/*virtual void decsion(Person& person) const override {
		person.makeDecisionEating = true;
	}*/
	virtual void update() override {}
	unsigned costShop() const { return costs; }
};

class House : public Place
{
public:
	House(SDL_Renderer* renderer, int x, int y, unsigned slots) : Place(renderer, x, y, slots) {}

	//void SleepTime(Person& sleeper);
	virtual void action(Person& person) override;
	/*virtual void decsion(Person& person) const override {
		person.makeDecisionSleeping = true;
	}*/
	virtual void update() override {}
};

//class MyPlace : public Place
//{
//public:
//	MyPlace(SDL_Renderer* renderer, int x, int y) : Place(renderer, x, y, 0) {}
//	virtual void action(Person& person) override {}
//	virtual void update() override {}
//};


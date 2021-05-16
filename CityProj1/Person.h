#include <iostream>
#include "gameEngine.h"
#include <queue>

#pragma once

class Shop;
class Place;

enum character {
	gluttony = 20,
	diligence = 15,
	lazy = 9,
	avoidsEating = 9,
	sociable = 12,
	unsociable = 9,
	end = 6
};

/*
* Mo¿na zrealizowaæ to jako pochodna gameObject
*/

class ActionPerson
{
	friend class Person;
	friend class gameEngine;

	const char* nazwa;

	Place* place;
	int destination[2] = { 0 };
	const int TIME;
	int timeToEnd = TIME;

	int costOfAction = -1; // nale¿y rozwa¿yæ te dwa modyfikatory w uj¹ciu Akcji wykonywanych przez osobê
	int benefitsOfAction = 0; // poniewa¿ np iœcie do sklepu mo¿e kosztowaæ nas wysi³ek

public:
	ActionPerson(Place* place, int dx, int dy, int timeToEnd, const char* nazwa) : place(place), TIME(timeToEnd), nazwa(nazwa) {
		destination[0] = dx; destination[1] = dy;
	}
	bool reachDestination(int x, int y) const {
		return x == destination[0] && y == destination[1];
	}

	//inline void setCostOfAction(int cost) { costOfAction = cost; }
	//inline void setBenefitsOfAction(int benefit) { benefitsOfAction = benefit; }

	operator const char*() const {
		return nazwa;
	}
};

//class Job
//{
//
//};

class Person : public gameObject
{
public:
	const unsigned MAX = 7050;
	const unsigned MAX_CHARACTER_TRAITS = 2;
	
	// u¿ywamy notacji ¿e 100,11% to unas 10011 za to 99% = 9900
	bool makeDecisionEating = false;
	unsigned eating = MAX;
	unsigned EATING_VALUE = 10;

	bool makeDecisionSleeping = false;
	unsigned sleeping = MAX ; // normalnie najlepiej t¹ wartoœæ pomno¿yæ razy dwa
	unsigned SLPEEPING_VALUE = 10;

	unsigned entertainment = MAX;
	unsigned ENTERTAINMENT_VALUE = 10;

	unsigned tiring = MAX;
	unsigned TIRING_VALUE = 10;

	unsigned meetings = MAX;
	unsigned MEETINGS_VALUE = 10;


	unsigned goods = 4; // jest liczona nie w procentach, opisuje ile dana persona posiada rzeczy
					// niezbêdnych do funkcjonowania
	unsigned GOODS_VALUE = 1; // jest liczona nie w procentach, opisuje ile rzeczy zurzywa dana persona
	unsigned WORK_VALUE = 10; // opisuje stope zwrotu w walucie

	int age;
	std::string name;
	int budget = 10000; // np 1 z³ i 40 groszy zapisujemy 140..; 10,30zl = 1030..
	int health = 1050; // oznacza 9.5 = 95 albo 0.5 = 5
	bool living = true;
	//Job job;

	//Shop* shop;

	// odpowiada za poruszanie siê
	const int baseMowe = 18;
	bool canMove = true;
	int directionx = 0, directiony = 0; // odpowiada za kierunek poruszania góra/dó³, prawo/lewo
	int xa = 0, ya = 0;
	int rx = 0, ry = 0;
	int movingx = 0, movingy =0;

	int destination[2] = { 0 }; // ustawia punkt do którego zmierzamy

	// zmienne przydatne przy czekaniu
	short waiting = 5;
	bool stand_m = true;

	//odpowiada za wykonywane akcje
	//ActionPerson* timeTable = nullptr;
	ActionPerson* baseAction[3]; // standing slep hugary  <----- static ma byæ!!!!!

	std::queue<ActionPerson*> timeTable;
	ActionPerson* currentTask = nullptr;
	
public:
	Person(SDL_Renderer* renderer, int x, int y , const int& age, std::string name);

	~Person() {}
	virtual void update() override;
	//void life();

	//// main vital functions
	void wantSleep();
	void wantEat();
	void getTired();
	void wantMeeting();
	void wantEntertainment();
	void useGoods();

	bool myMoney(int money) { return money <= budget; }
	void pay(int cost) { budget -= cost; }
	bool walking(int x2, int y2);
	void move();
	void death();

	void doSleep(unsigned sleeptime);
	void doEat(unsigned food);

	//void addShop(Shop* s) { shop = s; } // nie wiem jak zaplanowaæ interakcje miêdzy elementami gry

	void addBaseAction(ActionPerson** ab) { for (int i = 0; i < 3; i++) baseAction[i] = ab[i]; }
};


#include "Person.h"
#include "Place.h"

Person::Person(SDL_Renderer* renderer, int x, int y, const int& age, std::string name) :
															gameObject(renderer, x, y),  age(age), name()
{

	srand(time(NULL));
	int a;
	for (unsigned i = 0; i < MAX_CHARACTER_TRAITS; i++)
	{
		a = rand() % character::end;
		switch (a)
		{
		case 0:
			EATING_VALUE = character::gluttony;
		case 1:
			WORK_VALUE = character::diligence;
		case 2:
			WORK_VALUE = character::lazy;
		case 3:
			EATING_VALUE = character::avoidsEating;
		case 4:
			MEETINGS_VALUE = character::sociable;
		case 5:
			MEETINGS_VALUE = character::unsociable;
		default:
			break;
		}
	}
}



void Person::update()
{
	// w przypadku œmierci ca³kowicie od³¹czamy dan¹ postaæ
	if (health == 0) {
		canMove = true;
		death();
		return;
	}

	// zmieniamy podstawowe parametry ¿yciowe
	wantEat();
	wantSleep();

	// ustawienie akcji - przeciwdzia³anie g³ód
	if (!makeDecisionEating && eating < 7000) {
		stand_m = false;
		if(baseAction[2]->costOfAction <= budget)
			if (!currentTask && canMove)
			{
				currentTask = baseAction[2];
				walking(currentTask->destination[0], currentTask->destination[1]);
				makeDecisionEating = true;
			}
			else
			{
				timeTable.push(baseAction[2]);
				makeDecisionEating = true;
			}
	}

	if (living && eating < 100) {
		health -= 2;
	}


	// pobieranie z koleiki akcji do wykonania
	if (!currentTask && !timeTable.empty() && canMove) {
		currentTask = timeTable.front();
		walking(currentTask->destination[0], currentTask->destination[1]);
		timeTable.pop();
	}

	// ustawienie akcji - przeciwdzia³anie sen
	if(!makeDecisionSleeping)
		if (sleeping < 5000) {
			if (!currentTask && canMove) {
				currentTask = baseAction[1];
				walking(baseAction[1]->destination[0], baseAction[1]->destination[1]);
				makeDecisionSleeping = true;
			}
			else
			{
				timeTable.push(baseAction[1]);
				makeDecisionSleeping = true;
			}
		}

	// uruchamianie opcji czekania
	if (!currentTask && !stand_m && !makeDecisionEating && !makeDecisionSleeping && canMove) {
		if (waiting == 0) {
			stand_m = true;
			waiting = 5;
			walking(baseAction[0]->destination[0], baseAction[0]->destination[1]);
		}
		else
			waiting--;
	}

	// uruchamiane g³ównego zadania ka¿dej akcji która znajduje siê w polu wykonywania (currentTask)
	if (currentTask && currentTask->reachDestination(x, y)) {
		if (currentTask->timeToEnd == 0)
		{
			currentTask->place->action(*this);
			currentTask->timeToEnd = currentTask->TIME;
			currentTask = nullptr;
		}
		else
			currentTask->timeToEnd -= 1;
	}
}

void Person::death()
{
	clearObject();
	if (!FromFile("skull.png")) health = -1000;
}



void Person::wantSleep() {
	if (sleeping < SLPEEPING_VALUE)
	{
		sleeping = 0;
	}
	else
		sleeping -= SLPEEPING_VALUE;
}
void Person::wantEat() {
	if (eating < EATING_VALUE)
		eating = 0;
	else
		eating -= EATING_VALUE;
}
void Person::getTired() {
	tiring -= TIRING_VALUE;
}
void Person::wantMeeting() {
	meetings -= MEETINGS_VALUE;
}
void Person::wantEntertainment() {
	entertainment -= ENTERTAINMENT_VALUE;
}
void Person::useGoods() {
	goods -= GOODS_VALUE;
}

void Person::doSleep(unsigned sleeptime) {
	sleeping = sleeptime;
}
void Person::doEat(unsigned food) {
	eating += food;
}



bool Person::walking(int x2, int y2)
{
	 //x1,y1 - to jesteœmy my
	 //x2, y2 - to nasz cel
	int xPath = abs(x - x2), yPath = abs(y - y2);

	if (canMove)
	{
		destination[0] = x2, destination[1] = y2;
		
		directionx = x > x2 ? -1 : 1;
		directiony = y > y2 ? -1 : 1;

		xa = xPath / baseMove; ya = yPath / baseMove;
		rx = xPath - xa * baseMove; ry = yPath - ya * baseMove;

		canMove = false;
		return true;
	}

	return false;
	
}

void Person::move()
{
	int choice;

	if (!canMove)
	{
		if (xa == 0 && ya == 0 && movingx == 0 && movingy == 0)
		{
			if (rx != 0) {
				x += directionx;
				rx -= 1;
			}
			else if (ry != 0) {
				y += directiony;
				ry -= 1;
			}
			else
				canMove = true;

			return;
		}

		if (movingx == 0 && movingy == 0)
		{
			if (xa == 0 && ya != 0)
			{
				movingy = baseMove;
				ya -= 1;
			}
			else if (ya == 0 && xa != 0)
			{
				movingx = baseMove;
				xa -= 1;
			}
			else
			{
				choice = rand() % 2;
				if (choice == 1)
				{
					xa -= 1;
					movingx = baseMove;
				}
				else
				{
					ya -= 1;
					movingy = baseMove;
				}
			}
		}

		if (movingx > 0)
		{
			x += directionx;
			movingx -= 1;
		}
		else if (movingy > 0)
		{
			y += directiony;
			movingy -= 1;
		}

	}
}
#include "Place.h"

void Shop::action(Person& person) // zastêpuje funkcje typu  -->  bool Shop::buyFood(Person& buyer) 
{
	if (!person.myMoney(costs)) {
		person.makeDecisionEating = false;
		std::cout << "za malo kasy" << std::endl;
		return;
	}
	person.pay(costs);
	person.doEat(food);
	person.makeDecisionEating = false;


}


//void House::SleepTime(Person& sleeper) 
//{
//	sleeper.doSleep(10000);
//}

void House::action(Person& person) // zastêpuje funkcje typu  -->  void House::SleepTime(Person& sleeper) 
{
	person.doSleep(7000);
	person.makeDecisionSleeping = false;

}
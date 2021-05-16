#include "Place.h"

void Shop::action(Person& person)
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

//bool Shop::buyFood(Person& buyer) 
//{
//	if (!buyer.myMoney(costs)) {
//		std::cout << "za malo kasy" << std::endl;
//		return false;
//	}
//	buyer.pay(costs);
//	buyer.doEat(food);
//	return true;
//}

//void House::SleepTime(Person& sleeper) 
//{
//	sleeper.doSleep(10000);
//}

void House::action(Person& person) 
{
	person.doSleep(7000);
	person.makeDecisionSleeping = false;

}
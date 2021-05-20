#include "Place.h"

bool ResidentialArea::occupiedNewField(const int fieldIndex, int& xh, int& yh)
{
	if (fieldIndex < 0 || fieldIndex >= 16) return false;
	if (occupiedField[fieldIndex]) return false;

	// tutaj mog¹ dziaæ sie dziiwneeee rzeczy
	xh = (int)fieldForHouse[fieldIndex, 0]; 
	yh = (int)fieldForHouse[fieldIndex, 1];

	return true;
}

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

void House::action(Person& person) // zastêpuje funkcje typu  -->  void House::SleepTime(Person& sleeper) 
{
	person.doSleep(7000);
	person.makeDecisionSleeping = false;

}
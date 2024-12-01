#include "Potion.h"

using namespace std;

Result RevivalPotion::activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field)
{
	self->printPlayerPotion();
	cout << " Revival Potion on " << target->getName() << " ";
	if (target->isAlive())
	{
		cout << " Waste";
		return waste;
	}
	target->heal(0.5);
	return success;
}
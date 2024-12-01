#include "Change.h"

using namespace std;

Result Change::activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field)
{
	if(self->getPlayer() == 1)
	{
		cout << "You send " << target->getName();
		field->setSlimes(make_pair(target, field->getSlimes().second));
	}
	else if (self->getPlayer() == 2)
	{
		cout << "Enemy sends " << target->getName();
		field->setSlimes(make_pair(field->getSlimes().first, target));
	}
	return success;
}
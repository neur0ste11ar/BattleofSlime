#include "Enemy.h"

using namespace std;

Effect EnemySun::selectAct(shared_ptr<Player> player, shared_ptr<Field> field)
{
	Effect effect;
	shared_ptr<Slime> self = field->getSlimes().second;
	shared_ptr<Slime> target = field->getSlimes().first;
	if (self->getName() == "Green" && self->getHealth() < self->getMaxHealth() / 2 && slimes[2]->getHealth() > 0)
	{
		effect = { change, make_shared<Change>("Change", 6), self, slimes[2], nullptr };
		return effect;
	}
	else if (self->getName() == "Pink")
	{
		if (target->getHealth() < target->getMaxHealth() / 3 && (target->isPainted() || target->isSleeping()))
		{
			effect = { skill, self->getSkills()[0], self, nullptr, nullptr };
			return effect;
		}
		else if (!target->isSleeping())
		{
			effect = { skill, self->getSkills()[1], self, nullptr, nullptr };
			return effect;
		}
		else if (target->isSleeping() && !target->isPainted())
		{
			effect = { skill, self->getSkills()[2], self, nullptr, nullptr };
			return effect;
		}
		else if (target->isSleeping() && target->isPainted())
		{
			effect = { skill, self->getSkills()[0], self, nullptr, nullptr };
			return effect;
		}
	}
	else if (self->getName() == "Red")
	{
		if (target->getHealth() < target->getMaxHealth()/ 5 && (target->getElement() == water || target->getElement() == fire))
		{
			effect = { skill, self->getSkills()[0], self, nullptr, nullptr };
			return effect;
		}
		else if (field->getWeather().first == sun)
		{
			effect = { skill, self->getSkills()[1], self, nullptr, nullptr };
			return effect;
		}
		else if (field->getWeather().first != sun)
		{
			effect = { skill, self->getSkills()[2], self, nullptr, nullptr };
			return effect;
		}
	}
	else if (self->getName() == "Green")
	{
		if (self->getHealth() > self->getMaxHealth() / 2 || (self->getHealth() > target->getHealth() && aliveNum() == 1))
		{
			if (target->getElement() == water)
			{
				effect = { skill, self->getSkills()[1], self, nullptr, nullptr };
				return effect;
			}
			else
			{
				effect = { skill, self->getSkills()[0], self, nullptr, nullptr };
				return effect;
			}
		}
		else
		{
			effect = { skill, self->getSkills()[2], self, nullptr, nullptr };
			return effect;
		}
	}
}

void EnemySun::changeSlime(shared_ptr<Field> field)
{
	shared_ptr<Slime> self = field->getSlimes().second;
	shared_ptr<Act> change = make_shared<Change>("Change", 6);
	if (self->getName() == "Pink")
	{
		change->activate(self, slimes[1], field);
	}
	else if (self->getName() == "Green")
	{
		change->activate(self, slimes[2], field);
	}
	else if (self->getName() == "Red")
	{
		change->activate(self, slimes[1], field);
	}
}

Effect EnemyRain::selectAct(shared_ptr<Player> player, shared_ptr<Field> field)
{
	Effect effect;
	shared_ptr<Slime> self = field->getSlimes().second;
	shared_ptr<Slime> target = field->getSlimes().first;
	for (const auto& pair : player->getPotions())
	{
		if (pair.first->getName() == "RevivalPotion" && pair.second > 0 && slimes[1]->getHealth() == 0)
		{
			usePotion(pair.first);
			effect = { potion, pair.first, self, slimes[1], nullptr};
			return effect;
		}
	}
	if (self->getName() == "Green")
	{
		if (target->getElement() == fire && slimes[1]->getHealth() > 0)
		{
			effect = { change, make_shared<Change>("Change", 6), self, slimes[1], nullptr };
			return effect;
		}
		else if (target->getElement() == fire && slimes[1]->getHealth() == 0)
		{
			if (self->getHealth() > self->getMaxHealth() * 2 / 3)
			{
				effect = { skill, self->getSkills()[0], self, nullptr, nullptr };
				return effect;
			}
			else
			{
				effect = { skill, self->getSkills()[2], self, nullptr, nullptr };
				return effect;
			}
		}
		else if (target->getElement() == grass)
		{
			if (self->getHealth() > self->getMaxHealth() / 2)
			{
				effect = { skill, self->getSkills()[0], self, nullptr, nullptr };
				return effect;
			}
			else
			{
				effect = { skill, self->getSkills()[2], self, nullptr, nullptr };
				return effect;
			}
		}
		else
		{
			if (self->getHealth() > self->getMaxHealth() / 2 || target->getHealth() < target->getMaxHealth() / 5)
			{
				effect = { skill, self->getSkills()[1], self, nullptr, nullptr };
				return effect;
			}
			else
			{
				effect = { skill, self->getSkills()[2], self, nullptr, nullptr };
				return effect;
			}
		}
	}
	else if (self->getName() == "Blue")
	{
		if (field->getWeather().first == sun)
		{
			effect = { skill, self->getSkills()[2], self, nullptr, nullptr };
			return effect;
		}
		else if ((field->getWeather().first != sun && target->getElement() == electric) || (field->getWeather().first == rain && target->getElement() == grass))
		{
			if (slimes[0]->getHealth() > 0)
			{
				effect = { change, make_shared<Change>("Change", 6), self, slimes[0], nullptr };
				return effect;
			}
			else
			{
				bool flag = false;
				for (auto iter : player->getSlimes())
				{
					if (iter->getName() == "Yellow" && iter->getHealth() > 0)
					{
						flag = true;
						break;
					}
				}
				if (flag)
				{
					effect = { change, make_shared<Change>("Change", 6), self, slimes[2], nullptr };
					return effect;
				}
				else
				{
					effect = { skill, self->getSkills()[1], self, nullptr, nullptr };
					return effect;
				}
			}
		}
		else if (field->getWeather().first != sun && target->getElement() == water)
		{
			effect = { skill, self->getSkills()[0], self, nullptr, nullptr };
			return effect;
		}
		else
		{
			if (field->getWeather().first == rain)
			{
				effect = { skill, self->getSkills()[1], self, nullptr, nullptr };
				return effect;
			}
			else
			{
				effect = { skill, self->getSkills()[2], self, nullptr, nullptr };
				return effect;
			}
		}
	}
	else if (self->getName() == "Yellow")
	{
		if (target->getHealth() < target->getMaxHealth() / 5)
		{
			effect = { skill, self->getSkills()[0], self, nullptr, nullptr };
			return effect;
		}
		else if (target->getElement() == fire)
		{
			if (slimes[1]->getHealth() > 0)
			{
				effect = { change, make_shared<Change>("Change", 6), self, slimes[1], nullptr };
				return effect;
			}
			else
			{
				effect = { skill, self->getSkills()[1], self, nullptr, nullptr };
				return effect;
			}
		}
		else if (field->getWeather().first == rain && target->getElement() != fire)
		{
			effect = { skill, self->getSkills()[2], self, nullptr, nullptr };
			return effect;
		}
		else if (field->getWeather().first != rain && target->getElement() != fire)
		{
			if (slimes[0]->getHealth() > 0)
			{
				effect = { change, make_shared<Change>("Change", 6), self, slimes[0], nullptr };
				return effect;
			}
			else
			{
				if (target->getElement() == electric || target->getElement() == grass)
				{
					effect = { skill, self->getSkills()[0], self, nullptr, nullptr };
					return effect;
				}
				else
				{
					effect = { skill, self->getSkills()[1], self, nullptr, nullptr };
					return effect;
				}
			}
		}
	}
}

void EnemyRain::changeSlime(shared_ptr<Field> field)
{
	shared_ptr<Slime> self = field->getSlimes().second;
	shared_ptr<Act> change = make_shared<Change>("Change", 6);
	if (self->getName() == "Green")
	{
		if (slimes[1]->getHealth() > 0)
		{
			change->activate(self, slimes[1], field);
		}
		else
		{
			change->activate(self, slimes[2], field);
		}
	}
	else if (self->getName() == "Blue")
	{
		if (slimes[0]->getHealth() > 0)
		{
			change->activate(self, slimes[0], field);
		}
		else
		{
			change->activate(self, slimes[2], field);
		}
	}
	else if (self->getName() == "Yellow")
	{
		if (slimes[1]->getHealth() > 0)
		{
			change->activate(self, slimes[1], field);
		}
		else
		{
			change->activate(self, slimes[0], field);
		}
	}
}
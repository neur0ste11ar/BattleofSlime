#pragma once

#include <string>
#include <memory>
#include "Act.h"
#include "Slime.h"
#include "Field.h"

using namespace std;

class Change :
    public Act
{
    public:
        Change(string name, int priority) : Act(name, priority) {};

        Result activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field) override;
};


#ifndef THROW_H
#define THROW_H

#include "cave.h"
#include "command.h"

#include <string>
#include <iostream>
#include <string>

#include "coin.h"
#include "command.h"
#include "mushroom.h"
#include "rock.h"
#include <iostream>


#include <vector>

#include "thing.h"

using namespace std;

class Throw : public Command
{
public:
    Throw() : Command("throw") {};
    void fire(Cave& c, string userCommand);
};


#endif // THROW_H

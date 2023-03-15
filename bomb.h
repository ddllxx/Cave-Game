#ifndef BOMB_H
#define BOMB_H
#include "thing.h"

class Bomb : public Thing
{
public:
    Bomb() = default;
    string getName() override;
};

#endif // BOMB_H

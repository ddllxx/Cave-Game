#ifndef EXPLODE_H
#define EXPLODE_H

#include "command.h"
class Explode : public Command
{
public:
    Explode();
    void fire(Cave &c, string arguments) override;
};

#endif // EXPLODE_H

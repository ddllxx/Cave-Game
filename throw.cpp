#include "throw.h"
#include "thing.h"

#include <algorithm>
#include "place.h"
#include "thing.h"

#include "blocks.h"
#include "location.h"
#include "tom.h"
#include "bomb.h"

using namespace std;

void Throw::fire(Cave& c, string userCommand)
{
    string s = tail(userCommand);
    string finals = tail(s);
    auto pos = s.find(' ');
    if (pos == string::npos) {
        cerr << "I don't know how to throw " << userCommand << endl;
        return;
    }
    string obj = s.substr(0, pos);

    int newTomX = c.getTom()->getX(),  newTomY = c.getTom()->getY();

    if (finals[0] == 'w')
        newTomX--;
    else if  (finals[0] == 'n')
        newTomY--;
    else if  (finals[0] == 'e')
        newTomX++;
    else if  (finals[0] == 's')
        newTomY++;
    else
    {
        cerr << "tom can't \"" << s << "\"" << endl;
        return;
    }
    Location* loc = c.getMap()[newTomX][newTomY];

    if (newTomX < 0 || newTomY < 0 || newTomX >= c.getHeight() ||newTomY >= c.getHeight())
    {
        cerr << "can't throw into the void" << endl;
        return;
    }
    else if ( c.getMap()[newTomX][newTomY] -> isBlocking() )
    {
        cerr << "something is blocking the way" << endl;
        return;
    }
    else
    {
        if (obj.compare("coin") == 0)
            loc ->add(new Coin());
        else if (obj.compare("mushroom") == 0)
            loc ->add(new Mushroom());
        else if (obj.compare("bomb") == 0)
            loc->add(new Bomb());
        else
            cerr << "I don't know how to place a " << userCommand << endl;
    }
}

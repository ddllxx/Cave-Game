#ifndef LOCATION_H
#define LOCATION_H


#include <vector>

#include "thing.h"

class Location
{
public:
    Location()
    {
        ++count;
    }
    ~Location()
    {
        for (auto t : things)
            delete(t);
        --count;
    }
    void add(Thing *t);
    void remove(Thing *t);
    char show();
    bool isBlocking();
    vector<Thing*>* getThings() { return &things; }
    static int count; // a count of the number of locations allocated/deleted
    Location(const Location &dpc);
    Location& operator = (const Location &dpc);
private:

    vector<Thing*> things;
    void copydp(const Location& dp);
};



#endif // LOCATION_H

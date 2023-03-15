#include "explode.h"
#include "location.h"
#include "thing.h"
#include <queue>
#include <unordered_set>
#include <vector>

using std::queue;
using std::unordered_set;

Explode::Explode() : Command("explode") {}

// get all near the pos, north, south, west, east and current position
vector<pair<int, int>> getAllNear(int width, int height, int posX, int posY)
{
    vector<pair<int, int>> ret;
    for (int i = max(0, posX - 1); i <= min(posX + 1, width - 1); ++i) {
        ret.push_back(make_pair(i, posY));
    }
    for (int j = max(0, posY - 1); j <= min(posY + 1, height - 1); ++j) {
        if (j != posY) {
            ret.push_back(make_pair(posX, j));
        }
    }
    return ret;
}

void Explode::fire(Cave &c, string arguments)
{
    auto map = c.getMap();
    auto posX = c.getTom()->getX();
    auto posY = c.getTom()->getY();
    queue<pair<int, int>> q;    // position we should detect if there is a bomb
    unordered_set<Location *> record;   // postion we have checked
    for (auto p : getAllNear(c.getWidth(), c.getHeight(), posX, posY)) {
        q.push(p);
        record.insert(map[p.first][p.second]);
    }
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        auto loc = map[p.first][p.second];
        bool explode = false;
        // get all things except tom at this location
        vector<Thing *>things;
        for (Thing *thing : *loc->getThings()) {
            if (thing->getName() == "bomb") {
                explode = true;
            }
            if (thing->getName() != "tom") {
                things.push_back(thing);
            }
        }
        // if explde
        if (explode) {
            // move everything except tom
            for (auto t : things) {
                loc->remove(t);
                delete t;
            }
            // get position shoud be check
            for (const auto &pp : getAllNear(c.getWidth(), c.getHeight(), p.first, p.second)) {
                // if the postion has not been checked before
                if (record.count(map[pp.first][pp.second]) == 0) {
                    q.push(pp);
                    record.insert(map[pp.first][pp.second]);
                }
            }
        }
    }
}

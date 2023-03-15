#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
#include <string>

#include "cave.h"
#include "rock.h"
#include "thing.h"
#include "location.h"
#include "move.h"
#include "place.h"
#include "throw.h"
#include "explode.h"

using namespace std;

Cave::Cave(int w, int h) : width(w), height(h) // width and height of the cave
{
//    if (width != 8 || height != 8) // be sure to update Cave::show() if you remove this.
//        throw new logic_error("fixme: Cave needs to be fixed for non-standard sizes.");

    if ( width < 5 || height < 5)
        throw new logic_error("cave too small for tom.");

    map = new Location**[w];

    for (int x = 0; x < w; x++)
    {
        Location** column = new Location*[h];
        map[x] = column;
        for (int y = 0; y < h; y++)
            column[y] = new Location();
    }

    // create some rocks
    for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
            if ( x == 0 || y == 0 || x == w-1 || y == h-1 )
                 map[x][y] -> add( new Rock() );

    tom = new Tom();
    // add tom to the middle of the map
    tom -> setLocation( this, width/2,height/2);
}

void Cave::freeCave()
{
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            delete map[i][j];
        }
        delete []map[i];
    }
    delete []map;
    map = nullptr;
    // tom has been destructed by the location
    tom = nullptr;
}

Cave::~Cave()
{
//    for (int x = 0; x < width; x++)
//        for (int y = 0; y < height; y++)
//                delete (map[x][y]); // fixme: I don't think this deletes all Locations and arrays declared in the constructor...

    //delete[] map; // fixme: ...neither does this.
    freeCave();
}

void Cave::copydp(const Cave &dp){

//    for (int x = 0; x < width; x++) {
//        for (int y = 0; y < height; y++){
//            if(map[x][y] != NULL){
//            delete map[x][y];
//            }
//            else
//                break;
//        }
//    }
    freeCave();
    this->width = dp.width;
    this->height = dp.height;
    map = new Location**[dp.width];
    for (int m = 0; m < dp.width; m++) {
        map[m] = new Location*[dp.height];;
        for (int n = 0; n < dp.height; n++){
            map[m][n] = new Location(*dp.map[m][n]);
        }
     }
    tom = new Tom();
    tom->setLocation(this, dp.tom->getX(), dp.tom->getY());

}

Cave::Cave(const Cave &dp){
//      copydp(dp);
    width = dp.width;
    height = dp.height;
    map = new Location**[width];
    for (int m = 0; m < dp.width; ++m) {
        map[m] = new Location*[height];
        for (int n = 0; n < height; ++n) {
            map[m][n] = new Location(*dp.map[m][n]);
        }
    }
    tom = new Tom();
    tom->setLocation(this, dp.tom->getX(), dp.tom->getY());
}

Cave& Cave::operator = (const Cave &dp){

    if(this != &dp){
        copydp(dp);
    }
    return *this;
}

void Cave::command (string userCommand)
{
    if (Move().triggersOn(userCommand))
        Move().fire(*this, userCommand);
    else if (Place().triggersOn(userCommand))
        Place().fire(*this, userCommand);
    else if (Throw().triggersOn(userCommand))
        Throw().fire(*this, userCommand);
    else if (Explode().triggersOn(userCommand))
        Explode().fire(*this, userCommand);
    else
        cerr << "tom doesn't know how to "+userCommand << endl;;
}

void Cave::show()
{
    vector<Thing*>* thingsWithTom = map[tom -> getX()][tom -> getY()] -> getThings();

    for (int y = 0; y < height; y++)
    { // for all rows
        for (int x = 0; x < width; x++) // for all columns
            cout << map[x][y] -> show(); // output whatever we find there

        cout << "  "; // list the things at this location
        if (y <  (int) thingsWithTom -> size())
            cout << (*thingsWithTom)[y] -> getName();

        cout << endl;
    }

    cout << endl;
}


#include "terrainmap.h"
#include "rand_functions.h"
#include "gamemap.h"
#include "gameobject.h"
#include "qdebug.h"

// Use just testTerrainMap() to produce neat qDebug outputs
// demonstrating the procedural terrain generation.

// Example final code for generating a new GameMap:
// GameMap finalMap = makeLevel(30, 15);
// qDebug().noquote() << finalMap.print();

// Public Function -- Creates a test TerrainMap and outputs the results.
// Basically unit test for TerrainMap.
void testTerrainMap()
{
    TerrainMap testMap = TerrainMap(30, 15);
    testMap.fill('.');
    testMap.scatter('.', 'X', 35.0);
    qDebug().noquote() << testMap.show();

    for (unsigned int i = 0; i < 4; i++)
    {
        testMap.automata('X', '.');
        qDebug().noquote() << testMap.show();
    }

    testMap.scatter('.', 'g', 2.5);
    qDebug().noquote() << testMap.show();

    testMap.scatter('.', '^', 5.0);
    qDebug().noquote() << testMap.show();

    testMap.scatter('.', 't', 1.0);
    qDebug().noquote() << testMap.show();

    testMap.scatter('.', 'G', 1.0);
    qDebug().noquote() << testMap.show();

    testMap.scatter('.', 'H', 1.0);
    qDebug().noquote() << testMap.show();

    GameMap finalMap = testMap.intantiate();
    qDebug().noquote() << finalMap.print();
}

// Public Function -- Makes a level for the game. Returns new TerrainMap.
GameMap makeLevel(unsigned int const width, unsigned int const height)
{
    // Initialize base new TerrainMap.
    TerrainMap newMap = TerrainMap(width, height);
    newMap.fill('.');
    newMap.scatter('.', 'X', 35.0);

    // Execute iterations of cellular automata.
    for (unsigned int i = 0; i < 4; i++)
    {
        newMap.automata('X', '.');
    }

    // Place some other objects.
    newMap.scatter('.', 'g', 2.5);
    newMap.scatter('.', '^', 5.0);

    newMap.scatter('.', 't', 1.0);
    newMap.scatter('.', 'G', 1.0);
    newMap.scatter('.', 'H', 1.0);

    return newMap.intantiate();
}

// Public Method -- Converts a TerrainMap into a GameMap.
// This is a highly specific method. Terrain map stuff must exactly match
// the characters listed in the switch statement below.
GameMap TerrainMap::intantiate()
{
    GameMap newMap = GameMap(_width, _height);

    // For every character in the TerrainMap...
    char test;
    for (unsigned int yy = 0; yy < _height; yy++) {
    for (unsigned int xx = 0; xx < _width; xx++) {
        test = at(xx, yy);

        // Create a new corresponding object in the GameMap.
        switch (test)
        {
        case 'X' :
            newMap.create<Wall>(xx, yy);
            break;

        case 'g' :
            newMap.create<Goblin>(xx, yy);
            break;

        case '^':
            newMap.create<Spike>(xx, yy);
            break;

        case 't':
            newMap.create<Tombstone>(xx, yy);
            break;

        case 'G':
            newMap.create<GoblinBoss>(xx, yy);
            break;

        case 'H':
            newMap.create<HealthPotion>(xx, yy);
            break;
        }

    } } // End double for loop.

    // Return the new GameMap.
    return newMap;
}

// Constructor for TerrainMap class.
// Takes width/height parameters.
TerrainMap::TerrainMap(unsigned int const width, unsigned int const height)
{
    _width = width;
    _height = height;

    _mapList.resize(_width * _height);
    std::fill(_mapList.begin(), _mapList.end(), NULL);
}

// Public Method -- Debug outputs the contents of TerrainMap to a QString.
QString TerrainMap::show()
{
    QString output;
    // Iterate through the entire grid.
    for (unsigned int yy = 0; yy < _height; yy++)
    {
        for (unsigned int xx = 0; xx < _width; xx++)
        {
            output += at(xx, yy);
        }
        output += '\n';
    } // End double for loop.

    return output;
}

// Public Method -- Fills the TerrainMap with a particular value.
void TerrainMap::fill(const char value)
{
    std::fill(_mapList.begin(), _mapList.end(), value);
}

// Public Method -- Returns the character
// At a particular position in the GameMap.
// def is returned with out of bounds call.
char TerrainMap::at(const unsigned int xx, const unsigned int yy, const char def)
{
    // Test if the position is in bounds.
    if (xx >= _width || yy >= _height)
    {
       return def;
    }

    // Return the char at that position.
    return _mapList.at(xx + (yy * _width));
}

// Public Method -- Sets a character in the TerrainMap. (Override).
// Returns true/false based on success.
bool TerrainMap::set(const unsigned int xx, const unsigned int yy, const char value)
{
    // Test if the position is in bounds.
    if (xx >= _width || yy >= _height)
    {
       return false;
    }

    _mapList.at(xx + (yy * _width)) = value;
    return true;
}

// Public Method -- Replaces a particular character in the TerrainMap.
// Accepts a value to replace, returns true/false based on success.
// Key character '@' will replace all characters. (Function same as TerrainMap::set).
bool TerrainMap::replace(const unsigned int xx, const unsigned int yy, const char replace, const char value)
{
    // Test if the position is in bounds.
    if (xx >= _width || yy >= _height)
    {
       return false;
    }

    char test = at(xx, yy);
    if (test == replace || replace == '@')
    {
        set(xx, yy, value);
    }
    return true;
}

// Public Method -- Replaces a particular percentage of values in the TerrainMap.
// Accepts value to replace, new value, and percentage to replace.
// Key character '@' will replace all characters.
void TerrainMap::scatter(const char replace, const char value, const double chance)
{
    // Iterate through the entire grid.
    char test;
    for (unsigned int yy = 0; yy < _height; yy++) {
    for (unsigned int xx = 0; xx < _width; xx++) {

        // Replace chance percent of valid positions.
        test = at(xx, yy);
        if (test == replace || replace == '@')
        {
            if (random(100.0) < chance)
            {
                set(xx, yy, value);
            }
        }
    } } // End double for loop.
}

// Public Method -- Executes cellular automata between two different values.
// def is the value used when the position checked is out of bounds.
// valueA is alive cell value. valueD is dead cell value. Will not touch other cell values.
void TerrainMap::automata(const char valueA, const char valueD)
{
    TerrainMap newMap = TerrainMap(_width, _height);
    newMap.fill('\0');

    const int birthLimit = 4;
    const int deathLimit = 3;

    // Iterate through map, applying changes to the nweMap.
    int count;
    char testA, testB;
    for (unsigned int yy = 0; yy < _height; yy++) {
    for (unsigned int xx = 0; xx < _width; xx++) {

        // For every cell, check if it a living or a dead cell.
        testA = at(xx, yy, valueA);
        if (testA == valueA || testA == valueD)
        {
            newMap.set(xx, yy, testA);

            //qDebug() << "\n";
            //qDebug().noquote() << testA << " = " << "(" << xx << ", " << yy << "): ";

            // Counting the number of surrounding living cells.
            count = 0;
            for (int yyc = -1; yyc <= 1; yyc++) {
            for (int xxc = -1; xxc <= 1; xxc++) {
                if (xxc != 0 || yyc != 0)
                {
                    testB = at(xx + xxc, yy + yyc, valueA);
                    //qDebug() << "looped" << "(" << xxc << "," << yyc << "):" << testB;
                    if (testB == valueA)
                    {
                        count ++;
                    }
                }
            } } // End double for loop.

            //qDebug() << "Count:" <<  count;

            // Killing a living cell.
            if (testA == valueA)
            {
                if (count < deathLimit)
                {
                    newMap.set(xx, yy, valueD);
                }
            }
            // Reviving a dead cell.
            else if (testA == valueD)
            {
                if (count > birthLimit)
                {
                    newMap.set(xx, yy, valueA);
                }
            }
        }
    } } // End double for loop.

    // Copy the changed values of newMap to this map.
    for (unsigned int yy = 0; yy < _height; yy++) {
    for (unsigned int xx = 0; xx < _width; xx++) {
        testA = newMap.at(xx, yy);
        if (testA == valueA || testA == valueD)
        {
            set(xx, yy, testA);
        }
    } }
}













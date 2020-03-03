#include "gamemap.h"
#include "gameobjects.h"
#include "qdebug.h"
#include <iostream>

// Public Constructor -- Creates a GameMap of particular width and height
GameMap::GameMap(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;

    _map[width * height] = nullptr;
    for (unsigned int i = 0; i < width * height; i++)
    {
        _map[i] = nullptr;
    }
}

// Public Method -- Returns pointer to a GameObject at a position in the GameMap
GameObject* GameMap::at(unsigned int xx, unsigned int yy)
{
    return _map[xx + (_width * yy)];
}

// Public Method -- Sets a position within the GameMap
void GameMap::set(GameObject* object, unsigned int xx, unsigned int yy)
{
    // Canceling if it is impossible to set object at that position.
    GameObject* temp = _map[xx + (_width * yy)];
    if (xx >= _width || yy >= _height || temp != nullptr)
    {
        qDebug() << "Deleted " << object->print() << " object within GameMap::set(). [Error]";
        delete object; // Delete the provided object (as it could not be placed). To avoid memory leak.
        return;
    }

    _map[xx + (_width * yy)] = object;
}

// Public Method -- Prints to cout the contents of the GameMap.
// Intended for testing purposes mainly.
void GameMap::print()
{
    // Iterates through the grid, and prints the symbol for each GameObject.
    GameObject* temp;
    for (unsigned int yy = 0; yy < _height; yy++)
    {
        std::cout << '[';
        for (unsigned int xx = 0; xx < _width; xx++)
        {
            temp = at(xx, yy);
            if (temp != nullptr)
            {
                std::cout << temp->print();
            }
            else // Returns a filler space for a place with no GameObject.
            {
                std::cout << ' ';
            }
        }
        std::cout << "]\n";
    }
}

#include "gamemap.h"
#include "gameobject.h"

// Constructor for GameMap class.
// Takes width/height parameters.
GameMap::GameMap(unsigned int width, unsigned int height)
{
    // Resize vector and fill to match size of the GameMap.
    _width = width;
    _height = height;
    _mapList.resize(_width * _height);
    std::fill(_mapList.begin(), _mapList.end(), nullptr);
}

// Destructor for GameMap class.
// Clears all GameObjects (that aren't persistent).
GameMap::~GameMap()
{
    clear();
}

// Public Method -- Returns the GameObject.
// At a particular position in the GameMap.
GameObject* GameMap::at(const unsigned int xx, const unsigned int yy)
{
    // Test if the position is in bounds.
    if (xx >= _width || yy >= _height)
    {
       return nullptr;
    }

    // Return the GameObject at that position.
    return _mapList.at(xx + (yy * _width));
}

// Public Method -- Attempts to delete the GameObject.
// At a particular position in the GameMap.
bool GameMap::destroy(const unsigned int xx, const unsigned int yy)
{
    // Test if there is a GameObject to delete.
    GameObject* object = at(xx, yy);
    if (object == nullptr)
    {
        return false;
    }

    // Delete the GameObject.
    _set(xx, yy, nullptr);

    // Free memory of any non-persistent objects.
    if (!object->_persistent)
    {
        delete object;
    }
    return true;
}

// Public Method -- OVERLOAD of above destroy method.
// This one uses GameObject* directly instead of position.
bool GameMap::destroy(GameObject* object)
{
    if (object == nullptr || object->map() != this)
    {
        return false;
    }
    _set(object->x(), object->y(), nullptr);

    // Free memory of any non-persistent objects.
    if (!object->_persistent)
    {
        delete object;
    }
    return true;
}

// Public Method -- Prints the contents of the GameMap to a QString.
// Intended for testing purposes only. Will not be used to display.
QString GameMap::print()
{
    // Iterates through the grid, and prints the symbol for each GameObject.
    QString text = "";
    GameObject* temp;
    for (unsigned int yy = 0; yy < _height; yy++)
    {
        text += '[';
        for (unsigned int xx = 0; xx < _width; xx++)
        {
            temp = at(xx, yy);
            if (temp != nullptr)
            {
                text += temp->symbol();
            }
            else // Returns a filler space for a place with no GameObject.
            {
                text += ' ';
            }
        }
        text += "]\n";
    }
    return text;
}

// Public Method -- Executes the update event on all GameObjects.
void GameMap::update()
{
    for (unsigned int i = 0; i < _width * _height; i++)
    {
        if (_mapList.at(i) != nullptr)
        {
            _mapList.at(i)->update();
        }
    }
}

// Public Method -- Clears all GameObjects in the GameMap.
// Note: This will include player object also! Be careful.
void GameMap::clear()
{
    for (unsigned int i = 0; i < _width * _height; i++)
    {
        destroy(_mapList.at(i));
    }
}

// Private Method -- Sets a position within the GameMap to a particular value.
// Returns true/false depending on if it is succesfull.
bool GameMap::_set(const unsigned int xx, const unsigned int yy, GameObject* object)
{
    // Test if the position is in bounds.
    if (xx >= _width || yy >= _height)
    {
       return false;
    }

    // Set that position.
    _mapList.at(xx + (yy * _width)) = object;
    return true;
}

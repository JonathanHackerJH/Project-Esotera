#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include <QString>
#include <QPixmap>
#include "gameobject.h"
#include "qdebug.h"

// Class declaration for GameMap.
class GameMap
{
public:
    GameMap(unsigned int width, unsigned int height);
    ~GameMap();

    // Managing contents of the GameMap.
    template<class T> // Template for GameMap::create is defined below.
    GameObject* create(const unsigned int xx, const unsigned int yy, const bool persistent = false);

    GameObject* at(const unsigned int xx, const unsigned int yy);
    bool destroy(const unsigned int xx, const unsigned int yy);
    bool destroy(GameObject* object);

    // Other methods of GameMap.
    QString print();
    QPixmap show();
    void update();
    void clear();

protected:

    // Private methods of GameMap.
    bool _set(const unsigned int xx, const unsigned int yy, GameObject* object);

    // Private members of GameMap.
    unsigned int _width;
    unsigned int _height;
    std::vector<GameObject*> _mapList;

    // Is friend of GameObject;
    friend class GameObject;
};

// Public Method -- Attempts to create a GameObject of provided type.
// Will return the pointer to the newly created GameObject.
// This is in the .h file, to allow the template to work.
// Syntax Example: mainMap.create<Player>(3, 2);
template<class T>
GameObject* GameMap::create(const unsigned int xx, const unsigned int yy, const bool persistent)
{
    // Test if there is a GameObject already, and that position is in bounds.
    if (xx >= _width || yy >= _height)
    {
        qDebug() << "Error with GameMap::create. Attempting to create instance out of bounds.";
        return nullptr;
    }

    GameObject* object = at(xx, yy);
    if (object != nullptr)
    {
        return nullptr;
    }

    // Otherwise create and place the new object.
    GameObject* newObject = new T();
    newObject->_x = xx;
    newObject->_y = yy;
    newObject->_map = this;
    newObject->_persistent = persistent;
    _set(xx, yy, newObject);

    return newObject;
}

#endif // GAMEMAP_H

#include "gameobjects.h"
#include <vector>

#ifndef GAMEMAP_H
#define GAMEMAP_H

// Class declaration for GameMap
class GameMap
{
public:
    GameMap(unsigned int width, unsigned int height);
    GameObject* at(unsigned int xx, unsigned int yy);
    void set(GameObject* object, unsigned int xx, unsigned int yy);
    void print();

private:
    unsigned int _width;
    unsigned int _height;
    GameObject* _map[];
};

#endif // GAMEMAP_H

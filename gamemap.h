#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "gameobjects.h"
#include <vector>

// Class declaration for GameMap
class GameMap
{
public:
    GameMap(unsigned int width, unsigned int height);
    ~GameMap();

    GameObject* at(unsigned int xx, unsigned int yy);
    void set(GameObject* object, unsigned int xx, unsigned int yy);
    void print();
    void update();

private:
    unsigned int _width;
    unsigned int _height;
    std::vector<GameObject*> _map;
};

#endif // GAMEMAP_H

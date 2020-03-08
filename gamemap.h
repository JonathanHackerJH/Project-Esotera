#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QString>
#include <vector>

class GameObject;

// Class declaration for GameMap
class GameMap
{
public:
    GameMap(unsigned int width, unsigned int height);
    ~GameMap();

    GameObject* at(unsigned int xx, unsigned int yy);
    void replace(GameObject* object, unsigned int xx, unsigned int yy);
    QString print();
    void update();

private:
    unsigned int _width;
    unsigned int _height;
    std::vector<GameObject*> _map;

    friend class GameObject;
};

#endif // GAMEMAP_H

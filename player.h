#include "gameobjects.h"

#ifndef PLAYER_H
#define PLAYER_H

// Class declaration for Player
class Player : public Entity
{
public:
    Player();

    void update();
    void collide(GameObject* other);
};

#endif // PLAYER_H

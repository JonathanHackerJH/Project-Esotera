#ifndef PLAYER_H
#define PLAYER_H

#include "gameobjects.h"

// Class declaration for Player
class Player : public Entity
{
public:
    Player();

    void update();
    void collide(GameObject* other);

protected:
    double* _damage = new double(1.0);
};

#endif // PLAYER_H

#ifndef ENEMIES_H
#define ENEMIES_H

#include "gameobjects.h"

// Class declaration for Enemy
class Goblin : public Enemy //Number One
{
public:
    Goblin();

    void update();
};

#endif // ENEMIES_H

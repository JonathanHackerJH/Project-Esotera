#include "enemies.h"
#include "qdebug.h"

// Public Constructor
Goblin::Goblin()
{
    _name = "Goblin";
    _symbol = 'G';

    _health = 2.0;
    _damage = 1.0;
}

// Public Method -- Runs the update event on Goblin
void Goblin::update()
{
    //Move towards the player.
}

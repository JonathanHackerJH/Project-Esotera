#include "player.h"

// Public Constructor
Player::Player()
{
    _name = "Player";
    _type = "player";
    _symbol = 'A';
}

// Public Method -- Runs update event.
void Player::update()
{
    //Movement? Status effects probably.
}

// Public Method -- Runs collide event.
void Player::collide(GameObject* other)
{
    if (other->type() == "enemy")
    {
        other->takeDamage(*_damage);
    }
}

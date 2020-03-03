#include "player.h"

// Public Constructor
Player::Player()
{
    _name = "Player";
    _type = "enemy";
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

}

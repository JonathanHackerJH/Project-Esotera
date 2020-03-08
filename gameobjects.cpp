#include "gameobjects.h"
#include "gamemap.h"
#include "qdebug.h"

//Constructor for GameObject ------------------------------------ Game Object
GameObject::GameObject()
{

}

// Destructor for GameObject
GameObject::~GameObject()
{
    destroy();
}

// Public Method -- Runs destroy event for GameObject
void GameObject::destroy()
{

}

// Public Method -- Runs update event for GameObject
void GameObject::update()
{

}

// Public Method -- Returns print symbol (for debugging purposes)
char GameObject::print()
{
    return _symbol;
}

// Public Method -- Runs the move function for GameObject
void GameObject::move(const int xoff, const int yoff)
{
    // Get the GameObject at the position it attempts to move to.
    unsigned int gox = xx() + xoff;
    unsigned int goy = yy() + yoff;

    // Cancel if the target position is out of bounds.
    if (gox >= _map->_width || goy >= _map->_height)
    {
        return;
    }
    GameObject* other = _map->at(gox, goy);

    // Execute mutual collision events.
    if (other != nullptr)
    {
        collide(other);
    }
    if (other != nullptr)
    {
        other->collide(this);
    }
    else
    {
        // If there is no object, move this object to that position.
        _map->replace(nullptr, xx(), yy());
        _map->replace(this, gox, goy);
    }
}

//GameObject Getters/Setters
QString GameObject::type() const
{
    return _type;
}
unsigned int GameObject::xx() const
{
    return _x;
}
unsigned int GameObject::yy() const
{
    return _y;
}

// Constructor for Entity ------------------------------------ Entity
Entity::Entity()
{
    _name = "Generic Entity";
    _type = "untyped";
    _health = 1.0;
}

// Public Method -- Causes the entity to take damage
void Entity::takeDamage(const double amount)
{
    _health -= amount;
    if (_health <= 0.0)
    {
        // Destroy if health is reduced to zero
        destroy();
    }
}

// Entity Getters/Setters
double Entity::health()
{
    return _health;
}

// Constructor for Enemy ----------------------------------------------- Enemy
Enemy::Enemy()
{
    _name = "Generic Enemy";
    _type = "enemy";
}

// Public Method -- Runs the collide event with Enemy
void Enemy::collide(GameObject* other)
{
    if (other == nullptr) { return; }

    // Deal damage to the player
    if (other->type() == "player")
    {
        other->takeDamage(_damage);
    }
}



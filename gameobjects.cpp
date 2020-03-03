#include "gameobjects.h"
#include "gamemap.h"

//Constructor for GameObject ------------------------------------ Game Object
GameObject::GameObject()
{

}

// Destructor for GameObject
GameObject::~GameObject()
{

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
    //GameObject* other = mainMap.at(gox, goy);

    GameObject* other = nullptr;

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
        //mainMap.set(this, gox, goy);
        //mainMap.set(nullptr, xx(), yy());
        _x = gox;
        _y = goy;
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
}

// Destructor for Entity
Entity::~Entity()
{
    delete _health;
}

// Public Method -- Causes the entity to take damage
void Entity::takeDamage(const double amount)
{
    *_health -= amount;
    if (*_health <= 0.0)
    {
        // Destroy if health is reduced to zero
        destroy();
    }
}

// Entity Getters/Setters
double* Entity::health()
{
    return _health;
}

// Constructor for Enemy ----------------------------------------------- Enemy
Enemy::Enemy()
{
    _name = "Generic Enemy";
    _type = "enemy";
}

// Destructor for Enemy
Enemy::~Enemy()
{
    delete _damage;
}

// Public Method -- Runs the collide event with Enemy
void Enemy::collide(GameObject* other)
{
    if (other == nullptr) { return; }

    // Deal damage to the player
    if (other->type() == "player")
    {
        other->takeDamage(*_damage);
    }
}



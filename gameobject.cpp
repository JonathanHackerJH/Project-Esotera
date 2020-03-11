#include "gameobject.h"
#include "gamemap.h"

// Constructor for GameObject class.
GameObject::GameObject()
{
    _name = "Undefined GameObject";
    _type = "undefined";
    _symbol = '!';
}
GameObject::~GameObject() { }

// Public Method -- Moves the GameObject in the map.
// Returns true/false based on if it successfully moved.
bool GameObject::move(const int xoff, const int yoff)
{
    // Calculate the target move position based on current position.
    unsigned int gox = x() + xoff;
    unsigned int goy = y() + yoff;

    // Cancel if the target is out of bounds.
    if (gox >= map()->_width || goy >= map()->_height)
    {
        return false;
    }

    // Execute collision self with other.
    GameObject* other = map()->at(gox, goy);
    if (other != nullptr)
    {
        collide(other);
    }

    // Execute collision other with self.
    other = map()->at(gox, goy);
    if (other != nullptr)
    {
        other->collide(this);
    }

    // Finally, if the space is free, move the object to the new position.
    other = map()->at(gox, goy);
    if (other == nullptr)
    {
        // Using _set (private method) overrides all values.
        map()->_set(x(), y(), nullptr);
        map()->_set(gox, goy, this);
        _x = gox;
        _y = goy;
        return true;
    }
    return false;
}

// Virtual Public Methods -- These are not defined for GameObject.
// They are left empty here so that children objects may call them.
void GameObject::destroy() { }
void GameObject::update() { }
void GameObject::collide(GameObject*) { }
void GameObject::takeDamage(double) { }
double GameObject::health() const { return 0.0; }

// GameObject Getters/Setters.
QString GameObject::name() const
{
    return _name;
}
QString GameObject::type() const
{
    return _type;
}
char GameObject::symbol() const
{
    return _symbol;
}
unsigned int GameObject::x() const
{
    return _x;
}
unsigned int GameObject::y() const
{
    return _y;
}
GameMap* GameObject::map() const
{
    return _map;
}

// --------------------------------------------------- Spike

// Constructor for Spike class.
Spike::Spike()
{
    _name = "Hidden Spike";
    _type = "spike_trap";
    _symbol = '^';

    _damage = 1.0;
}

// Collision event for Spike Trap.
void Spike::collide(GameObject* other)
{
    if (other->type() == "enemy")
    {
        qDebug() << other->name() << "was stabbed!";

        other->takeDamage(_damage);
        destroy();
        map()->destroy(this);
    }
    else if (other->type() == "player")
    {
        qDebug() << "You got stabbed by a hidden spike!";

        other->takeDamage(_damage);
        destroy();
        map()->destroy(this);
    }
}

// --------------------------------------------------- Entity

// Constructor for Entity class.
Entity::Entity()
{
    _name = "Undefined Entity";
    _type = "undefined";
    _symbol = '!';
}

// Public Method -- Causes the Entity to take damage.
// Will be destroyed if _health is reduced to zero.
void Entity::takeDamage(double amount)
{
    _health -= amount;
    if (_health <= 0.0)
    {
        destroy();
        map()->destroy(this);
    }
}

// Entity Getters/Setters.
double Entity::health() const
{
    return _health;
}

// --------------------------------------------------- Enemy

// Constructor for Enemy class.
Enemy::Enemy()
{
    _name = "Enemy";
    _type = "enemy";
    _symbol = '!';
}

// Public Method -- collide event for Enemy.
// This deals damage to the player, primarily.
void Enemy::collide(GameObject* other)
{
    if (other->type() == "player")
    {
        qDebug() << _name << "deals" << _damage << "damage to you.";
        other->takeDamage(_damage);
    }
}

// Public Method -- Enemy destroy event.
// Display death message, primarily.
void Enemy::destroy()
{
    qDebug() << _name << "was slain.";
    // Also loot drop, XP gain, etcetera.
}

// --------------------------------------------------- Goblin

// Constructor for Goblin Enemy class.
Goblin::Goblin()
{
    _name = "Goblin";
    _symbol = 'G';

    _health = 2.0;
    _damage = 1.0;
}

// --------------------------------------------------- Player

// Constructor for Player class.
Player::Player()
{
    _name = "Player";
    _type = "player";
    _symbol = 'A';

    _health = 10.0;
    _damage = 1.0;
}

// Public Method -- collide event for Player.
void Player::collide(GameObject* other)
{
    // Deal damage to enemies with the Player's attack.
    if (other->type() == "enemy")
    {
        qDebug() << "You attacked" << other->name() << "for" << _damage << "damage!";
        other->takeDamage(_damage);
    }
}

#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <QString>

// This file contains the GameObject hierarchy. (Parent classes).
// These classes will never be intantiated into the GameMap.
// Proper game objects contained in sub files.

// Class Declaration for GameObject
// Parent of all GameObjects -- virtual
class GameObject
{
public:
    GameObject();
    virtual ~GameObject();
    char print();

    void destroy();
    void move(const int xoff, const int yoff);

    virtual void update() = 0;
    virtual void collide(GameObject* other) = 0;
    virtual void takeDamage(const double amount) = 0;

    QString type() const;
    unsigned int xx() const;
    unsigned int yy() const;

protected:
    QString _name = "Generic Object";
    QString _type = "untyped";
    char _symbol = '!';
    unsigned int _x;
    unsigned int _y;
};

// Class declaration for Entity
// This is any GameObject which has health and may take damage
// This includes Enemy and Player
class Entity : public GameObject
{
public:
    Entity();

    void takeDamage(const double amount);

    double health();

protected:
    double _health;
};

// Class declaration for Enemy
// This GameObject deals engages in combat with the player
class Enemy : public Entity
{
public:
    Enemy();

    void collide(GameObject* other);

protected:
    double _damage;
};

#endif // GAMEOBJECTS_H

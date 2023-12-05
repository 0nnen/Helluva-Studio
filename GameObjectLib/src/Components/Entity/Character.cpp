#include "Components/Entity/Character.h"
#include "Components/Entity.h"
#include "Managers/WindowManager.h"

Character::Character() : Entity(200, 30, 20.f, 50.f, 5.f)
{
    directionCharacter = false;
    direction = Direction::Right;
}

Character::Character(int _hp, int _damage, const float& _speed, const float& _attackSpeed, const float& _range) : Entity(_hp, _damage, _speed, _attackSpeed, _range)
{
    directionCharacter = false;
    direction = Direction::Right;
}

void Character::setDirection(Direction newDirection) {
    direction = newDirection;
}

void Character::Update(const float& _delta)
{
    Entity::Update( _delta);
    if (direction == Direction::Left)
    {
        directionCharacter = true;
    }
    else if (direction == Direction::Right)
    {
        directionCharacter = false;
    }
}
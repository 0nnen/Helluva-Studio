#include "Components/Entity/Character.h"
#include "Components/Entity.h"
#include "Components/SpriteRenderer.h"
#include "Managers/WindowManager.h"
#include "Managers/CameraManager.h"


Character::Character() : Entity(200, 30, 15.f, 50.f, 5.f)
{
	directionCharacter = false;
	direction = Direction::Right;
}

Character::Character(int _hp, int _damage, const float& _speed, const float& _attackSpeed, const float& _range) : Entity(_hp, _damage, _speed, _attackSpeed, _range)
{
	directionCharacter = false;
	direction = Direction::Right;
}

void Character::SetDirection(Direction _newDirection) {

		direction = _newDirection;
		if (direction == Direction::Left)
		{
			GetOwner()->GetComponent<Sprite>()->SetScale(-1 * GetOwner()->GetScale().GetX(), GetOwner()->GetScale().GetY());
		}
		else if (direction == Direction::Right)
		{
			GetOwner()->GetComponent<Sprite>()->SetScale(GetOwner()->GetScale().GetX(), GetOwner()->GetScale().GetY());
		}
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

    // BULLET SHOOT
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        bullets.push_back(sf::CircleShape());
        bullets.back().setRadius(5);
        bullets.back().setOrigin(5, 5);
        bullets.back().setPosition(shape.getPosition());
        angles.push_back(atan2(sf::Mouse::getPosition(*WindowManager::GetWindow()).y - shape.getPosition().y,
            sf::Mouse::getPosition(*WindowManager::GetWindow()).x - shape.getPosition().x));
    }
	CameraManager::SetCenter(GetOwner()->GetPosition().GetX(), GetOwner()->GetPosition().GetY());
}
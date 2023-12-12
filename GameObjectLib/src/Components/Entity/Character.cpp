#include "Components/Entity/Character.h"
#include "Components/Entity.h"
#include "Components/SpriteRenderer.h"
#include "Managers/WindowManager.h"
#include "Managers/CameraManager.h"


Character::Character() : Entity()
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
            for (Sprite* sprite : GetOwner()->GetComponentsByType<Sprite>()) {
                if(sprite) sprite->SetScale(-1 * GetOwner()->GetScale().GetX(), GetOwner()->GetScale().GetY());
            }
		}
		else if (direction == Direction::Right)
		{
            for (Sprite* sprite : GetOwner()->GetComponentsByType<Sprite>()) {
                if (sprite) sprite->SetScale(GetOwner()->GetScale().GetX(), GetOwner()->GetScale().GetY());
            }
		}
}

void Character::Update(const float& _delta)
{
    Entity::Update( _delta);
    sf::RenderWindow* window = WindowManager::GetWindow();

    const sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    const sf::Vector2f worldMousePosition = window->mapPixelToCoords(mousePosition);
    Maths::Vector2f mousePositionVector = Maths::Vector2f(worldMousePosition.x, worldMousePosition.y);
    const Maths::Vector2f directionMouse = mousePositionVector - GetOwner()->GetPosition();
    

    if (directionMouse.x <= 0)
    {
        SetDirection(Left);
        directionCharacter = true;
    }
    else if (directionMouse.x > 0)
    {
        SetDirection(Right);
        directionCharacter = false;
    }

	CameraManager::SetCenter(GetOwner()->GetPosition().GetX(), GetOwner()->GetPosition().GetY());
}
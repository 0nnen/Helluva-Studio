#include "Components/SquareCollider.h"
#include "GameObject.h"

void SquareCollider::Render(sf::RenderWindow* _window) 
{
    Component::Render(_window);
}

void SquareCollider::RenderGUI(sf::RenderWindow* _window) 
{
    Component::RenderGUI(_window);
}

bool SquareCollider::IsColliding(const SquareCollider& _colliderA, const SquareCollider& _colliderB)
{
	const Maths::Vector2f positionA = _colliderA.GetOwner()->GetPosition();
	const Maths::Vector2f positionB = _colliderB.GetOwner()->GetPosition();
	return (positionA.x - _colliderA.GetWidth() / 2  < positionB.x + _colliderB.GetWidth() / 2 && positionA.x + _colliderA.GetWidth() / 2 > positionB.x - _colliderB.GetWidth() / 2 && positionA.y - _colliderA.GetHeight() / 2 < positionB.y + _colliderB.GetHeight() / 2 && positionA.y + _colliderA.GetHeight() /2 > positionB.y - _colliderB.GetHeight() / 2);
}

bool SquareCollider::IsAbove(const SquareCollider& _colliderA, const SquareCollider& _colliderB)
{
	const Maths::Vector2f positionA = _colliderA.GetOwner()->GetPosition();
	const Maths::Vector2f positionB = _colliderB.GetOwner()->GetPosition();
	return positionA.y + _colliderA.GetHeight() / 2 < positionB.y - _colliderB.GetHeight() / 2;
}

bool SquareCollider::IsLeft(const SquareCollider& _colliderA, const SquareCollider& _colliderB)
{
    const Maths::Vector2f positionA = _colliderA.GetOwner()->GetPosition();
    const Maths::Vector2f positionB = _colliderB.GetOwner()->GetPosition();
    return positionA.x + _colliderA.GetWidth() / 2 < positionB.x - _colliderB.GetWidth() / 2;
}

bool SquareCollider::IsRight(const SquareCollider& _colliderA, const SquareCollider& _colliderB)
{
    const Maths::Vector2f positionA = _colliderA.GetOwner()->GetPosition();
    const Maths::Vector2f positionB = _colliderB.GetOwner()->GetPosition();
    return positionA.x - _colliderA.GetWidth() / 2 > positionB.x + _colliderB.GetWidth() / 2;
}

bool SquareCollider::IsBelow(const SquareCollider& _colliderA, const SquareCollider& _colliderB)
{
    const Maths::Vector2f positionA = _colliderA.GetOwner()->GetPosition();
    const Maths::Vector2f positionB = _colliderB.GetOwner()->GetPosition();
    return positionA.y - _colliderA.GetHeight() / 2 > positionB.y + _colliderB.GetHeight() / 2;
}






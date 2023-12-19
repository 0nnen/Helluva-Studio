#include "Components/SquareCollider.h"

bool SquareCollider::IsColliding(const SquareCollider& _rigidBody2DA, const SquareCollider& _squareColliderB)
{
	const Maths::Vector2f positionA = _rigidBody2DA.GetPosition();
	const Maths::Vector2f positionB = _squareColliderB.GetPosition();
	return (positionA.x - _rigidBody2DA.GetWidthCollider() / 2 < positionB.x + _squareColliderB.GetWidthCollider() / 2 && positionA.x + _rigidBody2DA.GetWidthCollider() / 2 > positionB.x - _squareColliderB.GetWidthCollider() / 2 && positionA.y - _rigidBody2DA.GetHeightCollider() / 2 < positionB.y + _squareColliderB.GetHeightCollider() / 2 && positionA.y + _rigidBody2DA.GetHeightCollider() / 2 > positionB.y - _squareColliderB.GetHeightCollider() / 2);
}

bool SquareCollider::IsAbove(const SquareCollider& _rigidBody2DA, const SquareCollider& _squareColliderB)
{
	if (_squareColliderB.GetActiveCollider())
	{
		const Maths::Vector2f positionA = _rigidBody2DA.GetPosition();
		const Maths::Vector2f positionB = _squareColliderB.GetPosition();
		return positionA.y - _rigidBody2DA.GetHeightCollider() / 2 < positionB.y + _squareColliderB.GetHeightCollider() / 2;
	}
}

bool SquareCollider::IsLeft(const SquareCollider& _rigidBody2DA, const SquareCollider& _squareColliderB)
{
	const Maths::Vector2f positionA = _rigidBody2DA.GetPosition();
	const Maths::Vector2f positionB = _squareColliderB.GetPosition();
	return positionA.x - _rigidBody2DA.GetWidthCollider() / 2 < positionB.x + _squareColliderB.GetWidthCollider() / 2;
}

bool SquareCollider::IsRight(const SquareCollider& _rigidBody2DA, const SquareCollider& _squareColliderB)
{
	const Maths::Vector2f positionA = _rigidBody2DA.GetPosition();
	const Maths::Vector2f positionB = _squareColliderB.GetPosition();
	return positionA.x + _rigidBody2DA.GetWidthCollider() / 2 > positionB.x - _squareColliderB.GetWidthCollider() / 2;
}

bool SquareCollider::IsBelow(const SquareCollider& _rigidBody2DA, const SquareCollider& _squareColliderB)
{
	const Maths::Vector2f positionA = _rigidBody2DA.GetPosition();
	const Maths::Vector2f positionB = _squareColliderB.GetPosition();
	return positionA.y + _rigidBody2DA.GetHeightCollider() / 2 > positionB.y - _squareColliderB.GetHeightCollider() / 2;
}

void SquareCollider::Update(const float& _delta)
{
	Component::Update(_delta);
}

void SquareCollider::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);
	if (GetOwner()) SetPosition((GetOwner()->GetPosition() + perfectPosition));

		
	/*	sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(widthCollider, heightCollider));
		if (name == "ground") rectangle.setFillColor(sf::Color::Red);
		rectangle.setOrigin(widthCollider / 2, heightCollider / 2);
		rectangle.setPosition(GetPosition().x, GetPosition().y);
		_window->draw(rectangle);*/
	
}
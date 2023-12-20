#include "Components/Shapes/Rectangle.h"
#include "Components/RigidBody2D.h"

Rectangle::Rectangle()
{
	rectangle.setFillColor(sf::Color::Green);
}

void Rectangle::Render(sf::RenderWindow* _window)
{
	const Maths::Vector2f position = GetOwner()->GetPosition();
	const Maths::Vector2f scale = GetOwner()->GetScale();
	const RigidBody2D* rigidBody = GetOwner()->GetComponent< RigidBody2D>();
	const float width = rigidBody->GetWidthCollider();
	const float height = rigidBody->GetHeightCollider();

	rectangle.setPosition(sf::Vector2f(position.x, position.y));
	rectangle.setScale(sf::Vector2f(scale.x, scale.y));
	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setOrigin(sf::Vector2f(width / 2, height / 2));

	Component::Render(_window);
	_window->draw(rectangle);
}

void Rectangle::RenderGUI(sf::RenderWindow* _window)
{
	const Maths::Vector2f position = GetOwner()->GetPosition();
	const Maths::Vector2f scale = GetOwner()->GetScale();
	const RigidBody2D* rigidBody = GetOwner()->GetComponent< RigidBody2D>();
	const float width = rigidBody->GetWidthCollider();
	const float height = rigidBody->GetHeightCollider();

	rectangle.setPosition(sf::Vector2f(position.x, position.y));
	rectangle.setScale(sf::Vector2f(scale.x, scale.y));
	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setOrigin(sf::Vector2f(width / 2, height / 2));

	Component::RenderGUI(_window);
	_window->draw(rectangle);
}

void Rectangle::Update(const float& _delta)
{
	Component::Update(_delta);

}

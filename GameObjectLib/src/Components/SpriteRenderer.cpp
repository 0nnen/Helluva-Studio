#include "Components/SpriteRenderer.h"
#include "Components/RigidBody2D.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Managers/AssetManager.h"
#include "Managers/HUDManager.h"
#include "Managers/CameraManager.h"

#include <cmath>
Sprite::Sprite()
{
	scalex = 1.0f;
	scaley = 1.0f;
	width = 1.0f;
	height = 1.0f;
}

sf::Vector2f Sprite::GetBounds() const
{
	return sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
}

void Sprite::SetTexture(sf::Texture* _texture)
{
	texture = _texture;
	sprite.setTexture(*texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	RigidBody2D* rigidBody2D = GetOwner()->GetComponent<RigidBody2D>();
	rigidBody2D->SetSize(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
}


void Sprite::SetTexture(sf::Texture* _texture, unsigned int& _frame)
{
	texture = _texture;
	sprite.setTexture(*texture);
	RigidBody2D* rigidBody2D = GetOwner()->GetComponent<RigidBody2D>();
	rigidBody2D->SetSize(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
}

void Sprite::SetRecTexture(const unsigned int& _frame, const int& width, const int& height)
{
	sprite.setTextureRect(sf::IntRect(width * _frame, 0, width, height));
	sprite.setOrigin(width / 2, height / 2);
	RigidBody2D* rigidBody2D = GetOwner()->GetComponent<RigidBody2D>();
	rigidBody2D->SetSize(width, height);
}

void Sprite::SetRecTexture(const unsigned int& _frameWidth, const unsigned int& _frameHeight, const int& _width, const int& _height)
{
	sprite.setTextureRect(sf::IntRect(_width * _frameWidth, _height * _frameHeight, _width, _height));
	sprite.setOrigin(_width / 2, _height / 2);
	RigidBody2D* rigidBody2D = GetOwner()->GetComponent<RigidBody2D>();
	rigidBody2D->SetSize(_width, _height);
}


void Sprite::SetRecTextureWithFrame(const unsigned int& _actualFrameWidth, const unsigned int& _actualFrameHeight, const unsigned int& _frameWidth, const unsigned int& _frameHeight)
{
	const float _width = sprite.getLocalBounds().width;
	const float _height = sprite.getLocalBounds().height;
	const float widthAfterFrame = _width / _frameWidth;
	const float heightAfterFrame = _height / _frameHeight;

	sprite.setTextureRect(sf::IntRect(widthAfterFrame * _actualFrameWidth, heightAfterFrame * _actualFrameHeight, _width / _frameWidth, _height / _frameHeight));
	sprite.setOrigin(widthAfterFrame / 2, heightAfterFrame / 2);
	RigidBody2D* rigidBody2D = GetOwner()->GetComponent<RigidBody2D>();
	rigidBody2D->SetSize(widthAfterFrame, heightAfterFrame);
}

void Sprite::Rotate(const float& angle)
{
	isRotate = true;
	rotate = angle;
	sprite.setRotation(angle);
}

void Sprite::Update(const float& _delta)
{

}

void Sprite::Render(sf::RenderWindow* _window)
{
	if (isVisible)
	{
		const Maths::Vector2f position = GetOwner()->GetPosition();
		const Maths::Vector2f scale = GetOwner()->GetScale();
		const float angle = GetOwner()->GetRotation();
		const RigidBody2D* rigidBody = GetOwner()->GetComponent<RigidBody2D>();
		const float width = rigidBody->GetWidthCollider();
		const float height = rigidBody->GetHeightCollider();
		

		sprite.setPosition(sf::Vector2f(position.x, position.y));
		sprite.setScale(sf::Vector2f(scale.x, scale.y));
		if(!isRotate) sprite.setRotation(angle);

		Component::Render(_window);
		_window->draw(sprite);
	}

}

void Sprite::RenderGUI(sf::RenderWindow* _window)
{
	if (isVisible)
	{
		const Maths::Vector2f position = GetOwner()->GetPosition();
		const Maths::Vector2f scale = GetOwner()->GetScale();
		const float angle = GetOwner()->GetRotation();
		const RigidBody2D* rigidBody = GetOwner()->GetComponent<RigidBody2D>();
		const float width = rigidBody->GetWidthCollider();
		const float height = rigidBody->GetHeightCollider();


		sprite.setPosition(sf::Vector2f(position.x, position.y));
		sprite.setScale(sf::Vector2f(scale.x, scale.y));
		if (!isRotate) sprite.setRotation(angle);

		Component::RenderGUI(_window);
		_window->draw(sprite);
	}
}

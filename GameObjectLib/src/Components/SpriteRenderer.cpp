#include "Components/SpriteRenderer.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Managers/AssetManager.h"
#include "Managers/HUDManager.h"
#include "Managers/CameraManager.h"

Sprite::Sprite()
{
	scalex = 1.0f;
	scaley = 1.0f;
}

sf::Vector2f Sprite::GetBounds() const
{
	return sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
}

void Sprite::SetScale()
{
	sprite.setScale(GetOwner()->GetScale().GetX(), GetOwner()->GetScale().GetY());
}

void Sprite::SetScale(const float& _scaleX, const float& _scaleY)
{
	sprite.setScale(_scaleX, _scaleY);
}

void Sprite::SetOrigin()
{
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}


void Sprite::Update(const float& _delta) {}

void Sprite::SetSprite()
{
	const Maths::Vector2f position = GetOwner()->GetPosition();
	sprite.setPosition(position.x, position.y);
}

void Sprite::SetTexture(sf::Texture* _texture)
{
	texture = _texture;
	sprite.setTexture(*texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void Sprite::SetRecTexture(const unsigned int& _frame, const unsigned int& _totalFrame)
{ 
	int textureWidth = sprite.getLocalBounds().width / _totalFrame;
	int textureHeight = sprite.getLocalBounds().height;
	sprite.setTextureRect(sf::IntRect(textureWidth * _frame, 0, textureWidth, textureHeight));
}

void Sprite::Render(sf::RenderWindow* _window)
{

	this->SetSprite();
	Component::Render(_window);
	_window->draw(sprite);
}

void Sprite::RenderGUI(sf::RenderWindow* _window)
{
	this->SetSprite();
	Component::RenderGUI(_window);
	_window->draw(sprite);
}

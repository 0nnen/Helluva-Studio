#include "Components/UIElements/Button.h"
#include "Components/RigidBody2D.h"
#include "Managers/WindowManager.h"
#include "Managers/HUDManager.h"
#include "Managers/CameraManager.h"
#include "Managers/FontManager.h"
#include "Managers/AudioManager.h"
#include "Managers/LanguageManager.h"
#include <iostream>

Button::Button()
{
	this->height = 0.f;
	this->width = 0.f;
	this->fontSize = 16;
	this->rectangle.setFillColor(sf::Color(90, 34, 139));
	this->rectangle.setOutlineColor(sf::Color::White);
	text.setFillColor(sf::Color::White);
	this->SetFontSize(16);

	this->SetFont(*FontManager::GetFont("PixelNES"));
	this->SetOrigin();
}

void Button::SetOrigin()
{
	rectangle.setOrigin(sf::Vector2f(width / 2, height / 2));
	text.setOrigin(sf::Vector2f(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2));
}

void Button::SetSize()
{
	rectangle.setSize(sf::Vector2f(width, height));
}

void Button::SetSize(const float& _width, const float& _height)
{
	width = _width;
	height = _height;
	rectangle.setSize(sf::Vector2f(width, height));
}

void Button::SetScale(const Maths::Vector2f& _scale)
{
	rectangle.setScale(_scale.x, _scale.y);
	text.setScale(_scale.x, _scale.y);
}

void Button::SetPosition(const float& _x, const float& _y)
{
	text.setPosition(_x, _y);
	rectangle.setPosition(_x, _y);
}

void Button::SetPosition(const Maths::Vector2f& _position)
{
	text.setPosition(_position.x, _position.y);
	rectangle.setPosition(_position.x, _position.y);
}


void Button::SetFontSize(const unsigned int& _fontSize)
{
	fontSize = _fontSize;
	text.setCharacterSize(_fontSize);
}

void Button::SetFont(const sf::Font& _font)
{
	font = _font;
	text.setFont(font);
}

void Button::SetText(const std::string& _text, const sf::Color& _color)
{
	text.setString(LanguageManager::GetInstance()->GetButtonsByKey(GetOwner()->GetName()));
	text.setFillColor(_color);
	if (width == 0 && height == 0)
	{
		rectangle.setSize(sf::Vector2f(text.getLocalBounds().width * 1.2, text.getLocalBounds().height * 1.2));
	}
}

void Button::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);
	const Maths::Vector2f position = GetOwner()->GetPosition();
	SetPosition(position.x, position.y);
	const  Maths::Vector2f scale = GetOwner()->GetScale();
	SetScale(scale);
	if (width == 0 && height == 0)
	{
		RigidBody2D* rigidBody2D = GetOwner()->GetComponent<RigidBody2D>();
		SetSize(rigidBody2D->GetWidthCollider(), rigidBody2D->GetHeightCollider());	
	}

	if (needBackground && !rectangle.getTexture()) {
		rectangle.setFillColor(sf::Color(90, 34, 139));
		rectangle.setSize(sf::Vector2f(width, height));
	}
	SetOrigin();
	if (needBackground) {
		_window->draw(rectangle);
	}
	_window->draw(text);
}

void Button::RenderGUI(sf::RenderWindow* _window)
{
	Component::RenderGUI(_window);
	const Maths::Vector2f position = GetOwner()->GetPosition();
	SetPosition(position.x, position.y);
	const  Maths::Vector2f scale = GetOwner()->GetScale();
	SetScale(scale);
	if (width == 0 && height == 0)
	{
		RigidBody2D* rigidBody2D = GetOwner()->GetComponent<RigidBody2D>();
		SetSize(rigidBody2D->GetWidthCollider(), rigidBody2D->GetHeightCollider());
	}

	if (needBackground && !rectangle.getTexture()) {
		rectangle.setFillColor(sf::Color(90, 34, 139));
		rectangle.setSize(sf::Vector2f(width, height));
	}
	SetOrigin();
	if (needBackground) _window->draw(rectangle);
	_window->draw(text);
}

void Button::Update(const float& _delta)
{
	Sprite* sprite = GetOwner()->GetComponent<Sprite>();
	if (sprite) 
	{
		if (IsClicked(sprite) && state != Button::StateButton::Clicked)
		{
			state = Button::Clicked;
			sprite->SetRecTexture(0, 2, sprite->GetBounds().x, sprite->GetBounds().y);
		}
		else if (IsOver(sprite) && state != Button::StateButton::Hover && state != Button::StateButton::Clicked)
		{
			state = Button::Hover;
			sprite->SetRecTexture(0, 1, sprite->GetBounds().x, sprite->GetBounds().y);
		}
		else if (!IsOver(sprite) && state != Button::StateButton::Normal && state != Button::StateButton::Clicked)
		{
			state = Button::Normal;
			sprite->SetRecTexture(0, 0, sprite->GetBounds().x, sprite->GetBounds().y);
		}
	}
	text.setString(LanguageManager::GetInstance()->GetButtonsByKey(GetOwner()->GetName()));
}

bool Button::IsOver(const Sprite* sprite)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*WindowManager::GetWindow());
	if (GetOwner()->GetLayer() == LayerType::HUD)return sprite->GetSprite().getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)) && GetOwner()->GetActive();
	else
	{
		sf::Vector2f worldPos = WindowManager::GetWindow()->mapPixelToCoords(mousePosition, CameraManager::GetView());
		return sprite->GetSprite().getGlobalBounds().contains(worldPos) && GetOwner()->GetActive();
	}
}

bool Button::IsClicked()
{
	Sprite* sprite = GetOwner()->GetComponent<Sprite>();
	
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*WindowManager::GetWindow());
		if (GetOwner()->GetLayer() == LayerType::HUD)
		{
			if(sprite) return sprite->GetSprite().getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && GetOwner()->GetActive();
			return rectangle.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && GetOwner()->GetActive();
		}
		else
		{
			sf::Vector2f worldPos = WindowManager::GetWindow()->mapPixelToCoords(mousePosition, CameraManager::GetView());
			if (sprite) return sprite->GetSprite().getGlobalBounds().contains(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && GetOwner()->GetActive();
			return rectangle.getGlobalBounds().contains(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && GetOwner()->GetActive();
		}

}
bool Button::IsClicked(const Sprite* _sprite)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*WindowManager::GetWindow());
	if (GetOwner()->GetLayer() == LayerType::HUD)
	{
		 return _sprite->GetSprite().getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && GetOwner()->GetActive();
	}
	else
	{
		sf::Vector2f worldPos = WindowManager::GetWindow()->mapPixelToCoords(mousePosition, CameraManager::GetView());
		return _sprite->GetSprite().getGlobalBounds().contains(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && GetOwner()->GetActive();
	}
}

Button::~Button() {}
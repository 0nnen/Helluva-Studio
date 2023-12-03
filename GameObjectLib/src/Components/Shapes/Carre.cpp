#include "Components/Shapes/Carre.h"
#include "Managers/WindowManager.h"
#include "Managers/CameraManager.h"

Carre::Carre() 
{
	this->side = 50.f;
	this->outlineThickness = 2.f;

	this->fillColor = sf::Color::White;
	this->outlineColor = sf::Color::Black;
	
	this->square.setSize(sf::Vector2f(side, side));
	this->square.setFillColor(fillColor);
	this->square.setOutlineColor(outlineColor);
	this->square.setOutlineThickness(outlineThickness);
	this->SetOrigin();
}

void Carre::Render(sf::RenderWindow* _window) 
{
	const auto position = GetOwner()->GetPosition();
	square.setPosition(position.x, position.y);
	Component::Render(_window);
	_window->draw(square);
}

void Carre::RenderGUI(sf::RenderWindow* _window)
{
	const auto position = GetOwner()->GetPosition();
	square.setPosition(position.x, position.y);
	Component::RenderGUI(_window);
	_window->draw(square);
}


bool Carre::IsClicked() 
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*WindowManager::GetWindow());
	sf::Vector2f worldPos = WindowManager::GetWindow()->mapPixelToCoords(mousePos, CameraManager::GetView());
	return square.getGlobalBounds().contains(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}


void Carre::SetOutline(const float& _outlineThickness, const sf::Color& _outlineColor)
{
	outlineThickness = _outlineThickness;
	square.setOutlineThickness(_outlineThickness);
	outlineColor = _outlineColor;
	square.setOutlineColor(_outlineColor);
	
}

void Carre::SetColor(const sf::Color& _fillColor)
{ 
	fillColor = _fillColor;
	square.setFillColor(_fillColor);
}

void Carre::SetSize(const float& _side) 
{
	side = _side;
	square.setSize(sf::Vector2f(side, side));
}

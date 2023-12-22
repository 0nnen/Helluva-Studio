#include "Components/UIElements/Slider.h"
#include "Managers/SceneManager.h"
#include "Managers/AudioManager.h"
#include "Managers/WindowManager.h"
#include "Managers/SceneManager.h"

Slider::Slider() 
{
	minData = 0.f;
	incertitude = 20.f;
	bar.setFillColor(sf::Color::Magenta);
	cursorText.setFillColor(sf::Color::White);
	titleText.setFillColor(sf::Color::White);
	cursor.setFillColor(sf::Color(90, 34, 139));
	cursor.setOutlineThickness(3);
	cursor.setOutlineColor(sf::Color::White);
	percent = 0.f;
	previousData = data;
}

void Slider::SetSizeBar(float _width, float _height)
{
	bar.setSize(sf::Vector2f(_width, _height));
	bar.setOrigin(sf::Vector2f(_width / 2, _height / 2));
}

void Slider::SetSizeCursor(float _width, float _height)
{
	cursor.setSize(sf::Vector2f(_width, _height));
	cursor.setOrigin(sf::Vector2f(_width / 2, _height / 2));
}

void Slider::SetCursorText(unsigned int _fontSize) {
	fontSize = _fontSize;
	if (!font.loadFromFile("Assets/Fonts/PixelNES.otf")) 
	{
		std::cout << "no font found" << std::endl;
	}
	cursorText = sf::Text(std::to_string(this->GetDataInt()), font, fontSize);
	cursorText.setOrigin(cursorText.getLocalBounds().width / 2, cursorText.getLocalBounds().height / 2);
}

void Slider::SetCursorText(unsigned int _fontSize, float _data) 
{
	data = _data;
	fontSize = _fontSize;
	if (!font.loadFromFile("Assets/Fonts/PixelNES.otf")) 
	{
		std::cout << "no font found" << std::endl;
	}
	cursorText = sf::Text(std::to_string(this->GetDataInt()), font, fontSize);
	cursorText.setOrigin(cursorText.getLocalBounds().width / 2, cursorText.getLocalBounds().height / 2);
}

void Slider::SetTitleText() 
{
	titleText = sf::Text(GetOwner()->GetName(), font, fontSize + 20);
	cursorText.setOrigin(cursorText.getLocalBounds().width / 2, cursorText.getLocalBounds().height / 2);
}

void Slider::SetPosition(float _x, float _y)
{
	bar.setPosition(sf::Vector2f(_x, _y));
	cursor.setPosition(sf::Vector2f(_x + bar.getSize().x / 2, _y));
	cursorText.setPosition(sf::Vector2f(_x + bar.getSize().x / 2, _y));
	titleText.setPosition(sf::Vector2f(_x - bar.getSize().x / 2, _y + bar.getSize().y / 2));

}

void Slider::Render(sf::RenderWindow* _window) 
{
	Component::Render(_window);
	_window->draw(bar);
	_window->draw(cursor);
	_window->draw(cursorText);
	_window->draw(titleText);
}

void Slider::RenderGUI(sf::RenderWindow* _window)
{
	Component::RenderGUI(_window);
	_window->draw(bar);
	_window->draw(cursor);
	_window->draw(cursorText);
	_window->draw(titleText);
}
float Slider::GetPercent(float _x, float _y, float width) {
	if (width == 0.0) 
	{
		return 0.0;
	}
	float pourcentage = ((_y - (_x - width / 2)) / width) * 100.0;
	// Assurez-vous que le pourcentage reste entre 0 et 100
	pourcentage = std::fmax(0.0, std::fmin(100.0, pourcentage));

	return pourcentage;
}


void Slider::Update(const float& _delta) 
{
	Component::Update(_delta);

	sf::Vector2i mousePos = sf::Mouse::getPosition(*WindowManager::GetWindow());
	previousData = data;

	if (this->isClicked(mousePos)) 
	{

		float cursorX = static_cast<float>(mousePos.x);
		if (cursorX <= (bar.getPosition().x - bar.getSize().x / 2) - incertitude) 
		{
			cursorX = (bar.getPosition().x - bar.getSize().x / 2) ;
			this->SetData(minData);
		}
		else if (cursorX >= bar.getPosition().x + bar.getSize().x / 2 + incertitude) 
		{
			cursorX = bar.getPosition().x + bar.getSize().x / 2;
			this->SetData(maxData);
		}
		else if (cursorX != cursor.getPosition().x)
		{
			percent = this->GetPercent(bar.getPosition().x, cursor.getPosition().x, bar.getSize().x);
			this->SetData(((maxData - minData) * percent / 100) + minData);
			this->SetCursorText(fontSize);
		}
		cursor.setPosition(cursorX , cursor.getPosition().y);
		cursorText.setPosition(cursorX , cursor.getPosition().y);
	}
}

bool Slider::isClicked(const sf::Vector2i& _mousePosition) 
{
	return cursor.getGlobalBounds().contains(sf::Vector2f(_mousePosition.x, _mousePosition.y)) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && GetOwner()->GetActive();
}
#include "Components/HealthPointBar.h"
#include "Components/Entity.h"
HealthPointBar::HealthPointBar() 
{
	backgroundBar.setFillColor(sf::Color::Black);
	hpBar.setFillColor(sf::Color::Green);
}


void HealthPointBar::SetOrigin() 
{
	backgroundBar.setOrigin(sf::Vector2f(width / 2, height / 2));
	hpBar.setOrigin(sf::Vector2f(width / 2, height / 2));
}

void HealthPointBar::SetPosition(const float& _x, const float& _y) 
{
	backgroundBar.setPosition(sf::Vector2f(_x, _y - aboveSprite));
	hpBar.setPosition(sf::Vector2f(_x , _y - aboveSprite));
}

void HealthPointBar::SetHealthPointBar() 
{
	this->SetHealthPoint(GetOwner()->GetComponent<Entity>()->GetHealthPoint());
	this->SetMaxHealthPoint(GetOwner()->GetComponent<Entity>()->GetMaxHealthPoint());
	if (healthPoint > maxHealthPoint * 0.6666f) 
	{
		hpBar.setFillColor(sf::Color::Green);
	}
	else if (healthPoint > maxHealthPoint * 0.3333f) 
	{
		hpBar.setFillColor(sf::Color::Yellow);
	}
	else
	{
		hpBar.setFillColor(sf::Color::Red);
	}
	const float percent = width * healthPoint / maxHealthPoint;
	hpBar.setSize(sf::Vector2f(percent, height));
	backgroundBar.setSize(sf::Vector2f(width, height));
	const auto position = GetOwner()->GetPosition();
	this->SetPosition(position.x, position.y);
	hpBar.setScale(sf::Vector2f(scaleX, scaleY));
	backgroundBar.setScale(sf::Vector2f(scaleX, scaleY));
	this->SetOrigin();
}
void HealthPointBar::Update(const float& _delta) 
{
	Component::Update(_delta);
}

void HealthPointBar::Render(sf::RenderWindow* _window) 
{
	this->SetHealthPointBar();
	Component::Render(_window);
	_window->draw(backgroundBar);
	_window->draw(hpBar);
}

void HealthPointBar::RenderGUI(sf::RenderWindow* _window)
{
	this->SetHealthPointBar();
	Component::RenderGUI(_window);
	_window->draw(backgroundBar);
	_window->draw(hpBar);
}
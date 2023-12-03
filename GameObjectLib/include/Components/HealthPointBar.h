#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"
class HealthPointBar : public Component
{
public:

	HealthPointBar();

	inline void SetHealthPoint(const int& _hp) { healthPoint = _hp; }
	inline void SetMaxHealthPoint(const int& _maxHp) { maxHealthPoint = _maxHp; }
	inline void SetAboveSprite(const float& _height) { aboveSprite = _height; }
	void SetOrigin();
	inline void SetSize(const float& _width, const float& _height)
	{
		width = _width;
		height = _height;
	}
	inline void SetScale(const float& _scaleX, const float& _scaleY)
	{
		scaleX = _scaleX;
		scaleY = _scaleY;
	}
	void SetPosition(const float& _x, const float& _y);

	void SetHealthPointBar();
	void Render(sf::RenderWindow* _window) override;
	void RenderGUI(sf::RenderWindow* _window) override;
	void Update(const float& _delta) override;

private:
	int healthPoint;
	int maxHealthPoint;
	float aboveSprite = 0.f;
	float width = 1.0f;
	float height = 1.0f;
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	sf::RectangleShape backgroundBar;
	sf::RectangleShape hpBar;

};


#pragma once

#include "Component.h"

#include <SFML/Graphics.hpp>

class Text : public Component
{
public:
	Text();

	void SettingText(sf::Text& _text, const std::string& _string, const unsigned int& _fontSize, const sf::Uint32& _style, const sf::Color& _color);
	void SetTitle(const std::string& _text, const unsigned int& _fontSize, const sf::Uint32& _style, const sf::Color& _color);
	void SetText(const std::string& _text, const unsigned int& _fontSize, const sf::Uint32& _style, const sf::Color& _color);
	void LoadTextFromFile(const std::string& _fileName);
	void AddText(const std::string& _text);
	void SetDisplayText(const std::string& _text);

	void SetPositionText(const Maths::Vector2f& _position) {
		positionText = _position;
	}
	void SetPositionTitle(const Maths::Vector2f& _position) {
		positionTitle = _position;
	}

	void Render(sf::RenderWindow* _window) override;
	void RenderGUI(sf::RenderWindow* _window) override;
	void Update(const float& _delta) override;

	~Text();
private:
	sf::Text displayText;
	sf::Text title;
	std::vector<std::string> finalTexts;
	Maths::Vector2f positionText = Maths::Vector2f::Zero;
	Maths::Vector2f positionTitle = Maths::Vector2f::Zero;

	unsigned int textIndex = 0;
	unsigned int charIndex = 0;

	float pauseDuration = 3.f;
	float totalDuration = 0.f;
	float currentTime = 0.f;

	bool isDone = false;
};


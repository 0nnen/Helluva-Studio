#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"
#include "Components/SpriteRenderer.h"
#include "Scene.h"

class Button : public Component
{

public:
	Button();
	enum StateButton {Normal, Hover, Clicked};
	void SetOrigin();
	void SetSize();
	void SetSize(const float& _width, const float& _height);
	void SetScale(const Maths::Vector2f& _scale);
	void SetPosition(const float& _x, const float& _y);
	void SetPosition(const Maths::Vector2f& _position);
	void SetFont(const sf::Font& _font);
	void SetFontSize(const unsigned int& _fontSize);
	void SetText(const std::string& _text, const sf::Color& _color);
	inline void SetIsBackgroundNeeded(const bool& _state) { needBackground = _state; }

	void Render(sf::RenderWindow* _window) override;
	void RenderGUI(sf::RenderWindow* _window) override;

	void Update(const float& _delta) override;
	bool IsClicked();
	bool IsClicked(const Sprite* _sprite);
	bool IsOver(const Sprite* _sprite);
	inline void SetState(const StateButton& _state) {
		state = _state;
		Sprite* sprite = GetOwner()->GetComponent<Sprite>();
		if (sprite)
		{
			if (state == Button::StateButton::Clicked)
			{
				sprite->SetRecTexture(0, 2, sprite->GetBounds().x, sprite->GetBounds().y);
			}
			else if (state == Button::StateButton::Hover)
			{
				sprite->SetRecTexture(0, 1, sprite->GetBounds().x, sprite->GetBounds().y);
			}
			else if (state == Button::StateButton::Normal)
			{
				sprite->SetRecTexture(0, 0, sprite->GetBounds().x, sprite->GetBounds().y);
			}
		}
	}

	sf::RectangleShape& GetRectangleShape() {
		return rectangle;
	}

	~Button();

private:
	bool needBackground = true;
	float width, height;
	unsigned int fontSize;
	StateButton state = Normal;
	sf::Font font;
	sf::RectangleShape rectangle;
	sf::Text text;
};


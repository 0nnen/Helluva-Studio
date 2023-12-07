#pragma once

#include "Component.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>

class Sprite : public Component
{
public:
	Sprite();
	~Sprite() override = default;

	void Update(const float& _delta);
	void SetScale();
	void SetScale(const float& _scaleX, const float& _scaleY);
	void SetOrigin();
	inline sf::Vector2f GetSize() const { return sf::Vector2f(sprite.getLocalBounds().width * scalex, sprite.getLocalBounds().height * scaley); }
	sf::Vector2f GetBounds() const;


	inline float GetTop() const { return sprite.getLocalBounds().top * scaley; }
	inline float GetBottom()  const { return (sprite.getLocalBounds().top + sprite.getLocalBounds().height) * scaley; }
	inline float GetLeft() const { return sprite.getLocalBounds().left * scalex; }
	inline float GetRight() const { return (sprite.getLocalBounds().left + sprite.getLocalBounds().width) * scalex; }

	void SetSprite();
	void SetTexture(sf::Texture* _texture);
	void SetRecTexture(const unsigned int& _frame, const unsigned int& _totalFrame);

	void Render(sf::RenderWindow* _window) override;
	void RenderGUI(sf::RenderWindow* _window) override;


private:

	sf::Texture* texture = nullptr;
	float scalex, scaley;
	sf::Sprite sprite;
};

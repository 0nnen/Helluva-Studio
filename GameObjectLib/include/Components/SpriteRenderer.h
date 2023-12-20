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
	inline sf::Vector2f GetSize() const { return sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height); }
	inline Maths::Vector2f GetSizeV2f() const { return Maths::Vector2f(width, height); }
	sf::Vector2f GetBounds() const;
	sf::Vector2f GetPosition() const { return sprite.getPosition(); }


	inline float GetTop() const { return sprite.getGlobalBounds().top; }
	inline float GetBottom()  const { return (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height); }
	inline float GetLeft() const { return sprite.getGlobalBounds().left ; }
	inline float GetRight() const { return (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width); }

	sf::Sprite GetSprite() const { return sprite; }

	void SetTexture(sf::Texture* _texture);
	void SetTexture(sf::Texture* _texture, unsigned int& _frame);
	void SetRecTexture(const unsigned int& _frame, const int& width, const int& height);
	void SetRecTexture(const unsigned int& _frameWidth, const unsigned int& _frameHeight, const int& width, const int& height);
	void SetRecTextureWithFrame(const unsigned int& _frameWidth, const unsigned int& _frameHeight, const unsigned int& _actualFrameWidth, const unsigned int& _actualFrameHeight);

	void Rotate(const float& angle);

	void Render(sf::RenderWindow* _window) override;
	void RenderGUI(sf::RenderWindow* _window) override;


private:

	sf::Texture* texture = nullptr;
	float scalex, scaley, width, height;
	sf::Sprite sprite;
	float rotate = 0.f;
	bool isRotate = false;
};

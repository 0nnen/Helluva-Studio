#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include "Component.h"

class SquareCollider : public Component
{
public:
	SquareCollider() = default;
	~SquareCollider() override = default;

	void Render(sf::RenderWindow* _window) override;
	void RenderGUI(sf::RenderWindow* _window) override;

	inline float GetWidth() const { return width; }
	inline float GetHeight() const { return height; }

	inline void SetSize(const float& _width, const float& _height)
	{
		width = _width;
		height = _height;
	}
	inline void SetScale(const float& _scaleX, const float& _scaleY)
	{ 
		scaleX = _scaleX;
		width *= _scaleX;
		height *= _scaleY;
		scaleY = _scaleY;
	}

	static bool IsColliding(const SquareCollider& _colliderA, const SquareCollider& _colliderB);

	static bool IsAbove(const SquareCollider& _colliderA, const SquareCollider& _colliderB);
	static bool IsLeft(const SquareCollider& _colliderA, const SquareCollider& _colliderB);
	static bool IsRight(const SquareCollider& _colliderA, const SquareCollider& _colliderB);
	static bool IsBelow(const SquareCollider& _colliderA, const SquareCollider& _colliderB);

private:
	float width = 1.0f;
	float height = 1.0f;
	float scaleX = 1.0f;
	float scaleY = 1.0f;
};

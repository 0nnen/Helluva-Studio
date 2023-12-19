#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
class SquareCollider : public Component
{
public:
	static bool IsColliding(const SquareCollider& _rigidBody2DA, const SquareCollider& _rigidBody2DB);

	static bool IsAbove(const SquareCollider& _rigidBody2DA, const SquareCollider& _rigidBody2DB);
	static bool IsLeft(const SquareCollider& _rigidBody2DA, const SquareCollider& _rigidBody2DB);
	static bool IsRight(const SquareCollider& _rigidBody2DA, const SquareCollider& _rigidBody2DB);
	static bool IsBelow(const SquareCollider& _rigidBody2DA, const SquareCollider& _rigidBody2DB);

	float GetWidthCollider() const { return widthCollider; }
	float GetHeightCollider() const { return heightCollider; }
	void SetHeightCollider(const float& _heightCollider) { heightCollider = _heightCollider; }
	void SetWidthCollider(const float& _widthCollider) { widthCollider = _widthCollider; }

	float GetTopCollider() const { return position.y - heightCollider / 2; }
	float GetBottomCollider() const { return position.y + heightCollider / 2; }
	float GetLeftCollider() const { return position.x - widthCollider / 2; }
	float GetRightCollider() const { return position.x + widthCollider / 2; }
	float GetCenterX() const { return position.x; }
	float GetCenterY() const { return position.y; }

	Maths::Vector2f GetPosition() const { return position; }
	void SetPosition(const Maths::Vector2f& _position) { position = _position; }

	Maths::Vector2f GetPerfectPosition() const { return perfectPosition; }
	void SetPerfectPosition(const Maths::Vector2f& _perfectPosition) { perfectPosition = _perfectPosition; }

	void SetShow(const bool& _show) { show = _show; }
	void SetActiveCollider(const bool& _activeCollider) { activeCollider = _activeCollider; }
	bool GetActiveCollider() const { return activeCollider; }

	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;
private:
	float widthCollider = 0.f;
	float heightCollider = 0.f;
	Maths::Vector2f position = Maths::Vector2f::Zero;
	Maths::Vector2f perfectPosition = Maths::Vector2f::Zero;
	bool show = false;
	bool activeCollider = true;
};


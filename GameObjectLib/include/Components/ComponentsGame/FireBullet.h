#pragma once
#include "Component.h"
#include "Components/Animation.h"
#include "Components/RigidBody2D.h"
class FireBullet : public Component
{
public:
	enum Direction { Left, Right };

	FireBullet();
	void Update(const float& _delta) override;

	inline void SetSpeed(const float& _speed) { speed = _speed; }
	inline float GetSpeed() const { return speed; }

	void AddAnimation(const std::string& _name, Animation* animation);
	Animation* GetAnimation(const std::string& _name);
	Animation* GetAndSetAnimation(const std::string& _name);
	inline Animation* GetActualAnimation() const { return actualAnimation; }
	inline void SetActualAnimation(Animation* animation) { actualAnimation = animation; }

	void SetDirection(Direction _newDirection);
	void Collision();

private:
	float speed = 330.f;
	std::map<std::string, Animation*> animations;
	Animation* actualAnimation = nullptr;
	bool directionFireBullet;
	Direction direction;
};


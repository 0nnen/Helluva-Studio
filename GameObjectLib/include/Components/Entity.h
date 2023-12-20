#pragma once
#include "Component.h"
#include "Components/Animation.h"

class Entity : public Component
{
public:
	Entity();
	explicit Entity(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range);

	enum Direction { Left, Right };

	inline int GetHealthPoint() const { return healthPoint; }
	inline int GetMaxHealthPoint() const { return maxHealthPoint; }
	inline int GetDamage() const { return damage; }
	inline float GetSpeed() const { return speed; }
	inline float GetMaxSpeed() const { return maxSpeed; }
	inline float GetAttackSpeed() const { return attackSpeed; }
	inline float GetRange() const { return range; }

	inline void SetHealthPoint(const int& _hp) { healthPoint = _hp; }
	inline void SetMaxHealthPoint(const int& _maxHp) { maxHealthPoint = _maxHp; }
	inline void SetDamage(const int& _damage) { damage = _damage; }
	inline void SetSpeed(const float& _speed) { speed = _speed; }
	inline void SetMaxSpeed(const float& _maxSpeed) { maxSpeed = _maxSpeed; }
	inline void SetAttackSpeed(const float& _attackspeed) { attackSpeed = _attackspeed; }
	inline void SetRange(const float& _range) { range = _range; }

	inline int GetCurrPathPoint() { return currPathPoint; }

	inline void SetLane(const int& newLane) { lane = newLane; }
	inline int GetLane() { return lane; }

	inline void IncrementCount() { count++; }
	inline void ResetCount() { count = 0; }
	inline int GetCount() { return count; }

	void SetDirection(Direction _newDirection);

	void TakeDamage(const int& damage);
	void TakeHealt(const int& _healt) { healthPoint += _healt; }
	virtual void Die();
	void Update(const float& _delta) override;

	inline bool GetOnFloor() const { return onFloor; }
	inline void SetOnFloor(const bool& _state) { onFloor = _state; }

	inline void SetInvicible(const bool& _state) { isInvicible = _state; }
	inline bool GetInvicible() const { return isInvicible; }

	inline void SetFiring(const bool& _state) { isFiring = _state; }
	inline bool GetFiring() const { return isFiring; }


	void AddAnimation(const std::string& _name, Animation* animation);
	Animation* GetAnimation(const std::string& _name);
	Animation* GetAndSetAnimation(const std::string& _name);
	inline Animation* GetActualAnimation() const { return actualAnimation; }
	inline void SetActualAnimation(Animation* animation) { actualAnimation = animation; }

protected:
	int currPathPoint = 0;
	int count = 0;

	int healthPoint;
	int maxHealthPoint;
	int damage;
	int lane;
	float speed;
	float maxSpeed;
	float attackSpeed;
	float range;
	bool onFloor = true;
	bool isInvicible = false;
	bool isFiring = false;
	Animation* actualAnimation = nullptr;
	std::map<std::string, Animation*> animations;
	Direction direction;
	bool directionEnemy;

};

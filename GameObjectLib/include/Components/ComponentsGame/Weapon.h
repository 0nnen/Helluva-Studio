#pragma once
#include "Component.h"

class Weapon : public Component
{
public:
	enum TypeWeapon { DefaultWeapon, Gun, Sword };
	void Update(const float& _delta);
	inline float GetDamage() const { return damage; }
	inline void SetDamage(const float& _damage) { damage = _damage; }

	inline float GetRange() const { return range; }
	inline void SetRange(const float& _range) { range = _range; }

	inline float GetCooldown() const { return cooldown; }
	inline void SetCooldown(const float& _cooldown) { cooldown = _cooldown; }

	inline float GetAttackSpeed() const { return attackSpeed; }
	inline void SetAttackSpeed(const float& _attackSpeed) { attackSpeed = _attackSpeed; }

	inline size_t GetIndexWeapon() const { return indexInventory; }
	inline void SetIndexWeapon(const size_t& _indexInventory) { indexInventory = _indexInventory; }
	
	inline TypeWeapon GetTypeWeapon() const { return typeWeapon; }
	inline void SetAttackSpeed(const TypeWeapon& _typeWeapon) { typeWeapon = _typeWeapon; }

	virtual void Attack();

protected:
	float damage = 0.f;
	float range = 0.f;
	float cooldown = 0.f;
	float attackSpeed = 0.f;
	size_t indexInventory = 0;
	TypeWeapon typeWeapon = DefaultWeapon;
};


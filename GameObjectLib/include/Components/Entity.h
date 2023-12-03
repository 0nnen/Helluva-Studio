#pragma once
#include "Component.h"
class Entity : public Component
{
public:
    Entity();
    explicit Entity(const int& _hp, const int& _damage, const int& _lane, const float& _speed , const float& _attackSpeed, const float& _range);

    inline int GetHealthPoint() const { return healthPoint; }
    inline int GetMaxHealthPoint() const { return maxHealthPoint; }
    inline int GetDamage() const { return damage; }
    inline float GetSpeed() const { return speed; }
    inline float GetAttackSpeed() const { return attackSpeed; }
    inline float GetRange() const { return range; }

    inline void SetHealthPoint(const int& _hp)  { healthPoint = _hp;}
    inline void SetMaxHealthPoint(const int& _maxHp)  { maxHealthPoint = _maxHp;}
    inline void SetDamage(const int& _damage)  { damage = _damage; }
    inline void SetSpeed(const float& _speed)  {  speed = _speed; }
    inline void SetAttackSpeed(const float& _attackspeed) { attackSpeed = _attackspeed; }
    inline void SetRange(const float& _range) { range = _range; }

    void MoveToPoint(const Maths::Vector2i& point, const float& speed);
    void SetCurrPathPoint(const int& newPathPoint);
    inline int GetCurrPathPoint() { return currPathPoint; }
    
    inline void SetLane(const int& newLane) { lane = newLane; }
    inline int GetLane() { return lane; }

    inline void IncrementCount() { count++; }
    inline void ResetCount() { count = 0; }
    inline int GetCount() { return count; }

    void TakeDamage(const int& damage);
    virtual void Die();
    void Update(const float& _delta) override;

protected:
    int currPathPoint = 0;
    int count = 0;

    int healthPoint;
    int maxHealthPoint;
    int damage;
    int lane;
    float speed;
    float attackSpeed;
    float range;
};

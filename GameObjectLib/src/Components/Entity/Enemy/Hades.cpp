#include "Components/Entity/Enemy/Hades.h"


Hades::Hades() : Entity() 
{
   
}
Hades::Hades(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range) : Entity(_hp, _damage, _speed, _attackSpeed, _range) 
{
 
}

void Hades::Update(const float& _delta)
{
    Entity::Update(_delta);
    GameObject* hades = GetOwner();
    if(protection) protection->SetPosition(hades->GetPosition());
   
    if (state == Hades::State::Idle)
    {
        if (!GetAnimation("idle")->GetIsPlaying()) {
            GetAnimation("roar")->Stop();
            GetAnimation("attack")->Stop();
            GetAnimation("idle")->Play();
        }
    }
    else if (state == Hades::State::Move)
    {
        if (!GetAnimation("idle")->GetIsPlaying()) {
            GetAnimation("roar")->Stop();
            GetAnimation("attack")->Stop();
            GetAnimation("idle")->Play();
        }
    }
    else if (state == Hades::State::Attack)
    {
        if (!GetAnimation("attack")->GetIsPlaying()) {
            GetAnimation("idle")->Stop();
            GetAnimation("roar")->Stop();
            GetAnimation("attack")->Play();
        }
    }
    else if (state == Hades::State::Roar)
    {
        if (!GetAnimation("roar")->GetIsPlaying()) {
            GetAnimation("idle")->Stop();
            GetAnimation("attack")->Stop();
            GetAnimation("roar")->Play();
        }
    }
    
    if (balls.size() == 0) SetProtection();
    if (healthPoint > maxHealthPoint * 66 / 100) step = Step1;
    else if (healthPoint > maxHealthPoint * 33 / 100 && healthPoint  < maxHealthPoint * 66 / 100) step = Step2;
    else step = Step3;

}
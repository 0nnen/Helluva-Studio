#pragma once
#include "Component.h"
#include "Managers/AssetManager.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Components/Animation.h"
class LavaArea : public Component
{
public:
	LavaArea();
	void Update(const float& _delta);
	~LavaArea();
	void Render(sf::RenderWindow* _window);
	void AddAnimation(const std::string& _name, Animation* animation);
	Animation* GetAnimation(const std::string& _name);
	Animation* GetAndSetAnimation(const std::string& _name);
	inline Animation* GetActualAnimation() const { return actualAnimation; }
	inline void SetActualAnimation(Animation* animation) { actualAnimation = animation; }


private:
	GameObject* player = nullptr;
	float cooldown = 0.f;
	Animation* actualAnimation = nullptr;
	std::map<std::string, Animation*> animations;
};


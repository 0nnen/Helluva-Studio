#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "Components/SpriteRenderer.h"
class Animation : public Component
{
public:

	Animation();
	void Update(const float& _delta) override;

	void Play();
	inline void Stop() { isPlaying = false; }

	inline void SetName(const std::string& _name) { name = _name; }
	inline std::string GetName() const { return name; }
	inline void SetFrame(const unsigned int _frame) { totalFrame = _frame; }
	inline unsigned int GetFrame() const { return totalFrame; }

	inline int GetActualLoop() const { return actualLoop; }
	inline int GetTotalLoop() const { return totalLoop; }
	void SetLoop(const int& _loop);

	void SetSpriteSheet(sf::Texture* _spriteSheet);
	inline void SetAnimationTime(const float& _animationTime) { animationTime = _animationTime; }

	
private:
	Sprite* sprite = nullptr;
	std::string name = "Animation";
	sf::Texture* spriteSheet = nullptr;

	unsigned int totalFrame = 0;
	unsigned int actualFrame = 0;
	int totalLoop = 1;
	int actualLoop = 0;
	float animationTime = 3.f;
	float actualTime = 0.f;
	bool isPlaying = true;

};


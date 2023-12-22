#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "Components/SpriteRenderer.h"

class Animation : public Component
{
public:

	void Update(const float& _delta) override;

	void Play();
	void Play(const std::string& _nameSprite);
	inline void Stop() {
		isPlaying = false; 
		if(sprite) sprite->SetActiveAndVisible(false);
	}

	inline void SetFrame(const unsigned int _frame) { totalFrame = _frame; }
	inline unsigned int GetFrame() const { return totalFrame; }

	inline void SetSprite(Sprite* _sprite) { sprite = _sprite; }
	inline Sprite* GetSprite() const { return sprite; }

	inline bool GetIsPlaying() const { return isPlaying; }
	inline int GetActualLoop() const { return actualLoop; }
	inline int GetTotalLoop() const { return totalLoop; }
	void SetLoop(const int& _loop);

	void SetSpriteSheet(sf::Texture* _spriteSheet);
	inline void SetAnimationTime(const float& _animationTime) { animationTime = _animationTime; }

	inline int GetWidth() { return width; }
	inline int GetHeight() { return height; }
private:
	Sprite* sprite = nullptr;
	sf::Texture* spriteSheet = nullptr;

	std::string spriteName = "spriteName";
	int width, height;
	unsigned int totalFrame = 0;
	unsigned int actualFrame = 0;
	int totalLoop = 1;
	int actualLoop = 0;
	float animationTime = 3.f;
	float actualTime = 0.f;
	bool isPlaying = false;

};


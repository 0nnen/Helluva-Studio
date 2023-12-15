#pragma once
#include "Scene.h"

class SceneOpening : public Scene
{
public:
	SceneOpening();
	SceneOpening(const std::string& _name);
	virtual ~SceneOpening() = default;


	 void Create() override;
	 void Preload() override;
	 void Delete() override;
	 void Update(const float& _delta) override;
	 void Render(sf::RenderWindow* _window) override;

	void Awake();


private:
	float timeLogoStudio = 3.0;
	float timeLogoGame = 3.0;
	std::vector<sf::Sprite*> sprites;

	float actualTime = 0.f;
	float pauseTime = 1.f;
	bool isPauseTime = false;
	int actualSprite = 0;

	sf::RectangleShape progressBar;
	float progressBarFill = 0.0f;
	const float fillRate = 0.5f;

};


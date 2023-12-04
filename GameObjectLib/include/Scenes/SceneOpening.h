#pragma once

#include "Scene.h"
class SceneOpening : public Scene
{
	SceneOpening();
	SceneOpening(const std::string& _name);
	virtual ~SceneOpening() = default;


	 void Create();
	 void Delete();
	 void Update(const float& _delta);
	 void Render(sf::RenderWindow* _window);

	void Awake();


private:
	float timeLogoStudio = 3.0;
	float timeLogoGame = 3.0;
};


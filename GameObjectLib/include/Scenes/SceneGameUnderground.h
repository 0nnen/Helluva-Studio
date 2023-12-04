#pragma once

#include "Scenes/SceneGameAbstract.h"
class SceneGameUnderground : public SceneGameAbstract
{
public:
	SceneGameUnderground(const std::string& _newName);


	void Preload() override;
	void Create() override;
	void Delete() override;
	void Render(sf::RenderWindow* _window) override;
	void Update(const float& _delta) override;
};


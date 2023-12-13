#pragma once
#include "Scenes/SceneGameAbstract.h"
class SceneGameBossRoom final : public SceneGameAbstract
{
public:
	SceneGameBossRoom();
	SceneGameBossRoom(const std::string& _name);
	void Awake() override;
	void Create() override;
	void Preload() override;
	void Delete() override;
	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;

private:
	GameObject* plateforme = nullptr;
};


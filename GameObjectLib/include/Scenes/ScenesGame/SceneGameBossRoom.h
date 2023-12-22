#pragma once
#include "Scenes/SceneGameAbstract.h"
#include "Components/UIElements/ATH.h"

class SceneGameBossRoom final : public SceneGameAbstract
{
public:
	SceneGameBossRoom();
	~SceneGameBossRoom();
	SceneGameBossRoom(const std::string& _name);
	void Awake() override;
	void Create() override;
	void Preload() override;
	void Delete() override;
	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;

	GameObject* GetHades() {return hades ;}

	inline void KillHades() { delete hades; }

private:
	GameObject* plateforme = nullptr;
	GameObject* wallRight = nullptr;
	GameObject* wallLeft = nullptr;
	GameObject* ceiling = nullptr;
	GameObject* textDialogue = nullptr;
	float victoryTime = 3.f;

	bool textActive = false;
};


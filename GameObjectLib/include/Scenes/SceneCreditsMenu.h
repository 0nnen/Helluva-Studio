#pragma once
#include "Scene.h"
#include "SceneGameAbstract.h"

class SceneCreditsMenu : public Scene
{
public:
	SceneCreditsMenu(const std::string& _newName);

	void CreateSceneButtonsMenu();
	void LoadCreditsTexture();

	GameObject* CreateCreditsGameObject(const std::string& name, const float& positionx, const float& positiony, const sf::Texture& texture, const float& scalex, const float& scaley);

	void AnimCredits(const float& _deltaSeconds, const float& _iteration, const int& _totalLoop);

	void SetOrigin();

	void Create() override;
	void Render(sf::RenderWindow* _window) override;
	void Update(const float& _delta) override;

private:
	GameObject* creditsButton = nullptr;
	GameObject* backButton = nullptr;
	GameObject* credits = nullptr;
	std::vector<GameObject*> imagesCredits;
	std::vector<GameObject*> texteCredits;
	std::vector<std::string> allTexteCredits = {
		"Game Master : LAHALLE François\nDéveloppeur : LAHALLE François\n",
		"Développeur : LEFORESTIER Quentin\nDiagramme Production : LEFORESTIER Quentin",
		"Développeur : Maurad",
		"Développeur : DIFALLAH Kaïs\nDiagramme Production : DIFALLAH Kaïs",
		"Développeur : ROY Hugo",
		"Développeur : BRU Arthur\nSound Production : BRU Arthur\nAssets Production : BRU Arthur"
	};
	sf::Text text;

	float deltaSeconds = 0.f;
	float iteration = 2.f;
	int totalLoop = 1;
	bool goodPosCredits;
	float startPosFrancoisX; //Tutur tu abuses
	float startPosFrancoisY;
};



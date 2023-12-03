#pragma once
#include "Scene.h"
class SceneLoginSignup : public Scene
{
public:
	SceneLoginSignup(const std::string& _newName);
	void Create() override;
	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;

private:
	GameObject* loginName;
	GameObject* loginPassWord;
	GameObject* buttonLogin;

	GameObject* signupName;
	GameObject* signupPassWord;
	GameObject* buttonSignup;

	GameObject* buttonReturn;
};


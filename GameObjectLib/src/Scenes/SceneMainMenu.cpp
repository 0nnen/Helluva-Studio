#include "Scenes/SceneMainMenu.h"
#include "Components/UIElements/Button.h"
#include "Components/UIElements/Slider.h"
#include "Managers/AudioManager.h"
#include "Managers/WindowManager.h"
#include "Managers/AssetManager.h"
#include "Components/SpriteRenderer.h"

#include "BuilderGameObject.h"

SceneMainMenu::SceneMainMenu(const std::string& _newName) : Scene(_newName)
{
}

void SceneMainMenu::Preload()
{
	AssetManager::AddAsset("BackgroundMainMenu", "../Assets/bgMenu.png");
	AssetManager::AddAsset("Buttons", "../Assets/buttons.png");
}

void SceneMainMenu::Create()
{
	Scene::Create();
	GameObject* background1 = BuilderGameObject::CreateBackgroundGameObject("BackgroundMenu", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, 1.0f, 1.0f, AssetManager::GetAsset("BackgroundMainMenu"));
	this->CreateSceneButtonsMenu();
	this->ActiveOption(false);
	this->ActiveMenu(true);

}
void SceneMainMenu::Delete()
{
	Scene::Delete();
}

void SceneMainMenu::Render(sf::RenderWindow* _window)
{
	Scene::Render(_window);
}

void SceneMainMenu::CreateSceneButtonsMenu()
{
	float widthScreen = WindowManager::GetFloatWindowWidth();
	float heightScreen = WindowManager::GetFloatWindowHeight();
	playButton = BuilderGameObject::CreateButtonGameObject("PLAY", widthScreen / 2, heightScreen / 2.1, 0.8f, 0.8f, 0, 0, 1, 3, AssetManager::GetAsset("Buttons"));
	worldButton = BuilderGameObject::CreateButtonGameObject("PLAY WORLD", widthScreen / 2, heightScreen / 1.6, 0.8f, 0.8f, 0, 0, 1, 3, AssetManager::GetAsset("Buttons"));
	optionsButton = BuilderGameObject::CreateButtonGameObject("OPTIONS", widthScreen / 2, heightScreen / 1.3, 0.8f, 0.8f, 0, 0, 1, 3, AssetManager::GetAsset("Buttons"));
	quitButton = BuilderGameObject::CreateButtonGameObject("QUIT", widthScreen / 2, heightScreen / 1.1, 0.8f, 0.8f, 0, 0, 1, 3, AssetManager::GetAsset("Buttons"));

	successButton = BuilderGameObject::CreateButtonGameObject("Success", widthScreen / 1.2, heightScreen / 10, 25);
	rankButton = BuilderGameObject::CreateButtonGameObject("Rank", widthScreen / 1.3, heightScreen / 10, 25);
	creditsButton = BuilderGameObject::CreateButtonGameObject("Credits", widthScreen / 1.1, heightScreen / 10, 25);
	backButton = BuilderGameObject::CreateButtonGameObject("Back", widthScreen / 10, heightScreen / 10, 20);
	sliderFPS = BuilderGameObject::CreateSliderGameObject("SliderFPS", widthScreen / 2, heightScreen / 2, 1200, 40, 50, 50, 20, WindowManager::GetFps(), WindowManager::GetMinFps(), WindowManager::GetMaxFps());
	sliderVolume = BuilderGameObject::CreateSliderGameObject("SliderVolume", widthScreen / 2, heightScreen / 1.5, 1200, 40, 50, 50, 20, AudioManager::GetVolume(), AudioManager::GetMaxVolume());
	//signupLoginButton = CreateButtonGameObject("Signup Login", widthScreen / 1.2, heightScreen / 1.2, 30)

}

void SceneMainMenu::Update(const float& _delta)
{
	Scene::Update(_delta);

	if (playButton->GetComponent<Button>()->IsClicked() || isFadeOut)
	{
		isFadeOut = true;
		if (FadeOut(_delta))
		{
			SceneManager::RunScene("SceneGameWorld");
		}

	}
	else if (worldButton->GetComponent<Button>()->IsClicked())
	{
		SceneManager::RunScene("SceneGameWorld");
	}
	else if (optionsButton->GetComponent<Button>()->IsClicked())
	{
		this->ActiveMenu(false);
		this->ActiveOption(true);
	}
	else if (quitButton->GetComponent<Button>()->IsClicked())
	{
		WindowManager::GetWindow()->close();
	}
	else if (backButton->GetComponent<Button>()->IsClicked())
	{
		optionsButton->GetComponent<Button>()->SetState(Button::StateButton::Normal);
		this->ActiveOption(false);
		this->ActiveMenu(true);
	}
	else if (successButton->GetComponent<Button>()->IsClicked())
	{
		SceneManager::RunScene("SceneSuccessMenu");
	}
	else if (rankButton->GetComponent<Button>()->IsClicked())
	{
		SceneManager::RunScene("SceneRankMenu");
	}
	else if (creditsButton->GetComponent<Button>()->IsClicked())
	{
		SceneManager::RunScene("SceneCreditsMenu");
	}
	if (option)
	{
		if (sliderFPS)
		{
			WindowManager::SetFps(sliderFPS->GetComponent<Slider>()->GetDataInt());
		}
		if (sliderVolume)
		{
			AudioManager::SetVolume(sliderVolume->GetComponent<Slider>()->GetDataInt());
		}
	}

	/*else if (signupLoginButton->GetComponent<Button>()->IsClicked() && signupLoginButton->GetActive())
	{
		SceneManager::RunScene("SceneLoginSignup");
	}*/
}

void SceneMainMenu::ActiveMenu(const bool& _state)
{
	this->playButton->SetActiveAndVisible(_state);
	this->worldButton->SetActiveAndVisible(_state);
	this->optionsButton->SetActiveAndVisible(_state);
	this->quitButton->SetActiveAndVisible(_state);
	this->creditsButton->SetActiveAndVisible(_state);
	this->rankButton->SetActiveAndVisible(_state);
	this->successButton->SetActiveAndVisible(_state);
	//this->signupLoginButton->SetActiveAndVisible(_state);
}

void SceneMainMenu::ActiveOption(const bool& _state)
{
	this->backButton->SetActiveAndVisible(_state);
	this->sliderFPS->SetActiveAndVisible(_state);
	this->sliderVolume->SetActiveAndVisible(_state);
	option = _state;
}

SceneMainMenu::~SceneMainMenu()
{
	this->Delete();
}
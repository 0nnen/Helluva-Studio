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
	texture = nullptr;
	textureBullet = nullptr;
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
	this->activeOption(false);
	this->activeMenu(true);

}
void SceneMainMenu::Delete()
{
	delete texture;
	delete textureBullet;
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
			std::cout << "Switch Scene" << std::endl;
			//SceneManager::RunScene("SceneGameUnderground");
			SceneManager::RunScene("ScenesTest");
		}

	}
	else if (worldButton->GetComponent<Button>()->IsClicked())
	{
		std::cout << "World Scene" << GetName() << std::endl;
		SceneManager::RunScene("SceneGameWorld");
	}
	else if (optionsButton->GetComponent<Button>()->IsClicked())
	{
		std::cout << "Option";
		this->activeMenu(false);
		this->activeOption(true);
	}
	else if (quitButton->GetComponent<Button>()->IsClicked())
	{
		std::cout << "Close";
		WindowManager::GetWindow()->close();

	}
	else if (backButton->GetComponent<Button>()->IsClicked())
	{
		std::cout << "Back";
		optionsButton->GetComponent<Button>()->SetState(Button::StateButton::Normal);
		this->activeOption(false);
		this->activeMenu(true);
	}
	else if (successButton->GetComponent<Button>()->IsClicked())
	{
		std::cout << "Succes";
		SceneManager::RunScene("SceneSuccessMenu");
	}
	else if (rankButton->GetComponent<Button>()->IsClicked())
	{
		std::cout << "Rank";
		SceneManager::RunScene("SceneRankMenu");
	}
	else if (creditsButton->GetComponent<Button>()->IsClicked())
	{
		std::cout << "Credits";
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

void SceneMainMenu::activeMenu(const bool& _state)
{
	this->playButton->SetActive(_state);
	this->worldButton->SetActive(_state);
	this->optionsButton->SetActive(_state);
	this->quitButton->SetActive(_state);
	this->creditsButton->SetActive(_state);
	this->rankButton->SetActive(_state);
	this->successButton->SetActive(_state);
	this->playButton->SetVisible(_state);
	this->worldButton->SetVisible(_state);
	this->optionsButton->SetVisible(_state);
	this->quitButton->SetVisible(_state);
	this->creditsButton->SetVisible(_state);
	this->rankButton->SetVisible(_state);
	this->successButton->SetVisible(_state);
	//this->signupLoginButton->SetActive(_state);
}

void SceneMainMenu::activeOption(const bool& _state)
{
	this->backButton->SetActive(_state);
	this->sliderFPS->SetActive(_state);
	this->sliderVolume->SetActive(_state);
	this->backButton->SetVisible(_state);
	this->sliderFPS->SetVisible(_state);
	this->sliderVolume->SetVisible(_state);
	option = _state;
}

SceneMainMenu::~SceneMainMenu()
{
	this->Delete();
}
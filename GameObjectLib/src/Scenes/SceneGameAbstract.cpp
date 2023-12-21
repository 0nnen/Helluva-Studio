#include "Scenes/SceneGameAbstract.h"

#include "Engine.h"
#include "Managers/SceneManager.h"
#include "Managers/AssetManager.h"
#include "Managers/AudioManager.h"
#include "Managers/WindowManager.h"

#include "Components/UIElements/Button.h"
#include "Components/Shapes/Carre.h"
#include "Components/SpriteRenderer.h"
#include "Components/HealthPointBar.h"

#include "BuilderGameObject.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"
#include <Scenes/ScenesGame/SceneGameWorld.h>


SceneGameAbstract::SceneGameAbstract(const std::string& _newName) : Scene(_newName)
{
	this->Awake();
	srand(time(nullptr));
	isPause = false;
}


SceneGameAbstract::~SceneGameAbstract() 
{
	this->Delete();
}

void SceneGameAbstract::Create() 
{
	Scene::Create();
	//Background Pause
	const float& widthScreen = WindowManager::GetWindowWidth();
	const float& heightScreen = WindowManager::GetWindowHeight();
	backgroundPause = BuilderGameObject::CreateBackgroundGameObject("BackgroundPause", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, Maths::Vector2f(WindowManager::GetWindowWidth(), WindowManager::GetWindowHeight()), 1.f, 1.f, LayerType::HUD, sf::Color(0, 0, 0, static_cast <sf::Uint8>(170)));
	//Pause Buttons
	
	pausePlayButton = BuilderGameObject::CreateButtonGameObject("continue", widthScreen / 2, heightScreen / 3, 0.8f, 0.8f, 0, 0, 1, 3, AssetManager::GetAsset("ButtonsMenu"), 40);
	pauseMenuPrincipalButton = BuilderGameObject::CreateButtonGameObject("mainMenu", widthScreen / 2, heightScreen / 2, 0.8f, 0.8f, 0, 0, 1, 3, AssetManager::GetAsset("ButtonsMenu"), 25);
	pauseQuitButton = BuilderGameObject::CreateButtonGameObject("quit", widthScreen / 2, heightScreen / 1.5, 0.8f, 0.8f, 0, 0, 1, 3, AssetManager::GetAsset("ButtonsMenu"), 40);
	this->Pause(false);
}

void SceneGameAbstract::CreatePlayer()
{
	player = BuilderEntityGameObject::CreateCharacterGameObject("Player", WindowManager::GetWindowWidth() / 2, 600.f, AssetManager::GetAsset("idleCharacter"), 2.f, 2.f);
}

void SceneGameAbstract::CreatePlayer(const float& _positionX, const float& _positionY)
{
	player = BuilderEntityGameObject::CreateCharacterGameObject("Player", _positionX, _positionY, AssetManager::GetAsset("idleCharacter"), 2.f, 2.f);
}

void SceneGameAbstract::Preload()
{
	Scene::Preload();

	AssetManager::AddAsset("BackgroundAbstract", "Assets/Graphics/Backgrounds/bgMenu.png");
	AssetManager::AddAsset("idleCharacter", "Assets/Graphics/Characters/Zephyr/Idle/Character_Idle_48x48.png");
	AssetManager::AddAsset("Character", "Assets/Graphics/Characters/Zephyr/Idle/Character-Idle_01.png");
	AssetManager::AddAsset("jumpCharacter", "Assets/Graphics/Characters/Zephyr/Jump/Character_Jump_48x48.png");
	AssetManager::AddAsset("runCharacter", "Assets/Graphics/Characters/Zephyr/Run/Character_Run_48x48.png");
	AssetManager::AddAsset("shootArm", "Assets/Graphics/Characters/Zephyr/Idle_Shoot/Character_Idle_Shoot_ARM_48x48.png");
	AssetManager::AddAsset("shootBody", "Assets/Graphics/Characters/Zephyr/Idle_Shoot/Character_Idle_Shoot_BODY_48x48.png");
	AssetManager::AddAsset("bullet", "Assets/Graphics/Characters/Zephyr/bullet.png");
	AssetManager::AddAsset("ButtonsMenu", "Assets/Graphics/UI/Buttons/buttonsMenu.png");
}


void SceneGameAbstract::Delete() 
{
	Scene::Delete();
}

void SceneGameAbstract::Pause()
{
	isPause = !isPause;

	this->pausePlayButton->SetActiveAndVisible(isPause);
	this->pauseMenuPrincipalButton->SetActiveAndVisible(isPause);
	this->pauseQuitButton->SetActiveAndVisible(isPause);
	this->backgroundPause->SetActiveAndVisible(isPause);
}

void SceneGameAbstract::Pause(const bool& _state)
{
	isPause = _state;

	this->pausePlayButton->SetActiveAndVisible(_state);
	this->pauseMenuPrincipalButton->SetActiveAndVisible(_state);
	this->pauseQuitButton->SetActiveAndVisible(_state);
	this->backgroundPause->SetActiveAndVisible(_state);
}


void SceneGameAbstract::Awake() 
{
	Scene::Awake();
}

void SceneGameAbstract::Physics(const float& _delta)
{
	if (!isPause)
	{
		Scene::Physics(_delta);
	}
}

void SceneGameAbstract::Update(const float& _delta)
{

	if (!isPause)
	{
		Scene::Update(_delta);
	}
	else
	{
		AudioManager::PauseMusic();
		if (pausePlayButton->GetComponent<Button>()->IsClicked())
		{
			AudioManager::ResumeMusic();
			this->Pause(false);
		}
		else if (pauseMenuPrincipalButton->GetComponent<Button>()->IsClicked()) 
		{
			AudioManager::Stop();
			this->Pause(true);
			SceneManager::RunScene("SceneMainMenu");
		}
		else if (pauseQuitButton->GetComponent<Button>()->IsClicked()) 
		{
			Engine::GetInstance()->Quit();
		}

	}
}

void SceneGameAbstract::Render(sf::RenderWindow* _window) 
{
	Scene::Render(_window);
}

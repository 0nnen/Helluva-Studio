#include "Scenes/SceneGameAbstract.h"

#include "Engine.h"
#include "Managers/SceneManager.h"
#include "Managers/AssetManager.h"
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
	//Pause Buttons
	pausePlayButton = BuilderGameObject::CreateButtonGameObject("Continue", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 4.0, 25);
	pauseMenuPrincipalButton = BuilderGameObject::CreateButtonGameObject("Menu Principal", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2.5, 15);
	pauseQuitButton = BuilderGameObject::CreateButtonGameObject("Quit", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 1.8,  40);
	this->ManageDefaultButtonsPause(false);
	//Background Pause
	backgroundAlpha1.backgroundAlpha.setSize(sf::Vector2f(WindowManager::GetFloatWindowWidth(), WindowManager::GetFloatWindowHeight()));
	backgroundAlpha1.backgroundAlpha.setOrigin(sf::Vector2f(WindowManager::GetFloatWindowWidth() / 2, WindowManager::GetFloatWindowHeight() / 2));
	backgroundAlpha1.backgroundAlpha.setFillColor(sf::Color(0, 0, 0, 112));
	backgroundAlpha1.backgroundAlpha.setPosition(WindowManager::GetFloatWindowWidth() / 2, WindowManager::GetFloatWindowHeight() / 2);
	backgroundAlpha2.backgroundAlpha.setSize(sf::Vector2f(WindowManager::GetFloatWindowWidth(), WindowManager::GetFloatWindowHeight()));
	backgroundAlpha2.backgroundAlpha.setOrigin(sf::Vector2f(WindowManager::GetFloatWindowWidth() / 2, WindowManager::GetFloatWindowHeight() / 2));
	backgroundAlpha2.backgroundAlpha.setFillColor(sf::Color::Transparent);
	backgroundAlpha2.backgroundAlpha.setPosition(WindowManager::GetFloatWindowWidth() / 2, WindowManager::GetFloatWindowHeight() / 2);
	//Background
	//GameObject* background1 = BuilderGameObject::CreateBackgroundGameObject("Background1", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, 1.0f, 1.0f, AssetManager::GetAsset("BackgroundAbstract"));
	//Player
	
}

void SceneGameAbstract::CreatePlayer()
{
	player = BuilderEntityGameObject::CreateCharacterGameObject("Player", WindowManager::GetWindowWidth() / 2, 600.f, AssetManager::GetAsset("idleCharacter"), 4.f, 4.f);
}

void SceneGameAbstract::CreatePlayer(const float& _positionX, const float& _positionY)
{
	player = BuilderEntityGameObject::CreateCharacterGameObject("Player", _positionX, _positionY, AssetManager::GetAsset("Character"), 4.f, 4.f);
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
}

void SceneGameAbstract::Awake() 
{
	Scene::Awake();
}

void SceneGameAbstract::ManageDefaultButtonsPause(bool _state)
{
	this->pauseMenuPrincipalButton->SetActiveAndVisible(_state);
	this->pausePlayButton->SetActiveAndVisible(_state);
	this->pauseQuitButton->SetActiveAndVisible(_state);
}


void SceneGameAbstract::Update(const float& _delta)
{

	if (!isPause)
	{
		Scene::Update(_delta);
	}
	else
	{
		if (pausePlayButton->GetComponent<Button>()->IsClicked())
		{
			isPause = false;
			this->ManageDefaultButtonsPause(false);
		}
		else if (pauseMenuPrincipalButton->GetComponent<Button>()->IsClicked()) 
		{
			isPause = true;
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
	_window->draw(!isPause ? backgroundAlpha2.backgroundAlpha : backgroundAlpha1.backgroundAlpha);
	_window->setView(_window->getDefaultView());
}

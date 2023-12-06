#include "Scenes/SceneGameAbstract.h"

#include "Managers/SceneManager.h"
#include "Managers/AssetManager.h"
#include "Managers/WindowManager.h"

#include "Components/UIElements/Button.h"
#include "Components/Shapes/Carre.h"
#include "Components/SpriteRenderer.h"
#include "Components/HealthPointBar.h"

#include "BuilderGameObject.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"


SceneGameAbstract::SceneGameAbstract(const std::string& _newName) : Scene(_newName)
{
	this->Awake();
	srand(time(nullptr));
}


SceneGameAbstract::~SceneGameAbstract() 
{
	this->Delete();
}

void SceneGameAbstract::Create() 
{
	Scene::Create();
	this->CreateChartacter();
	this->CreatePauseMenuButtons();
}

void SceneGameAbstract::Delete() 
{
	Scene::Delete();
}


void SceneGameAbstract::CreatePauseMenuButtons() 
{
	pausePlayButton = BuilderGameObject::CreateButtonGameObject("Continue", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 4.0, 50);
	pauseMenuPrincipalButton = BuilderGameObject::CreateButtonGameObject("Menu Principal", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2.5, 50);
	//pauseOptionsButton = BuilderGameObject::CreateButtonGameObject("Options", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 1.8, 50);
	pauseQuitButton = BuilderGameObject::CreateButtonGameObject("Quit", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 1.8, 50);
	this->ManageSceneGameButtonsPause(false);
}


void SceneGameAbstract::CreateChartacter()
{
	AssetManager::AddAsset("Perso", "../Assets/Character/perso1.png");

	player = BuilderEntityGameObject::CreateCharacterGameObject("Player", WindowManager::GetWindowWidth() / 2, 50.f, *AssetManager::GetAsset("Perso"), 0.25f, 0.25f);
}

void SceneGameAbstract::PauseTest()
{ 
	isPause = !isPause;
	std::cout << isPause;
	pausePlayButton->SetActive(isPause);
	pausePlayButton->SetVisible(isPause);
	pauseMenuPrincipalButton->SetActive(isPause);
	pauseMenuPrincipalButton->SetVisible(isPause);
	pauseQuitButton->SetActive(isPause);
	pauseQuitButton->SetVisible(isPause);
}

void SceneGameAbstract::Awake() 
{
	Scene::Awake();
}

void SceneGameAbstract::ManageSceneGameButtonsPause(bool _state) 
{
	this->pauseMenuPrincipalButton->SetActive(_state);
	this->pausePlayButton->SetActive(_state);
	//this->pauseOptionsButton->SetActive(_state);
	this->pauseQuitButton->SetActive(_state);
}

void SceneGameAbstract::ManagePause()
{
	this->ManageSceneGameButtonsPause(!isActive);
	for (GameObject* enemy : this->enemies)
	{
		enemy->SetActive(isActive);
	}
}

void SceneGameAbstract::Update(const float& _delta) 
{
	this->ManagePause();
	if (isActive)
	{
		Scene::Update(_delta);
	}
	else
	{
		if (pausePlayButton->GetComponent<Button>()->IsClicked())
		{
			this->ManagePause();
			isActive = true;
		}
		else if (pauseMenuPrincipalButton->GetComponent<Button>()->IsClicked()) 
		{
			this->ManagePause();
			SceneManager::RunScene("SceneMainMenu");
		}
		//else if (pauseOptionsButton->GetComponent<Button>()->IsClicked()) 
		//{
		//	std::cout << "Options" << std::endl;
		//}
		else if (pauseQuitButton->GetComponent<Button>()->IsClicked()) 
		{
			WindowManager::GetWindow()->close();
		}
	}
}

void SceneGameAbstract::Render(sf::RenderWindow* _window) 
{
	Scene::Render(_window);
}
void SceneGameAbstract::CreateBackground()
{
	sf::Texture backgroundTexture1;

	if (!backgroundTexture1.loadFromFile("../assets/Sprite/background/background_color.png"))
	{
		std::cout << "pas d'image" << std::endl;
	}
	GameObject* background1 = BuilderGameObject::CreateBackgroundGameObject("Background1", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, backgroundTexture1);
};
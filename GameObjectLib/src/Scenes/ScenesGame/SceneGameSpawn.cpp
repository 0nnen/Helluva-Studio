#include "Scenes/ScenesGame/SceneGameSpawn.h"

#include "Managers/AssetManager.h"
#include "Managers/WindowManager.h"

#include "Components/Inputs/InputCharacter.h"
#include "Components/RigidBody2D.h"
#include "Components/UIElements/Text.h"
#include "Components/Entity/Enemy/Hades.h"
#include "Components/Entity/Character.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "BuilderGameObject.h"


SceneGameSpawn::SceneGameSpawn(const std::string& _newName) : SceneGameAbstract(_newName) {}
SceneGameSpawn::~SceneGameSpawn() {}

void SceneGameSpawn::Awake() 
{
	SceneGameAbstract::Awake();
}
void SceneGameSpawn::Preload() 
{
	SceneGameAbstract::Preload();
	AssetManager::AddAsset("BackgroundBoss", "Assets/Graphics/Maps/bossRoom.png");
	AssetManager::AddAsset("roarHades", "Assets/Enemy/Hades/demon-attack-no-breath.png");
	AssetManager::AddAsset("idleHades", "Assets/Enemy/Hades/demon-idle.png");
	AssetManager::AddAsset("NightmareGalloping", "Assets/Enemy/Nightmare/nightmare-galloping.png");
}

void SceneGameSpawn::Create() 
{
	SceneGameAbstract::Create();
	GameObject* backgroundBossRoom = BuilderGameObject::CreateBackgroundGameObject("BossRoom", WindowManager::GetFloatWindowWidth() / 2, WindowManager::GetFloatWindowHeight() / 2, 1, 1, AssetManager::GetAsset("BackgroundBoss"));
	CreatePlayer(1800.f, 1000.f);
	player->GetComponent<InputCharacter>()->SetActiveAndVisible(false);
	player->GetComponent<Character>()->SetCenterCamera(false);
	player->SetVisible(true);
	player->GetComponent<RigidBody2D>()->SetIsGravity(false);
	
	hades = BuilderEntityGameObject::CreateHadesSpawnGameObject("Hades", WindowManager::GetFloatWindowWidth() / 2.f, WindowManager::GetFloatWindowHeight() / 4.f, 2.5f, 2.5f, AssetManager::GetAsset("idleHades"));
	hades->GetComponent<Hades>()->SetActive(false);

	textDialogue = BuilderGameObject::CreateTextDialogueGameObject(
		"Hades", 
		"Oh!", 
		WindowManager::GetFloatWindowWidth() / 2, 
		WindowManager::GetFloatWindowHeight() / 1.1,
		WindowManager::GetFloatWindowWidth() / 1.2,
		WindowManager::GetFloatWindowHeight() / 6,
		20,
		sf::Text::Regular,
		sf::Color::White
	);

	textDialogue->GetComponent<Text>()->LoadTextFromFile("Assets/Texts/" + language + "/SpawnPlayer.txt");
	
}
void SceneGameSpawn::Delete() 
{
	SceneGameAbstract::Delete();
}

void SceneGameSpawn::Physics(const float& _delta) 
{
	SceneGameAbstract::Physics(_delta);
}

void SceneGameSpawn::Update(const float& _delta) 
{
	SceneGameAbstract::Update(_delta);
	if (isPause)
	{
		textDialogue->SetVisible(false);
	}
	else
	{
		textDialogue->SetVisible(true);
	}

	if (!textDialogue->GetActive())
	{
		isFadeOut = true;
		if (FadeOut(_delta))
		{
			SceneManager::RunScene("ScenesTest");
		}
	}
}

void SceneGameSpawn::Render(sf::RenderWindow* _window) 
{
	SceneGameAbstract::Render(_window);

}
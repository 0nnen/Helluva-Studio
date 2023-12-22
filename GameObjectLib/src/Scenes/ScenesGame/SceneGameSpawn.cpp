#include "Scenes/ScenesGame/SceneGameSpawn.h"

#include "Managers/AssetManager.h"
#include "Managers/WindowManager.h"
#include "Managers/AudioManager.h"

#include "Components/Inputs/InputCharacter.h"
#include "Components/RigidBody2D.h"
#include "Components/UIElements/Text.h"
#include "Components/UIElements/Button.h"
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
	AssetManager::AddAsset("spawnPlateform", "Assets/Graphics/Backgrounds/SceneGame/plateformeSpawn.png");
}

void SceneGameSpawn::Create()
{
	startText = false;
	AudioManager::PlayMusic("MusicAmbiant_HOM");
	SceneGameAbstract::Create();
	skipButton = BuilderGameObject::CreateButtonGameObject("skip", WindowManager::GetFloatWindowWidth() / 1.1f, WindowManager::GetFloatWindowHeight() / 10, 0.8f, 0.8f, 0, 0, 1, 3, AssetManager::GetAsset("ButtonsMenu"), 40);
	skipButton->SetVisible(false);
	
	GameObject* backgroundBossRoom = BuilderGameObject::CreateBackgroundGameObject("BossRoom", WindowManager::GetFloatWindowWidth() / 2, WindowManager::GetFloatWindowHeight() / 2, 1, 1, AssetManager::GetAsset("BackgroundBoss"));
	plateform = BuilderEntityGameObject::CreateRectangleSpriteGameObject("Spawn", "spawnPlateform", 500, 600, 0.5f, 0.5f, AssetManager::GetAsset("spawnPlateform"));
	CreatePlayer(500.f, -500.f);
	player->GetComponent<InputCharacter>()->SetActiveAndVisible(false);
	player->GetComponent<Character>()->SetCenterCamera(false);
	player->GetComponent<ATH>()->SetActiveAndVisible(false);
	
	hades = BuilderEntityGameObject::CreateHadesSpawnGameObject("Hades", WindowManager::GetFloatWindowWidth() / 2.f, WindowManager::GetFloatWindowHeight() / 4.f, 2.5f, 2.5f, AssetManager::GetAsset("idleHades"));
	hades->GetComponent<Hades>()->SetActive(false);

	textDialogue = BuilderGameObject::CreateTextDialogueGameObject(
		"Hades", 
		"Oh! Oh! Ooooohhhhhh!",
		WindowManager::GetFloatWindowWidth() / 2, 
		WindowManager::GetFloatWindowHeight() / 1.1,
		WindowManager::GetFloatWindowWidth() / 1.2,
		WindowManager::GetFloatWindowHeight() / 6,
		20,
		sf::Text::Regular,
		sf::Color::White
	);

	textDialogue->GetComponent<Text>()->LoadTextFromFile("Assets/Texts/" + language + "/SpawnPlayer.txt");
	textDialogue->SetActiveAndVisible(false);
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
	if (!isPause && !startText)
	{
		if (player && plateform)
		{
			SquareCollider* squareColliderPlayer = player->GetComponent<SquareCollider>();
			SquareCollider* squareColliderPlateforme = plateform->GetComponent<SquareCollider>();
			RigidBody2D* rigidBody2DPlayer = player->GetComponent<RigidBody2D>();
			if (SquareCollider::IsColliding(*squareColliderPlayer, *squareColliderPlateforme))
			{
				rigidBody2DPlayer->SetIsGravity(false);
				textDialogue->SetActiveAndVisible(true);
				startText = true;
				skipButton->SetVisible(true);
				const float distanceY = std::abs(squareColliderPlayer->GetCenterY() - squareColliderPlateforme->GetCenterY());
				const float height = squareColliderPlayer->GetHeightCollider() / 2 + squareColliderPlateforme->GetHeightCollider() / 2;
				const float difference = height - distanceY;
				player->SetPosition(player->GetPosition() - Maths::Vector2f(0, difference - 30));
				rigidBody2DPlayer->SetVelocity(Maths::Vector2f(rigidBody2DPlayer->GetVelocity().x, 0));
			}
		}
	}
	if (startText)
	{
		if (!textDialogue->GetActive())
		{
			textDialogue->SetVisible(false);
			isFadeOut = true;
			if (FadeOut(_delta))
			{
				SceneManager::RunScene("SceneGameOverworld");
			}
		}
		else
		{
			if (isPause)
			{
				textDialogue->SetVisible(false);
				skipButton->SetVisible(false);
			}
			else
			{
				textDialogue->SetVisible(true);
				skipButton->SetVisible(true);
				if (skipButton->GetComponent<Button>()->IsClicked() && skipButton->GetVisible())
				{
					textDialogue->SetActive(false);
				}
			}
		}
	}

}

void SceneGameSpawn::Render(sf::RenderWindow* _window) 
{
	SceneGameAbstract::Render(_window);

}
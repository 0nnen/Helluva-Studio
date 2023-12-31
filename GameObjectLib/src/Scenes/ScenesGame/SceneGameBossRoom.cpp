#include "Scenes/ScenesGame/SceneGameBossRoom.h"
#include "BuilderGameObject.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "BuildersGameObject/BuilderShapeGameObject.h"
#include "Managers/AudioManager.h"
#include "Managers/CameraManager.h"
#include "Managers/AssetManager.h"
#include "Managers/WindowManager.h"
#include "Components/Entity/Character.h"
#include "Components/Entity/Enemy/Hades.h"
#include "Components/Entity/Enemy/ProtectionBall.h"
#include "Components/ComponentsGame/WeaponsContainer.h"
#include "Components/ComponentsGame/Gun.h"
#include "Components/ComponentsGame/Bullet.h"
#include "Components/SquareCollider.h"
#include "Components/UIElements/Text.h"

#include <nlohmann/json.hpp>

SceneGameBossRoom::SceneGameBossRoom() : SceneGameAbstract("SceneGameBossRoom") {}
SceneGameBossRoom::SceneGameBossRoom(const std::string& _name) : SceneGameAbstract(_name) {}

void SceneGameBossRoom::Awake()
{
	SceneGameAbstract::Awake();
}


SceneGameBossRoom::~SceneGameBossRoom()
{
	delete plateforme;
}

void SceneGameBossRoom::Preload()
{
	SceneGameAbstract::Preload();

	AudioManager::AddMusic("MusicAmbiant_CI", "Assets/Audio/Musics/MusicAmbiant_CrackerIsland.ogg");

	AudioManager::AddSound("Hades_Scream", "Assets/Audio/SFX/Enemies/Hades/scream.ogg");

	AssetManager::AddAsset("BackgroundBoss", "Assets/Graphics/Maps/bossRoom.png");
	AssetManager::AddAsset("breathHades", "Assets/Enemy/Hades/breath.png");
	AssetManager::AddAsset("breathFireHades", "Assets/Enemy/Hades/breath-fire.png");
	AssetManager::AddAsset("attackHades", "Assets/Enemy/Hades/demon-attack.png");
	AssetManager::AddAsset("roarHades", "Assets/Enemy/Hades/demon-attack-no-breath.png");
	AssetManager::AddAsset("idleHades", "Assets/Enemy/Hades/demon-idle.png");
	AssetManager::AddAsset("protectionHades", "Assets/Enemy/Hades/protection.png");
	AssetManager::AddAsset("NightmareGalloping", "Assets/Enemy/Nightmare/nightmare-galloping.png");
	AssetManager::AddAsset("protectionBallsHades", "Assets/Boss/balls.png");
	AssetManager::AddAsset("lavaArea", "Assets/Graphics/Lava/lava.png");
	unsigned seed = static_cast<unsigned>(time(0));
	srand(seed);

}

void SceneGameBossRoom::Create()
{
	CameraManager::DefaultZoom();
	CameraManager::DefaultCenter();
	SceneGameAbstract::Create();
	AudioManager::PlayMusic("MusicAmbiant_CI");
	GameObject* backgroundBossRoom = BuilderGameObject::CreateBackgroundGameObject("BossRoom", WindowManager::GetFloatWindowWidth() / 2, WindowManager::GetFloatWindowHeight() / 2, 1, 1, AssetManager::GetAsset("BackgroundBoss"));
	plateforme = BuilderEntityGameObject::CreatePlateformGameObject("Plateforme", WindowManager::GetFloatWindowWidth() / 2, WindowManager::GetFloatWindowHeight() + 50.f, 12, 2);
	plateforme->SetVisible(false);
	CreatePlayer(WindowManager::GetFloatWindowWidth() / 1.1, WindowManager::GetFloatWindowHeight() / 1.2);
	player->GetComponent<Character>()->SetCenterCamera(false);


	wallRight = BuilderShapeGameObject::CreateCollisionGameObject("wallRight", WindowManager::GetFloatWindowWidth(), WindowManager::GetFloatWindowHeight() / 2, 20, 1500);
	wallLeft = BuilderShapeGameObject::CreateCollisionGameObject("wallLeft", 0, WindowManager::GetFloatWindowHeight() / 2, 20, 1500);
	ceiling = BuilderShapeGameObject::CreateCollisionGameObject("Ceiling", WindowManager::GetFloatWindowWidth() / 2, 0, 2000, 20);

	hades = BuilderEntityGameObject::CreateHadesGameObject("Hades", WindowManager::GetFloatWindowWidth() / 6.f, WindowManager::GetFloatWindowHeight() / 1.5f, 2.5f, 2.5f, AssetManager::GetAsset("idleHades"));
	victoryTime = 5.f;
}

void SceneGameBossRoom::Delete()
{
	SceneGameAbstract::Delete();
}

void SceneGameBossRoom::Update(const float& _delta)
{
	SceneGameAbstract::Update(_delta);
	if (!isPause)
	{
		RigidBody2D* rigidBody2DPlayer = player->GetComponent<RigidBody2D>();
		Character* character = player->GetComponent<Character>();
		std::vector<SquareCollider*> squareColliders = player->GetComponentsByType<SquareCollider>();
		SquareCollider* squareCollider = squareColliders[0];
		SquareCollider* squareColliderGround = squareColliders[1];
		SquareCollider* squareColliderPlateforme = plateforme->GetComponent<SquareCollider>();

		if (!squareColliderGround->GetActiveCollider())
		{
			if (SquareCollider::IsColliding(*squareCollider, *squareColliderPlateforme))
			{
				character->SetOnFloor(true);
				rigidBody2DPlayer->SetIsGravity(false);
				const float distanceY = std::abs(squareCollider->GetCenterY() - squareColliderPlateforme->GetCenterY());
				const float height = squareCollider->GetHeightCollider() / 2.f + squareColliderPlateforme->GetHeightCollider() / 2.f;
				const float difference = height - distanceY;
				player->SetPosition(player->GetPosition() - Maths::Vector2f(0.f, difference));
				squareColliderGround->SetActiveCollider(true);
				squareCollider->SetActiveCollider(false);
			}
			else
			{
				character->SetOnFloor(false);
				rigidBody2DPlayer->SetIsGravity(true);
			}
		}
		else if (squareColliderGround->GetActiveCollider())
		{

			if (!SquareCollider::IsColliding(*squareColliderGround, *(plateforme->GetComponent<SquareCollider>())))
			{
				squareColliderGround->SetActiveCollider(false);
				squareCollider->SetActiveCollider(true);
				rigidBody2DPlayer->SetIsGravity(true);
				character->SetOnFloor(false);
			}
		}
		if (player && hades)
		{
			Gun* gun = player->GetComponent<WeaponsContainer>()->GetArme()->GetComponent<Gun>();
			if (gun) {
				for (GameObject* bullet : gun->GetBullets())
				{

					if (SquareCollider::IsColliding(*(bullet->GetComponent<SquareCollider>()), *(hades->GetComponent<SquareCollider>())) && hades->GetActive())
					{
						hades->GetComponent<Hades>()->TakeDamage(bullet->GetComponent<Bullet>()->GetDamageReduced());
						gun->RemoveBullet(bullet);
						RemoveGameObject(bullet);
					}
					for (GameObject* protectionBall : hades->GetComponent<Hades>()->GetProtectionBalls())
					{
						if (SquareCollider::IsColliding(*(bullet->GetComponent<SquareCollider>()), *(protectionBall->GetComponent<SquareCollider>())) && hades->GetActive())
						{
							protectionBall->GetComponent<ProtectionBall>()->TakeDamage(bullet->GetComponent<Bullet>()->GetDamageReduced());
							gun->RemoveBullet(bullet);
							RemoveGameObject(bullet);
						}
					}
				}
			}
		}
		if (player)
		{
			//Collision plafond
			SquareCollider* collision = ceiling->GetComponent<SquareCollider>();
			if (SquareCollider::IsColliding(*player->GetComponent<SquareCollider>(), *collision))
			{
				const float distanceY = std::abs(squareCollider->GetCenterY() - collision->GetCenterY());
				const float height = squareCollider->GetHeightCollider() / 2.f + collision->GetHeightCollider() / 2.f;
				const float difference = height - distanceY;
				player->SetPosition(player->GetPosition() + Maths::Vector2f(0.f, difference));
			}

			//Collision mur droite
			collision = wallRight->GetComponent<SquareCollider>();
			if (SquareCollider::IsColliding(*player->GetComponent<SquareCollider>(), *collision))
			{
				const float distanceX = std::abs(squareCollider->GetCenterX() - collision->GetCenterX());
				const float width = squareCollider->GetWidthCollider() / 2.f + collision->GetWidthCollider() / 2.f;
				const float difference = width - distanceX;
				player->SetPosition(player->GetPosition() - Maths::Vector2f(difference, 0.f));
			}

			//Collision mur gauche
			collision = wallLeft->GetComponent<SquareCollider>();
			if (SquareCollider::IsColliding(*player->GetComponent<SquareCollider>(), *collision))
			{
				const float distanceX = std::abs(squareCollider->GetCenterX() - collision->GetCenterX());
				const float width = squareCollider->GetWidthCollider() / 2.f + collision->GetWidthCollider() / 2.f;
				const float difference = width - distanceX;
				player->SetPosition(player->GetPosition() + Maths::Vector2f(difference, 0.f));
			}

			if (player->GetPosition().GetY() > 2000.f)
			{
				player->GetComponent<Character>()->SetHealthPoint(0);
			}
			if (player->GetComponent<Character>()->GetHealthPoint() == 0 && !textActive)
			{
				textActive = true;
				textDialogue = BuilderGameObject::CreateTextDialogueGameObject(
					"Hades",
					"Aaaaaaaaahhhhhhhh!",
					WindowManager::GetFloatWindowWidth() / 2,
					WindowManager::GetFloatWindowHeight() / 1.1,
					WindowManager::GetFloatWindowWidth() / 1.2,
					WindowManager::GetFloatWindowHeight() / 6,
					20,
					sf::Text::Regular,
					sf::Color::White
				);

				textDialogue->GetComponent<Text>()->LoadTextFromFile("Assets/Texts/" + language + "/HadesWin.txt");

			}
		}
		if (hades->GetComponent<Hades>()->GetHealthPoint() == 0 && !textActive)
		{
			hades->SetVisible(true);
			textActive = true;
			textDialogue = BuilderGameObject::CreateTextDialogueGameObject(
				"Hades",
				"Aaaaaaaaahhhhhhhh!",
				WindowManager::GetFloatWindowWidth() / 2,
				WindowManager::GetFloatWindowHeight() / 1.1,
				WindowManager::GetFloatWindowWidth() / 1.2,
				WindowManager::GetFloatWindowHeight() / 6,
				20,
				sf::Text::Regular,
				sf::Color::White
			);

			textDialogue->GetComponent<Text>()->LoadTextFromFile("Assets/Texts/" + language + "/HadesDie.txt");


		}
		if (textDialogue && !textDialogue->GetActive())
		{
			if (victoryTime <= 0.f)
			{
				std::cout << "victory";
				SceneManager::RunScene("SceneMainMenu");
			}
			victoryTime -= _delta;
		}
	}
}

void SceneGameBossRoom::Render(sf::RenderWindow* _window)
{
	SceneGameAbstract::Render(_window);
}
#include "Scenes/ScenesGame/SceneGameBossRoom.h"
#include "BuilderGameObject.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Managers/AudioManager.h"
#include "Managers/AssetManager.h"
#include "Managers/WindowManager.h"
#include "Components/Entity/Character.h"
#include "Components/Entity/Enemy/Hades.h"
#include "Components/Entity/Enemy/ProtectionBall.h"
#include "Components/ComponentsGame/WeaponsContainer.h"
#include "Components/ComponentsGame/Gun.h"
#include "Components/ComponentsGame/Bullet.h"

SceneGameBossRoom::SceneGameBossRoom() : SceneGameAbstract("SceneGameBossRoom") {}
SceneGameBossRoom::SceneGameBossRoom(const std::string& _name) : SceneGameAbstract(_name) {}

void SceneGameBossRoom::Awake()
{
	SceneGameAbstract::Awake();
}

void SceneGameBossRoom::Preload()
{
	SceneGameAbstract::Preload();

	AudioManager::AddMusic("MusicAmbiant_CI", "../Assets/Audio/Musics/MusicAmbiant_CrackerIsland.ogg");

	AssetManager::AddAsset("BackgroundBoss", "Assets/Graphics/Maps/bossRoom.png");
	AssetManager::AddAsset("breathHades", "Assets/Enemy/Hades/breath.png");
	AssetManager::AddAsset("breathFireHades", "Assets/Enemy/Hades/breath-fire.png");
	AssetManager::AddAsset("attackHades", "Assets/Enemy/Hades/demon-attack.png");
	AssetManager::AddAsset("roarHades", "Assets/Enemy/Hades/demon-attack-no-breath.png");
	AssetManager::AddAsset("idleHades", "Assets/Enemy/Hades/demon-idle.png");
	AssetManager::AddAsset("protectionHades", "Assets/Enemy/Hades/protection.png");
	AssetManager::AddAsset("protectionBallsHades", "Assets/Boss/balls.png");
	unsigned seed = static_cast<unsigned>(time(0));
	srand(seed);

}

void SceneGameBossRoom::Create()
{
	SceneGameAbstract::Create();
	AudioManager::PlayMusic("MusicAmbiant_CI");
	GameObject* backgroundBossRoom = BuilderGameObject::CreateBackgroundGameObject("BossRoom", WindowManager::GetFloatWindowWidth() / 2, WindowManager::GetFloatWindowHeight() / 2, 1, 1, AssetManager::GetAsset("BackgroundBoss"));
	plateforme = BuilderEntityGameObject::CreatePlateformGameObject("Plateforme", WindowManager::GetFloatWindowWidth() / 2, WindowManager::GetFloatWindowHeight() + 50, 12, 2);
	plateforme->SetVisible(false);
	CreatePlayer(WindowManager::GetFloatWindowWidth() / 1.1, WindowManager::GetFloatWindowHeight() / 1.2);
	player->GetComponent<Character>()->SetCenterCamera(false);

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
	if (player && plateforme)
	{
		if (RigidBody2D::IsColliding(*(player->GetComponent<RigidBody2D>()), *(plateforme->GetComponent<RigidBody2D>())) && firstCollide)
		{
			player->GetComponent<RigidBody2D>()->SetIsGravity(false);
			player->GetComponent<Character>()->SetOnFloor(true);
			firstCollide = false;
		}
		else if (!RigidBody2D::IsColliding(*(player->GetComponent<RigidBody2D>()), *(plateforme->GetComponent<RigidBody2D>())))
		{
			firstCollide = true;
			player->GetComponent<RigidBody2D>()->SetIsGravity(true);
			player->GetComponent<Character>()->SetOnFloor(false);
		}
	}
	if (player && hades)
	{
		Gun* gun = player->GetComponent<WeaponsContainer>()->GetArme()->GetComponent<Gun>();
		if (gun) {
			for (GameObject* bullet : gun->GetBullets())
			{

				if (RigidBody2D::IsColliding(*(bullet->GetComponent<RigidBody2D>()), *(hades->GetComponent<RigidBody2D>())) && hades->GetActive())
				{
					hades->GetComponent<Hades>()->TakeDamage(bullet->GetComponent<Bullet>()->GetDamageReduced());
					gun->RemoveBullet(bullet);
					RemoveGameObject(bullet);
				}
				for (GameObject* protectionBall : hades->GetComponent<Hades>()->GetProtectionBalls())
				{
					if (RigidBody2D::IsColliding(*(bullet->GetComponent<RigidBody2D>()), *(protectionBall->GetComponent<RigidBody2D>())) && hades->GetActive())
					{
						protectionBall->GetComponent<ProtectionBall>()->TakeDamage(bullet->GetComponent<Bullet>()->GetDamageReduced());
						gun->RemoveBullet(bullet);
						RemoveGameObject(bullet);
					}
				}
			}
		}
	}
	if (hades->GetComponent<Hades>()->GetHealthPoint() == 0)
	{
		if (victoryTime <= 0.f)
		{
			std::cout << "victory";
			SceneManager::RunScene("SceneMainMenu");
		}
		victoryTime -= _delta;
	}
}

void SceneGameBossRoom::Render(sf::RenderWindow* _window)
{
	SceneGameAbstract::Render(_window);
}
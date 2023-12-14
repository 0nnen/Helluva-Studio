#include "Scenes/ScenesGame/SceneGameBossRoom.h"
#include "BuilderGameObject.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Managers/AssetManager.h"
#include "Managers/WindowManager.h"
#include "Components/Entity/Character.h"

SceneGameBossRoom::SceneGameBossRoom() : SceneGameAbstract("SceneGameBossRoom") {}
SceneGameBossRoom::SceneGameBossRoom(const std::string& _name) : SceneGameAbstract(_name) {}

void SceneGameBossRoom::Awake()
{
	SceneGameAbstract::Awake();
}
void SceneGameBossRoom::Preload()
{
	SceneGameAbstract::Preload();
	AssetManager::AddAsset("BackgroundBoss", "../Assets/Graphics/Maps/bossRoom.png");
}
void SceneGameBossRoom::Create()
{
	SceneGameAbstract::Create();
	GameObject* backgroundBossRoom = BuilderGameObject::CreateBackgroundGameObject("BossRoom", WindowManager::GetFloatWindowWidth() / 2, WindowManager::GetFloatWindowHeight() / 2, 1, 1, AssetManager::GetAsset("BackgroundBoss"));
	plateforme = BuilderEntityGameObject::CreatePlateformGameObject("Plateforme", WindowManager::GetFloatWindowWidth() / 2, WindowManager::GetFloatWindowHeight(), 12, 2);
	CreatePlayer(WindowManager::GetFloatWindowWidth() / 1.1 ,WindowManager::GetFloatWindowHeight()/ 1.2);
	player->GetComponent<Character>()->SetCenterCamera(false);
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
}
void SceneGameBossRoom::Render(sf::RenderWindow* _window)
{
	SceneGameAbstract::Render(_window);
}
#include "Scenes/ScenesGame/SceneGameWorld.h"
#include "BuilderGameObject.h"

#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Components/Entity/Character.h"
#include "Components/Entity/Enemy/EnemyA.h"


bool SceneGameWorld::flip;

SceneGameWorld::SceneGameWorld(const std::string& _newName) : SceneGameAbstract(_newName) {
	shootBullet = true;
}

void SceneGameWorld::Preload()
{
	SceneGameAbstract::Preload();
	AssetManager::AddAsset("BackgroundMapBackgroundWorld", "../Assets/Graphics/Maps/worldMapBackground.png");
	AssetManager::AddAsset("BackgroundMapWorld", "../Assets/Graphics/Maps/worldMap1.png");
	AssetManager::AddAsset("idleEnemyA", "../Assets/Enemy/Hell-Beast-Files/PNG/with-stroke/hell-beast-idle.png");
	AssetManager::AddAsset("shootEnemyA", "../Assets/Enemy/Hell-Beast-Files/PNG/with-stroke/hell-beast-breath.png");
	AssetManager::AddAsset("FireBallEnemy", "../Assets/Enemy/Hell-Beast-Files/PNG/fire-ball.png");
}

void SceneGameWorld::Create()
{
	SceneGameAbstract::Create();
	CreatePlayer();
	CreateEnemy();
	GameObject* backgroundWorldMap = BuilderGameObject::CreateBackgroundGameObject("BackgroundMapWorld1", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, 1,1, AssetManager::GetAsset("BackgroundMapBackgroundWorld"), 0);
	GameObject* backgroundWorldMap2 = BuilderGameObject::CreateBackgroundGameObject("BackgroundMapWorld2", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, 1,1, AssetManager::GetAsset("BackgroundMapWorld"), 0);
	plateform = BuilderEntityGameObject::CreatePlateformGameObject("plateform", WindowManager::GetWindowWidth() / 2, 1200, 100, 2);
	//this->CreatePlatformCollision();
	isPause = false;
	hud = new ATH(player->GetComponent<Character>(), player->GetComponent<Character>()->GetMaxHealthPoint());
}

void SceneGameWorld::CreatePlatformCollision()
{
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform1", 10, 782, 1.4f, 0.5f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform2", 215, 834, 0.15f, 0.5f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform3", 235, 910, 0.70f, 0.5f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform4", 166, 870, 0.1f, 1.1f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform5", 320, 885, 0.15f, 0.5f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform6", 345, 858, 0.15f, 0.5f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform7", 370, 831, 0.15f, 0.5f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform8", 510, 806, 1.3f, 0.5f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform9", 842, 935, 0.76f, 0.5f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform10", 1050, 860, 0.50f, 0.5f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform11", 1304, 870, 1.27f, 0.5f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform12", 1497, 950, 0.65f, 0.5f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform13", 1742, 870, 1.8f, 0.5f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform14", 754, 744, 0.64f, 0.96f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform15", 907, 744, 0.63f, 1.95f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform16", 1125, 655, 0.88f, 1.47f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform16", 1010, 680, 0.27f, 0.47f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform17", 1187, 900, 0.1f, 1.25f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform18", 1421, 910, 0.1f, 1.30f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform19", 1571, 910, 0.1f, 1.30f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform20", 1725, 757, 0.13f, 0.5f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform21", 1778, 705, 0.13f, 0.5f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform22", 1675, 807, 0.38f, 0.5f));
	platformCarreCollision.push_back(BuilderEntityGameObject::CreatePlatformCollisionGameObject("Platform23", 1868, 693, 0.50f, 1.0f));

	platformTriangleCollision.push_back(BuilderEntityGameObject::CreatePlatformTriangleCollisionGameObject("Triangle1", 7.9f, 7.9f, 1045, 608, 90));
	platformTriangleCollision.push_back(BuilderEntityGameObject::CreatePlatformTriangleCollisionGameObject("Triangle2", 7.7f, 7.7f, 1360, 715, 90));
	platformTriangleCollision.push_back(BuilderEntityGameObject::CreatePlatformTriangleCollisionGameObject("Triangle3", 7.7f, 7.7f, 1310, 853, 180));
	platformTriangleCollision.push_back(BuilderEntityGameObject::CreatePlatformTriangleCollisionGameObject("Triangle4", 7.7f, 7.7f, 1312, 700, 180));
	platformTriangleCollision.push_back(BuilderEntityGameObject::CreatePlatformTriangleCollisionGameObject("Triangle5", 7.7f, 7.7f, 1157, 905, 180));
	platformTriangleCollision.push_back(BuilderEntityGameObject::CreatePlatformTriangleCollisionGameObject("Triangle6", 7.7f, 7.7f, 1192, 940, 180));
	platformTriangleCollision.push_back(BuilderEntityGameObject::CreatePlatformTriangleCollisionGameObject("Triangle7", 7.7f, 7.7f, 785, 940, 180));
	platformTriangleCollision.push_back(BuilderEntityGameObject::CreatePlatformTriangleCollisionGameObject("Triangle8", 7.7f, 7.7f, 737, 895, 180));
	platformTriangleCollision.push_back(BuilderEntityGameObject::CreatePlatformTriangleCollisionGameObject("Triangle9", 7.5f, 7.5f, 692, 850, 180));
	platformTriangleCollision.push_back(BuilderEntityGameObject::CreatePlatformTriangleCollisionGameObject("Triangle10", 7.9f, 7.9f, 214, 833, 180));
	platformTriangleCollision.push_back(BuilderEntityGameObject::CreatePlatformTriangleCollisionGameObject("Triangle11", 7.7f, 7.7f, 965, 879, 90));
	platformTriangleCollision.push_back(BuilderEntityGameObject::CreatePlatformTriangleCollisionGameObject("Triangle12", 7.7f, 7.7f, 1006, 840, 90));
}

void SceneGameWorld::CreateEnemy()
{
	enemy = BuilderEntityGameObject::CreateEnemyAGameObject("EnemyA", WindowManager::GetWindowWidth() / 2, 600.f, 7.f, 7.f, AssetManager::GetAsset("idleEnemyA"));
}

void SceneGameWorld::CreateRengeEnemy()
{
	rengePosition = BuilderEntityGameObject::CreatePlateformGameObject("RengePosition", enemy->GetPosition().GetX(), enemy->GetPosition().GetY(), 8.f, 5.f);
	rengeProjectil = BuilderEntityGameObject::CreatePlateformGameObject("RengeProjectil", enemy->GetPosition().GetX(), enemy->GetPosition().GetY(), 4.f, 5.f);
}

void SceneGameWorld::Delete()
{
	Scene::Delete();
}

void SceneGameWorld::Render(sf::RenderWindow* _window)
{
	SceneGameAbstract::Render(_window);

	if (hud) {
		hud->Render(*_window);
	}
	_window->setView(CameraManager::GetView());
}

void SceneGameWorld::CollisionRengePosition(const float& _delta) {
	EnemyA* enemyA = enemy->GetComponent<EnemyA>();
	RigidBody2D* rigidBody2D = enemy->GetComponent<RigidBody2D>();
	if (player && rengePosition)
	{
		if (RigidBody2D::IsColliding(*(player->GetComponent<RigidBody2D>()), *(rengePosition->GetComponent<RigidBody2D>())))
		{
			if (player->GetPosition().GetX() <= enemy->GetPosition().GetX())
			{
				EnemyA::Mouve(_delta, enemyA->GetSpeed());
			}
			if (player->GetPosition().GetX() > enemy->GetPosition().GetX())
			{
				EnemyA::Mouve(_delta, -enemyA->GetSpeed());
			}
		}
		else 
		{
			rigidBody2D->SetVelocity(Maths::Vector2f(0.f, 0.f) );
		}
		
	}
}

void SceneGameWorld::CollisionRengeShoot(const float& _delta)
{
	EnemyA* enemyA = enemy->GetComponent<EnemyA>();
	RigidBody2D* rigidBody2D = enemy->GetComponent<RigidBody2D>();
	if (player && rengeProjectil)
	{
		if (RigidBody2D::IsColliding(*(player->GetComponent<RigidBody2D>()), *(rengeProjectil->GetComponent<RigidBody2D>())))
		{
			rigidBody2D->SetVelocity(Maths::Vector2f(0.f, 0.f));
			if (player->GetPosition().GetX() <= enemy->GetPosition().GetX())
			{
				flip = false;
				enemyA->Attack(-1.f, 0.f);
			}
			if (player->GetPosition().GetX() > enemy->GetPosition().GetX())
			{
				flip = true;
				enemyA->Attack(1.f, 0.f);
			}

		}
		else if (!RigidBody2D::IsColliding(*(player->GetComponent<RigidBody2D>()), *(rengeProjectil->GetComponent<RigidBody2D>())))
		{
			if (!enemyA->GetAnimation("idle")->GetIsPlaying())
			{
				enemyA->GetAndSetAnimation("idle")->Play();
			}
		}
		
	}
};


void SceneGameWorld::Collision(GameObject* _entity)
{
	/*for (GameObject* onePlatformCarreCollision : platformCarreCollision)
	{
		if (_entity, onePlatformCarreCollision) {
			if (RigidBody2D::IsColliding(*(_entity->GetComponent<RigidBody2D>()), *(onePlatformCarreCollision->GetComponent<RigidBody2D>())))
			{
				_entity->SetPosition(_entity->GetPosition() - Maths::Vector2f(0, 0.5f));
				_entity->GetComponent<RigidBody2D>()->SetIsGravity(false);
				_entity->GetComponent<Entity>()->SetOnFloor(true);
				firstCollide = false;
			}
			else if (!RigidBody2D::IsColliding(*(_entity->GetComponent<RigidBody2D>()), *(onePlatformCarreCollision->GetComponent<RigidBody2D>())))
			{
				firstCollide = true;
				_entity->GetComponent<RigidBody2D>()->SetIsGravity(true);
				_entity->GetComponent<Entity>()->SetOnFloor(false);
			}
		}

	}*/
	if (_entity && plateform)
	{
		if (RigidBody2D::IsColliding(*(_entity->GetComponent<RigidBody2D>()), *(plateform->GetComponent<RigidBody2D>())))
		{
			_entity->SetPosition(_entity->GetPosition() - Maths::Vector2f(0, 0.5f));
			_entity->GetComponent<RigidBody2D>()->SetIsGravity(false);
			_entity->GetComponent<Entity>()->SetOnFloor(true);
			firstCollide = false;
		}
		else if (!RigidBody2D::IsColliding(*(_entity->GetComponent<RigidBody2D>()), *(plateform->GetComponent<RigidBody2D>())))
		{
			firstCollide = true;
			_entity->GetComponent<RigidBody2D>()->SetIsGravity(true);
			_entity->GetComponent<Entity>()->SetOnFloor(false);
		}
	}
}

void SceneGameWorld::Update(const float& _delta)
{
	SceneGameAbstract::Update(_delta);
	if (!isPause) {
		CreateRengeEnemy();
		Collision(player);
		Collision(enemy);
		CollisionRengePosition(_delta);
		CollisionRengeShoot(_delta); 
		if (EnemyA::GetBulletEnemy()->GetComponent<RigidBody2D>() && player)
		{
			if (RigidBody2D::IsColliding(*(EnemyA::GetBulletEnemy()->GetComponent<RigidBody2D>()), *(player->GetComponent<RigidBody2D>())))
			{
				
			}
		}
	}

	if (hud) {
		hud->Update(_delta);
	}

	
	
}


#include "Scenes/ScenesGame/ScenesTest.h"
#include "Components/Entity/Character.h"
#include "BuilderGameObject.h"
#include "Managers/CameraManager.h"

#include "Components/ComponentsGame/WeaponsContainer.h"
#include "Components/ComponentsGame/Gun.h"
#include "Components/ComponentsGame/Bullet.h"
bool ScenesTest::flip;

#include "Managers/AssetManager.h"
#include "Managers/WindowManager.h"
#include "Managers/SceneManager.h"

#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "BuildersGameObject/BuilderShapeGameObject.h"

#include "Components/RigidBody2D.h"
#include "TileMap/TileMap.h"


ScenesTest::ScenesTest(const std::string& _newName) : SceneGameAbstract(_newName) {
}

ScenesTest::~ScenesTest() {}

void ScenesTest::Awake()
{
	SceneGameAbstract::Awake();
}

void ScenesTest::Delete()
{
	SceneGameAbstract::Delete();
}

void ScenesTest::Preload()
{
	SceneGameAbstract::Preload();
	AssetManager::AddAsset("BackgroundSceneGame1", "Assets/Graphics/Backgrounds/SceneGame/backgroundSky.jpg"); 
	AssetManager::AddAsset("idleEnemyA", "Assets/Enemy/Hell-Beast-Files/PNG/with-stroke/hell-beast-idle.png");
	AssetManager::AddAsset("shootEnemyA", "Assets/Enemy/Hell-Beast-Files/PNG/with-stroke/hell-beast-breath.png");
	AssetManager::AddAsset("deadEnemyA", "Assets/Enemy/Hell-Beast-Files/PNG/with-stroke/hell-beast-burn.png");
	AssetManager::AddAsset("FireBallEnemy", "Assets/Enemy/Hell-Beast-Files/PNG/fire-ball.png");
}

void ScenesTest::Create()
{
	CameraManager::DefaultZoom();
	SceneGameAbstract::Create();
	backgrounds.push_back(BuilderGameObject::CreateBackgroundGameObject("BackgroundSceneGame1", 0, 0, 7.0f, 3.0f, AssetManager::GetAsset("BackgroundSceneGame1"), 0, 0.f));

	tileMap = BuilderEntityGameObject::CreateMapGameObject("OverWorld", "Assets/Graphics/Maps/WorldMap/WorldMap.json", "Assets/Graphics/Maps/WorldMap/worldMapBackground.png", 89);
	CreateEnemy();
	CreatePlayer(500,1400);
	CameraManager::SetZoom(1.75f);
	
}

void ScenesTest::CreateEnemy()
{
	enemys.push_back(BuilderEntityGameObject::CreateEnemyAGameObject("Enemy1", 1600.f, 1400.f, 1.5f, 1.5f, AssetManager::GetAsset("idleEnemyA")));
	enemys.push_back(BuilderEntityGameObject::CreateEnemyAGameObject("Enemy2", 1600.f, 800.f, 1.5f, 1.5f, AssetManager::GetAsset("idleEnemyA")));
	enemys.push_back(BuilderEntityGameObject::CreateEnemyAGameObject("Enemy3", 5000.f, 1400.f, 1.5f, 1.5f, AssetManager::GetAsset("idleEnemyA")));
	enemys.push_back(BuilderEntityGameObject::CreateEnemyAGameObject("Enemy4", 2300.f, 1200.f, 1.5f, 1.5f, AssetManager::GetAsset("idleEnemyA")));
	enemys.push_back(BuilderEntityGameObject::CreateEnemyAGameObject("Enemy5", 3500.f, 1200.f, 1.5f, 1.5f, AssetManager::GetAsset("idleEnemyA")));
}



void ScenesTest::Collinding()
{
	if (player && tileMap)
	{

		RigidBody2D* rigidBody2DPlayer = player->GetComponent<RigidBody2D>();
		Character* character = player->GetComponent<Character>();
		std::vector<SquareCollider*> squareColliders = player->GetComponentsByType<SquareCollider>();
		SquareCollider* squareCollider = squareColliders[0];
		SquareCollider* squareColliderGround = squareColliders[1];
		SquareCollider* detectedSquare = nullptr;
		if (!squareColliderGround->GetActiveCollider())
		{
			if (detectedSquare = tileMap->GetComponent<TileMap>()->CheckCollisionAbove(*squareCollider))
			{
				character->SetOnFloor(true);
				rigidBody2DPlayer->SetIsGravity(false);
				const float distanceY = std::abs(squareCollider->GetCenterY() - detectedSquare->GetCenterY());
				const float height = squareCollider->GetHeightCollider() / 2.f + detectedSquare->GetHeightCollider() / 2.f;
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
			detectedSquare = tileMap->GetComponent<TileMap>()->CheckCollisionAbove(*squareColliderGround);
			if (!detectedSquare)
			{
				squareColliderGround->SetActiveCollider(false);
				squareCollider->SetActiveCollider(true);
				rigidBody2DPlayer->SetIsGravity(true);
				character->SetOnFloor(false);


			}
		}
		if (detectedSquare = tileMap->GetComponent<TileMap>()->CheckCollisionBelow(*squareCollider))
		{
			const float distanceY = std::abs(squareCollider->GetCenterY() - detectedSquare->GetCenterY());
			const float height = squareCollider->GetHeightCollider() / 2 + detectedSquare->GetHeightCollider() / 2;
			const float difference = height - distanceY;
			player->SetPosition(player->GetPosition() + Maths::Vector2f(0, difference));
			rigidBody2DPlayer->SetVelocity(Maths::Vector2f(rigidBody2DPlayer->GetVelocity().x, 0));
		}
		if (detectedSquare = tileMap->GetComponent<TileMap>()->CheckCollisionLeft(*squareCollider))
		{
			const float distanceX = std::abs(squareCollider->GetCenterX() - detectedSquare->GetCenterX());
			const float width = squareCollider->GetWidthCollider() / 2 + detectedSquare->GetWidthCollider() / 2;
			const float difference = width - distanceX;
			player->SetPosition(player->GetPosition() - Maths::Vector2f(difference, 0));
			rigidBody2DPlayer->SetVelocity(Maths::Vector2f(0, rigidBody2DPlayer->GetVelocity().y));

		}
		if (detectedSquare = tileMap->GetComponent<TileMap>()->CheckCollisionRight(*squareCollider))
		{
			const float distanceX = std::abs(squareCollider->GetCenterX() - detectedSquare->GetCenterX());
			const float width = squareCollider->GetWidthCollider() / 2 + detectedSquare->GetWidthCollider() / 2;
			const float difference = width - distanceX;
			player->SetPosition(player->GetPosition() + Maths::Vector2f(difference, 0));
			rigidBody2DPlayer->SetVelocity(Maths::Vector2f(0, rigidBody2DPlayer->GetVelocity().y));
		}
	}
}

void ScenesTest::CollindingEntity(GameObject* _entity)
{
	if (_entity && tileMap)
	{

		RigidBody2D* rigidBody2DEntity = _entity->GetComponent<RigidBody2D>();
		Entity* entity = _entity->GetComponent<Entity>();
		std::vector<SquareCollider*> squareColliders = _entity->GetComponentsByType<SquareCollider>();
		SquareCollider* squareCollider = squareColliders[0];
		SquareCollider* squareColliderGround = squareColliders[1];
		SquareCollider* detectedSquare = nullptr;
		if (!squareColliderGround->GetActiveCollider())
		{
			if (detectedSquare = tileMap->GetComponent<TileMap>()->CheckCollisionAbove(*squareCollider))
			{
				entity->SetOnFloor(true);
				rigidBody2DEntity->SetIsGravity(false);
				const float distanceY = std::abs(squareCollider->GetCenterY() - detectedSquare->GetCenterY());
				const float height = squareCollider->GetHeightCollider() / 2.f + detectedSquare->GetHeightCollider() / 2.f;
				const float difference = height - distanceY;
				_entity->SetPosition(_entity->GetPosition() - Maths::Vector2f(0.f, difference));
				squareColliderGround->SetActiveCollider(true);
				squareCollider->SetActiveCollider(false);
			}
			else
			{
				entity->SetOnFloor(false);
				rigidBody2DEntity->SetIsGravity(true);
			}
		}
		else if (squareColliderGround->GetActiveCollider())
		{
			detectedSquare = tileMap->GetComponent<TileMap>()->CheckCollisionAbove(*squareColliderGround);
			if (!detectedSquare)
			{
				squareColliderGround->SetActiveCollider(false);
				squareCollider->SetActiveCollider(true);
				rigidBody2DEntity->SetIsGravity(true);
				entity->SetOnFloor(false);


			}
		}
		if (detectedSquare = tileMap->GetComponent<TileMap>()->CheckCollisionBelow(*squareCollider))
		{
			const float distanceY = std::abs(squareCollider->GetCenterY() - detectedSquare->GetCenterY());
			const float height = squareCollider->GetHeightCollider() / 2 + detectedSquare->GetHeightCollider() / 2;
			const float difference = height - distanceY;
			_entity->SetPosition(_entity->GetPosition() + Maths::Vector2f(0, difference));
			rigidBody2DEntity->SetVelocity(Maths::Vector2f(rigidBody2DEntity->GetVelocity().x, 0));
		}
		if (detectedSquare = tileMap->GetComponent<TileMap>()->CheckCollisionLeft(*squareCollider))
		{
			const float distanceX = std::abs(squareCollider->GetCenterX() - detectedSquare->GetCenterX());
			const float width = squareCollider->GetWidthCollider() / 2 + detectedSquare->GetWidthCollider() / 2;
			const float difference = width - distanceX;
			_entity->SetPosition(_entity->GetPosition() - Maths::Vector2f(difference, 0));
			rigidBody2DEntity->SetVelocity(Maths::Vector2f(0, rigidBody2DEntity->GetVelocity().y));

		}
		if (detectedSquare = tileMap->GetComponent<TileMap>()->CheckCollisionRight(*squareCollider))
		{
			const float distanceX = std::abs(squareCollider->GetCenterX() - detectedSquare->GetCenterX());
			const float width = squareCollider->GetWidthCollider() / 2 + detectedSquare->GetWidthCollider() / 2;
			const float difference = width - distanceX;
			_entity->SetPosition(_entity->GetPosition() + Maths::Vector2f(difference, 0));
			rigidBody2DEntity->SetVelocity(Maths::Vector2f(0, rigidBody2DEntity->GetVelocity().y));
		}
	}
}

void ScenesTest::CollisionRengePosition(const float& _delta, GameObject* _entity) {
	Entity* entity = _entity->GetComponent<Entity>();
	RigidBody2D* rigidBody2D = _entity->GetComponent<RigidBody2D>();
	squareColliders = _entity->GetComponentsByType<SquareCollider>();
	SquareCollider* squareCollider = nullptr;
	for (size_t i = 0; i < squareColliders.size(); i++)
	{
		if (squareColliders[i]->GetName() == std::string("Renge"))
		{ 
			squareCollider = squareColliders[i];
			break;
		}
	}
	if (player && squareCollider)
	{
		if (SquareCollider::IsColliding(*(player->GetComponent<SquareCollider>()), *(squareCollider)))
		{
			if (player->GetPosition().GetX() <= _entity->GetPosition().GetX())
			{
				rigidBody2D->AddForces(Maths::Vector2f::Left * _delta * entity->GetSpeed());
			}
			if (player->GetPosition().GetX() > _entity->GetPosition().GetX())
			{
				rigidBody2D->AddForces(Maths::Vector2f::Right * _delta * entity->GetSpeed());
			}
		}
		else
		{
			rigidBody2D->SetVelocity(Maths::Vector2f(0.f, rigidBody2D->GetVelocity().y));
		}
	}
}

void ScenesTest::CollisionBulletPlayer(GameObject* _entity)
{
	squareColliders = _entity->GetComponentsByType<SquareCollider>();
	SquareCollider* squareCollider = nullptr;
	for (size_t i = 0; i < squareColliders.size(); i++)
	{
		if (squareColliders[i]->GetName() == std::string("shapeEnemy"))
		{
			squareCollider = squareColliders[i];
			break;
		}
	}
	if (player && _entity)
	{
		Gun* gun = player->GetComponent<WeaponsContainer>()->GetArme()->GetComponent<Gun>();
		if (gun) {
			for (GameObject* bullet : gun->GetBullets())
			{
				//_entity->GetComponentsByType<SquareCollider>()

				if (SquareCollider::IsColliding(*(bullet->GetComponent<SquareCollider>()), *(_entity->GetComponent<SquareCollider>())) && _entity->GetActive())
				{
					_entity->GetComponent<Entity>()->TakeDamage(bullet->GetComponent<Bullet>()->GetDamageReduced());
					gun->RemoveBullet(bullet);
					RemoveGameObject(bullet);
				}
			}
		}
	}
};

void ScenesTest::CollisionRengeAttack(const float& _delta, GameObject* _entity)
{
	Entity* entity = _entity->GetComponent<Entity>();
	RigidBody2D* rigidBody2D = _entity->GetComponent<RigidBody2D>();
	squareColliders = _entity->GetComponentsByType<SquareCollider>();
	SquareCollider* squareCollider = nullptr;
	for (size_t i = 0; i < squareColliders.size(); i++)
	{
		if (squareColliders[i]->GetName() == std::string("RengeAttack"))
		{
			squareCollider = squareColliders[i];
			break;
		}
	}
	if (player && squareCollider)
	{
		
		if (SquareCollider::IsColliding(*(player->GetComponent<SquareCollider>()), *(squareCollider)))
		{
			rigidBody2D->SetVelocity(Maths::Vector2f(0.f, rigidBody2D->GetVelocity().y));
			if (player->GetPosition().GetX() <= _entity->GetPosition().GetX()) flip = true;
			if (player->GetPosition().GetX() > _entity->GetPosition().GetX()) flip = false;
			entity->Attack(_delta);
		}
		else if (!SquareCollider::IsColliding(*(player->GetComponent<SquareCollider>()), *(squareCollider)))
		{
			if (!entity->GetAnimation("shoot")->GetIsPlaying() && !entity->GetAnimation("idle")->GetIsPlaying()) entity->GetAnimation("idle")->Play();

		}
	}
};


void ScenesTest::DeadEnemy(GameObject* _entity)
{
	Entity* entity = _entity->GetComponent<Entity>();
	if (entity->GetHealthPoint() <= 0)
	{
		RemoveEnemy(_entity);
	}
}

void ScenesTest::Physics(const float& _delta)
{
	SceneGameAbstract::Physics(_delta);

	this->Collinding();

	for (size_t i = 0; i < enemys.size(); i++)
	{
		GameObject* enemy = enemys[i];
		if(enemy) 
		{
			this->CollindingEntity(enemy);
			this->CollisionBulletPlayer(enemy);

			this->CollisionRengePosition(_delta, enemy);
			this->CollisionRengeAttack(_delta, enemy);
			this->DeadEnemy(enemy);
		}
		
	}

}

void ScenesTest::Update(const float& _delta)
{
	SceneGameAbstract::Update(_delta);
	if (!isPause)
	{
		if (player->GetPosition().y >= 1600.f)
		{
			Character* character = player->GetComponent<Character>();
			if (character->GetIsCenter())
			{
				character->SetCenterCamera(false);
			}
		}
		if (player->GetPosition().y >= 9000.f)
		{
			player->SetPosition(Maths::Vector2f(500.f, 1400.f));
			Character* character = player->GetComponent<Character>();
			if (!character->GetIsCenter())
			{
				character->SetCenterCamera(true);
			}
		}
		if (player->GetPosition().x >= 210.f * 32.f && enemys.empty())
		{

			player->GetComponent<RigidBody2D>()->SetVelocity(Maths::Vector2f::Zero);

			this->Pause(true);
			SceneManager::RunScene("SceneGameBossRoom");
		}
	}

}

void ScenesTest::Render(sf::RenderWindow* _window)
{
	SceneGameAbstract::Render(_window);
}

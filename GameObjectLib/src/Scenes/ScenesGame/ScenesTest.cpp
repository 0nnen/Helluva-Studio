#include "Scenes/ScenesGame/ScenesTest.h"
#include "Components/Entity/Character.h"
#include "BuilderGameObject.h"
#include "Managers/CameraManager.h"

bool ScenesTest::flip;

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
	CreateRengeEnemy();
	CameraManager::SetZoom(1.75f);
	
}

void ScenesTest::CreateEnemy()
{
	enemy = BuilderEntityGameObject::CreateEnemyAGameObject("EnemyA", 1800.f, 1200.f, 2.5f, 2.5f, AssetManager::GetAsset("idleEnemyA"));
}

void ScenesTest::CreateRengeEnemy()
{
	rengePosition = BuilderEntityGameObject::CreatePlateformGameObject("RengePosition", enemy->GetPosition().GetX(), enemy->GetPosition().GetY(), 8.f, 5.f);
	rengeAttack = BuilderEntityGameObject::CreatePlateformGameObject("RengeProjectil", enemy->GetPosition().GetX(), enemy->GetPosition().GetY(), 4.f, 5.f);
}

//void ScenesTest::Collinding()
//{
//	if (player && tileMap)
//	{
//
//		RigidBody2D* rigidBody2DPlayer = player->GetComponent<RigidBody2D>();
//		Character* character = player->GetComponent<Character>();
//		std::vector<SquareCollider*> squareColliders = player->GetComponentsByType<SquareCollider>();
//		SquareCollider* squareCollider = squareColliders[0];
//		SquareCollider* squareColliderGround = squareColliders[1];
//		SquareCollider* detectedSquare = nullptr;
//		if (!squareColliderGround->GetActiveCollider())
//		{
//			if (detectedSquare = tileMap->GetComponent<TileMap>()->CheckCollisionAbove(*squareCollider))
//			{
//				character->SetOnFloor(true);
//				rigidBody2DPlayer->SetIsGravity(false);
//				const float distanceY = std::abs(squareCollider->GetCenterY() - detectedSquare->GetCenterY());
//				const float height = squareCollider->GetHeightCollider() / 2.f + detectedSquare->GetHeightCollider() / 2.f;
//				const float difference = height - distanceY;
//				player->SetPosition(player->GetPosition() - Maths::Vector2f(0.f, difference));
//				squareColliderGround->SetActiveCollider(true);
//				squareCollider->SetActiveCollider(false);
//			}
//			else
//			{
//				character->SetOnFloor(false);
//				rigidBody2DPlayer->SetIsGravity(true);
//			}
//		}
//		else if (squareColliderGround->GetActiveCollider())
//		{
//			detectedSquare = tileMap->GetComponent<TileMap>()->CheckCollisionAbove(*squareColliderGround);
//			if (!detectedSquare)
//			{
//				squareColliderGround->SetActiveCollider(false);
//				squareCollider->SetActiveCollider(true);
//				rigidBody2DPlayer->SetIsGravity(true);
//				character->SetOnFloor(false);
//
//
//			}
//		}
//		if (detectedSquare = tileMap->GetComponent<TileMap>()->CheckCollisionBelow(*squareCollider))
//		{
//			const float distanceY = std::abs(squareCollider->GetCenterY() - detectedSquare->GetCenterY());
//			const float height = squareCollider->GetHeightCollider() / 2 + detectedSquare->GetHeightCollider() / 2;
//			const float difference = height - distanceY;
//			player->SetPosition(player->GetPosition() + Maths::Vector2f(0, difference));
//			rigidBody2DPlayer->SetVelocity(Maths::Vector2f(rigidBody2DPlayer->GetVelocity().x, 0));
//		}
//		if (detectedSquare = tileMap->GetComponent<TileMap>()->CheckCollisionLeft(*squareCollider))
//		{
//			const float distanceX = std::abs(squareCollider->GetCenterX() - detectedSquare->GetCenterX());
//			const float width = squareCollider->GetWidthCollider() / 2 + detectedSquare->GetWidthCollider() / 2;
//			const float difference = width - distanceX;
//			player->SetPosition(player->GetPosition() - Maths::Vector2f(difference, 0));
//			rigidBody2DPlayer->SetVelocity(Maths::Vector2f(0, rigidBody2DPlayer->GetVelocity().y));
//
//		}
//		if (detectedSquare = tileMap->GetComponent<TileMap>()->CheckCollisionRight(*squareCollider))
//		{
//			const float distanceX = std::abs(squareCollider->GetCenterX() - detectedSquare->GetCenterX());
//			const float width = squareCollider->GetWidthCollider() / 2 + detectedSquare->GetWidthCollider() / 2;
//			const float difference = width - distanceX;
//			player->SetPosition(player->GetPosition() + Maths::Vector2f(difference, 0));
//			rigidBody2DPlayer->SetVelocity(Maths::Vector2f(0, rigidBody2DPlayer->GetVelocity().y));
//		}
//	}
//}

void ScenesTest::CollindingEntity(GameObject* _entity)
{
	if (player && tileMap)
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

void ScenesTest::CollisionRengePosition(const float& _delta, GameObject* _entity, GameObject* _rengePosition) {
	Entity* entity = _entity->GetComponent<Entity>();
	RigidBody2D* rigidBody2D = _entity->GetComponent<RigidBody2D>();
	if (player && _rengePosition)
	{
		//std::cout << "okk";
		if (SquareCollider::IsColliding(*(player->GetComponent<SquareCollider>()), *(_rengePosition->GetComponent<SquareCollider>())))
		{
			//std::cout << "okk";
			if (player->GetPosition().GetX() <= enemy->GetPosition().GetX())
			{
				_entity->GetComponent<RigidBody2D>()->AddForces(Maths::Vector2f::Left * _delta * entity->GetSpeed());
			}
			if (player->GetPosition().GetX() > enemy->GetPosition().GetX())
			{
				_entity->GetComponent<RigidBody2D>()->AddForces(Maths::Vector2f::Left * -entity->GetSpeed());
			}
		}
		else
		{
			rigidBody2D->SetVelocity(Maths::Vector2f(0.f, 0.f));
		}

	}
}

void ScenesTest::CollisionRengeAttack(const float& _delta, GameObject* _entity, GameObject* _rengeAttack)
{
	Entity* entity = _entity->GetComponent<Entity>();
	RigidBody2D* rigidBody2D = _entity->GetComponent<RigidBody2D>();
	if (player && _rengeAttack)
	{
		//std::cout << "okk";
		if (SquareCollider::IsColliding(*(player->GetComponent<SquareCollider>()), *(_rengeAttack->GetComponent<SquareCollider>())))
		{
			std::cout << "okk";
			rigidBody2D->SetVelocity(Maths::Vector2f(0.f, 0.f));
			if (player->GetPosition().GetX() <= enemy->GetPosition().GetX()) flip = true;
			if (player->GetPosition().GetX() > enemy->GetPosition().GetX()) flip = false;
			entity->Attack();
		}
		else if (!SquareCollider::IsColliding(*(player->GetComponent<SquareCollider>()), *(_rengeAttack->GetComponent<SquareCollider>())))
		{
			if (!entity->GetAnimation("idle")->GetIsPlaying())
			{
				entity->GetAndSetAnimation("idle")->Play();
			}
		}

	}
};


void ScenesTest::Physics(const float& _delta)
{
	SceneGameAbstract::Physics(_delta);
	this->CollindingEntity(player);
	this->CollindingEntity(enemy);
	this->CollisionRengeAttack(_delta, enemy, rengeAttack);
	this->CollisionRengePosition(_delta, enemy, rengePosition);
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
		if (player->GetPosition().x >= 210.f * 32.f)
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

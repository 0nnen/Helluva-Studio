#include "Scenes/ScenesGame/ScenesTest.h"

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

void ScenesTest::CreatePlatform()
{
	tileMap = BuilderEntityGameObject::CreateMapGameObject("OverWorld", "Assets/Graphics/Maps/WorldMap/WorldMap.json", "Assets/Graphics/Maps/WorldMap/worldMapBackground.png");
	CreatePlayer(1000, 50);
}

void ScenesTest::Create()
{
	SceneGameAbstract::Create();
	tileMap = BuilderEntityGameObject::CreateMapGameObject("OverWorld", "Assets/Graphics/Maps/WorldMap/WorldMap.json", "Assets/Graphics/Maps/WorldMap/worldMapBackground.png");
	CreatePlayer(200, 1200);
}

void ScenesTest::Collinding()
{
	if(player && tileMap)
	{
		RigidBody2D* rigidBody2DPlayer = player->GetComponent<RigidBody2D>();
		SquareCollider* squareCollider = player->GetComponent<SquareCollider>();
		if (tileMap->GetComponent<TileMap>()->CheckCollisionAbove(*squareCollider))
		{
			rigidBody2DPlayer->SetIsGravity(false);
			player->SetPosition(player->GetPosition() - Maths::Vector2f(0, 0.5));
		}
		else
		{
			rigidBody2DPlayer->SetIsGravity(true);
		}
		if (tileMap->GetComponent<TileMap>()->CheckCollisionBelow(*squareCollider))
		{
			rigidBody2DPlayer->SetVelocity(Maths::Vector2f(rigidBody2DPlayer->GetVelocity().x, 0));
			player->SetPosition(player->GetPosition() + Maths::Vector2f(0, 0.5));
		}
		if (tileMap->GetComponent<TileMap>()->CheckCollisionLeft(*squareCollider))
		{
			rigidBody2DPlayer->SetVelocity(Maths::Vector2f(0, rigidBody2DPlayer->GetVelocity().y));
			player->SetPosition(player->GetPosition() - Maths::Vector2f(0.5, 0));

		}
		if (tileMap->GetComponent<TileMap>()->CheckCollisionRight(*squareCollider))
		{
			rigidBody2DPlayer->SetVelocity(Maths::Vector2f(0, rigidBody2DPlayer->GetVelocity().y));
			player->SetPosition(player->GetPosition() + Maths::Vector2f(0.5, 0));
		}
	}
}


void ScenesTest::Update(const float& _delta)
{
	SceneGameAbstract::Update(_delta);
	this->Collinding();
}

void ScenesTest::Render(sf::RenderWindow* _window)
{
	SceneGameAbstract::Render(_window);
}

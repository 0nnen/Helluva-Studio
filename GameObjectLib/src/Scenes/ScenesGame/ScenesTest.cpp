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
	platform = BuilderShapeGameObject::CreateCarreGameObject("platform", 10.f, 500.f);
}

void ScenesTest::Create()
{
	this->CreatePlatform();
	SceneGameAbstract::Create();
}

void ScenesTest::Collinding()
{
	player = SceneManager::GetActiveGameScene()->GetPlayer();
	if (RigidBody2D::IsAbove(*(player->GetComponent<RigidBody2D>()), *(platform->GetComponent<RigidBody2D>())))
	{
		std::cout << "ok";
		player->GetComponent<RigidBody2D>()->SetIsGravity(false);
	}
}


void ScenesTest::Update(const float& _delta)
{
	this->Collinding();
	SceneGameAbstract::Update(_delta);
}

void ScenesTest::Render(sf::RenderWindow* _window)
{
	SceneGameAbstract::Render(_window);
}

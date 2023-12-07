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

void ScenesTest::CreateCharacter()
{
	AssetManager::AddAsset("Perso", "../Assets/Character/perso1.png");

	player = BuilderEntityGameObject::CreateCharacterGameObject("Player", 10.f, 50.f, *AssetManager::GetAsset("Perso"), 0.25f, 0.25f);
}

void ScenesTest::CreatePlatform()
{
	platform = BuilderShapeGameObject::CreateCarreGameObject("platform", 10.f, 500.f);
}
void ScenesTest::Create()
{
	this->CreateCharacter();
	this->CreatePlatform();
	SceneGameAbstract::Create();
}

void ScenesTest::Collinding()
{

	if (RigidBody2D::IsAbove(*(SceneManager::GetActiveGameScene()->GetPlayer()->GetComponent<RigidBody2D>()), *(SceneManager::GetActiveGameScene()->GetPlatform()->GetComponent<RigidBody2D>())))
	{
		SceneManager::GetActiveGameScene()->GetPlayer()->GetComponent<RigidBody2D>()->SetIsGravity(false);
	}
}


void ScenesTest::Update(const float& _delta)
{
	SceneGameAbstract::Update(_delta);
}

void ScenesTest::Render(sf::RenderWindow* _window)
{
	SceneGameAbstract::Render(_window);
}

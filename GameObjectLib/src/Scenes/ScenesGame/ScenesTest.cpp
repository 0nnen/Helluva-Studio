#include "Scenes/ScenesGame/ScenesTest.h"

ScenesTest::ScenesTest(sf::RenderWindow* _window) : SceneGameAbstract(_window) {
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

	player = BuilderEntityGameObject::CreateCharacterGameObject("Player", WindowManager::GetWindowWidth() / 2, 50.f, *AssetManager::GetAsset("Perso"), 0.25f, 0.25f);
}

void ScenesTest::CreatePlatform()
{
	platform = BuilderShapeGameObject::CreateCarreGameObject("platform", WindowManager::GetWindowWidth() / 2, 50.f);
}
void ScenesTest::Create()
{
	this->CreateCharacter();
	this->CreatePlatform();
	SceneGameAbstract::Create();
}

void ScenesTest::Collinding()
{

	if (SceneManager::GetActiveGameScene()->GetPlayer()->GetComponent<RigidBody2D>(), SceneManager::GetActiveGameScene()->GetPlatform()->GetComponent<RigidBody2D>())
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

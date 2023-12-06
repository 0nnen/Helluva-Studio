#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Managers/SceneManager.h"
#include "Components/SpriteRenderer.h"
#include "Components/RigidBody2D.h"
GameObject* BuilderEntityGameObject::CreateBulletGameObject(const std::string& _name, const sf::Texture& _textureBullet, const float& _scalex, const float& _scaley, GameObject* _player)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_player->GetPosition().GetX(), _player->GetPosition().GetY()));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_textureBullet);
	sprite->SetScale(_scalex, _scaley);
	sprite->SetSprite();

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	rigidBody2D->SetScale(0.5, 0.5);

	return gameObject;

}
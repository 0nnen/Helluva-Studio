#include "Components/ComponentsGame/FireBullet.h"
#include "Scenes/ScenesGame/SceneGameOverworld.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Managers/SceneManager.h"
#include "Components/SquareCollider.h"
FireBullet::FireBullet()
{
	direction = Direction::Right;
	player = SceneManager::GetActiveGameScene()->GetPlayer();
}

void FireBullet::Update(const float& _delta)
{
	Component::Update(_delta);
	if (!SceneGameOverworld::GetFlip())
	{
		SetDirection(Left);
	}
	if (SceneGameOverworld::GetFlip())
	{
		SetDirection(Right);

	}

	cooldown += _delta;
	if (SquareCollider::IsColliding(*(player->GetComponent<SquareCollider>()), *(GetOwner()->GetComponent<SquareCollider>())))
	{
		player->GetComponent<Character>()->TakeDamage(20);
		SceneManager::GetActiveGameScene()->RemoveGameObject(GetOwner());
		std::cout << player->GetComponent<Character>()->GetHealthPoint();

	}
	if (cooldown >= 5.0f)
	{
		SceneManager::GetActiveGameScene()->RemoveGameObject(GetOwner());
	}


};

void FireBullet::AddAnimation(const std::string& _name, Animation* animation)
{
	sf::Texture* texture = new sf::Texture();
	if (animations.find(_name) == animations.end())
	{
		animations.insert(std::make_pair(_name, animation));
	}
}

Animation* FireBullet::GetAnimation(const std::string& _name)
{
	if (animations.find(_name) != animations.end())
	{
		return animations.at(_name);
	}
	return nullptr;
}
Animation* FireBullet::GetAndSetAnimation(const std::string& _name)
{
	if (animations.find(_name) != animations.end())
	{
		actualAnimation = animations.at(_name);
		return actualAnimation;
	}
	return nullptr;
}


void FireBullet::SetDirection(Direction _newDirection) {
	direction = _newDirection;
	if (direction == Direction::Left)
		{
            GetOwner()->SetScale(Maths::Vector2f(-std::abs(GetOwner()->GetScale().x), GetOwner()->GetScale().y));
		}
		else if (direction == Direction::Right)
		{
            GetOwner()->SetScale(Maths::Vector2f(std::abs(GetOwner()->GetScale().x), GetOwner()->GetScale().y));
		}
}

void FireBullet::Collision()
{

};

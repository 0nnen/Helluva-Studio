#include "Components/ComponentsGame/LavaArea.h"
#include <Components/RigidBody2D.h>
#include <Managers/SceneManager.h>
#include <Components/Entity/Character.h>

LavaArea::LavaArea()
{
	player = SceneManager::GetActiveGameScene()->GetPlayer();
}

void LavaArea::Update(const float& _delta)
{
	Component::Update(_delta);
	cooldown += _delta;
	if (RigidBody2D::IsColliding(*(player->GetComponent<RigidBody2D>()), *(GetOwner()->GetComponent<RigidBody2D>())))
		{
				player->GetComponent<Character>()->TakeDamage(10 * _delta);
				
		}
	if (cooldown >= 15.0f)
	{
		player->GetComponent<Character>()->TakeDamage(10);
		SceneManager::GetActiveGameScene()->RemoveGameObject(GetOwner());
	}
	
}


void LavaArea::AddAnimation(const std::string& _name, Animation* animation)
{
	sf::Texture* texture = new sf::Texture();
	if (animations.find(_name) == animations.end())
	{
		animations.insert(std::make_pair(_name, animation));
	}
}

Animation* LavaArea::GetAnimation(const std::string& _name)
{
	if (animations.find(_name) != animations.end())
	{
		return animations.at(_name);
	}
	return nullptr;
}
Animation* LavaArea::GetAndSetAnimation(const std::string& _name)
{
	if (animations.find(_name) != animations.end())
	{
		actualAnimation = animations.at(_name);
		return actualAnimation;
	}
	return nullptr;
}

LavaArea::~LavaArea()
{
}

void LavaArea::Render(sf::RenderWindow* _window) {
	Component::Render(_window);
}


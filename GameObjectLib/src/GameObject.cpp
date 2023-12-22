#include "GameObject.h"
#include <iostream>
#include "Components/Transform.h"
GameObject::GameObject()
{
	this->isActive = true;
	this->transform = new Transform();
}

GameObject::~GameObject()
{

	for (const Component* component : components)
	{
		if (component) delete component;
	}
	components.clear();
}

Transform* GameObject::GetTransform() const { return transform; }

Maths::Vector2f GameObject::GetPosition() const { return transform->GetPosition(); }
void GameObject::SetPosition(Maths::Vector2f _newPosition) { transform->SetPosition(_newPosition); }

Maths::Vector2<float> GameObject::GetScale() const { return transform->GetScale(); }
void GameObject::SetScale(Maths::Vector2f _newScale) { transform->SetScale(_newScale); }

float GameObject::GetRotation() const { return transform->GetRotation(); }
void GameObject::SetRotation(float _newRotation) { transform->SetRotation(_newRotation); }

void GameObject::AddComponent(Component* _component)
{
	_component->SetOwner(this);
	components.push_back(_component);
}

void GameObject::RemoveComponent(Component* _component)
{

	components.erase(std::remove(components.begin(), components.end(), _component), components.end());
	delete _component;

}

void GameObject::SetDepth(const float& _depth)
{
	if (depth >= 0.f)
	{
		depth = _depth;
		while (depth > 1.f)
		{
			depth /= 10.f;
		}
	}
	else
	{
		depth = 0;
	}
}

void GameObject::Start()
{
	for (Component* const& component : components)
	{
		component->Start();
	}
}

void GameObject::Physics(const float& _delta) const
{
	if (this->isActive)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			if (components[i]->GetActive()) {
				components[i]->Physics(_delta);
			}
		}
	}
}

void GameObject::Update(const float& _delta) const
{
	if (this->isActive)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			if (components[i]->GetActive()) {
				components[i]->Update(_delta);
			}
		}
	}
}

void GameObject::Render(sf::RenderWindow* _window) const
{
	if (this->isVisible) {
		for (size_t i = 0; i < components.size(); i++)
		{
			if (components[i]->GetVisible())
			{
				if (layerType == LayerType::Normal)
				{
					components[i]->Render(_window);
				}
				else if (layerType == LayerType::HUD)
				{
					components[i]->RenderGUI(_window);
				}
				else if (layerType == LayerType::Background)
				{
					components[i]->RenderBackground(_window);
				}
			}
		}
	}
}


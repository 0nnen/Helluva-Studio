#include "GameObject.h"
#include <iostream>

GameObject::GameObject() 
{
	this->isActive = true;
	this->transform = new Transform();
}

GameObject::~GameObject()
{
	
	for (const Component* component : components)
	{
		if(component) delete component;
	}
	if(transform) delete transform;
	components.clear();
}

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

void GameObject::Update(const float& _delta) const
{
	if (this->isActive)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			components[i]->Update(_delta);
		}
	}
}

void GameObject::Render(sf::RenderWindow* _window) const
{
	if (this->isVisible) {
		for (Component* const& component : components)
		{
			if (layerType == LayerType::Normal)
			{
				component->Render(_window);
			}
			else if (layerType == LayerType::HUD)
			{
				component->RenderGUI(_window);
			}
			else if (layerType == LayerType::Background)
			{
				component->RenderBackground(_window);
			}
		}
	}
}


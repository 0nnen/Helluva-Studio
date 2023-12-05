#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Command
{
public:
	Command();
	Command(GameObject* _entity);
	
	virtual void Execute(const float& delta) = 0;

	~Command();
protected:
	GameObject* entity;
};


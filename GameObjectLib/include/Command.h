#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Command
{
public:
	Command();
	
	virtual void Execute(const float& _delta) = 0;

	~Command();
};


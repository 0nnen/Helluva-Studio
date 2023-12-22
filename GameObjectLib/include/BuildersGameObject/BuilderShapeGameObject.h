#pragma once
#include "Scene.h"

class BuilderShapeGameObject
{
public:

	static GameObject* CreateCarreGameObject(const std::string& name, const float& _positionx, const float& _positiony);
	static GameObject* CreateCollisionGameObject(const std::string& _name, const float& _positionx, const float& _positiony, const float& _width, const float& _height);
};


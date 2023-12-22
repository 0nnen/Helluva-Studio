#include "BuildersGameObject/BuilderShapeGameObject.h"
#include "Components/RigidBody2D.h"
#include "Scenes/SceneGameAbstract.h"
#include "Managers/SceneManager.h"
#include "Managers/WindowManager.h"
#include "Components/Shapes/Carre.h"
#include "Components/SquareCollider.h"
#include "Components/Shapes/Rectangle.h"

GameObject* BuilderShapeGameObject::CreateCarreGameObject(const std::string& _name, const float& _positionx, const float& _positiony)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_positionx, _positiony));
	gameObject->SetActive(false);
	
	RigidBody2D* rigidBody = gameObject->CreateComponent<RigidBody2D>();
	rigidBody->SetIsGravity(false);

	Carre* carre = gameObject->CreateComponent<Carre>();
	carre->SetSize(10);
	carre->SetOrigin();

	return gameObject;
};

GameObject* BuilderShapeGameObject::CreateCollisionGameObject(const std::string& _name, const float& _positionx, const float& _positiony, const float& _width, const float& _height)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_positionx, _positiony));
	gameObject->SetActive(false);

	RigidBody2D* rigidBody = gameObject->CreateComponent<RigidBody2D>();
	rigidBody->SetIsGravity(false);
	rigidBody->SetSize(Maths::Vector2f(_width, _height));

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetHeightCollider(_height);
	squareCollider->SetWidthCollider(_width);


	return gameObject;
};
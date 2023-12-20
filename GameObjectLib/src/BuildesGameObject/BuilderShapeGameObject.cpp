#include "BuildersGameObject/BuilderShapeGameObject.h"
#include "Components/RigidBody2D.h"
#include "Scenes/SceneGameAbstract.h"
#include "Managers/SceneManager.h"
#include "Managers/WindowManager.h"
#include "Components/Shapes/Carre.h"

GameObject* BuilderShapeGameObject::CreateCarreGameObject(const std::string& _name, float _positionx, float _positiony)
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
#include "BuilderGameObject.h"
#include "Managers/SceneManager.h"
#include "Managers/WindowManager.h"

#include "Components/Entity.h"
#include "Components/HealthPointBar.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Components/UIElements/Button.h"
#include "Components/UIElements/Input.h"
#include "Components/UIElements/Slider.h"
#include "Components/Shapes/Carre.h"
#include "Components/Entity/Character.h"
#include "Components/Inputs/InputCharacter.h"



//GAME ELEMENT

GameObject* BuilderGameObject::CreateButtonGameObject(const std::string& _name, const float& _x, const float& _y, const unsigned int& _fontSize)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetActive(true);
	gameObject->SetVisible(true);
	gameObject->SetLayer(LayerType::HUD);
	gameObject->SetDepth(1.f);

	Button* button = gameObject->CreateComponent<Button>();
	button->SetPosition(_x, _y);
	button->SetFontSize(_fontSize);
	button->SetText(_name, sf::Color::Black);
	button->SetOrigin();

	return gameObject;
}

GameObject* BuilderGameObject::CreateBackgroundGameObject(const std::string& _name, const float& _x, const float& _y, const sf::Texture& _texture)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetDepth(0.f);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);

	float scalerX = (float)WindowManager::GetWindowWidth() / _texture.getSize().x;
	float scalerY = (float)WindowManager::GetWindowHeight() / _texture.getSize().y;
	sprite->SetScale(scalerX, scalerY);
	sprite->SetOrigin();
	sprite->SetSprite();

	return gameObject;
}


GameObject* BuilderGameObject::CreateSliderGameObject(const std::string& _name, const float& _x, const float& _y, const float& _widthBar, const float& _heightBar, const float& _widthCursor, const float& _heightCursor, const unsigned int& _fontSize, const float& _data, const float& _maxData)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	Slider* slider = gameObject->CreateComponent<Slider>();
	slider->SetMaxData(_maxData);
	slider->SetData(_data);
	slider->SetSizeBar(_widthBar, _heightBar);
	slider->SetSizeCursor(_widthCursor, _heightCursor);
	slider->SetCursorText(_fontSize);
	slider->SetTitleText();
	slider->SetPosition(_x, _y);

	return gameObject;
}

GameObject* BuilderGameObject::CreateSliderGameObject(const std::string& _name, const float& _x, const float& _y, const float& _widthBar, const float& _heightBar, const float& _widthCursor, const float& _heightCursor, const unsigned int& _fontSize, const float& _data, const float& _minData, const float& _maxData)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	Slider* slider = gameObject->CreateComponent<Slider>();
	slider->SetMaxData(_maxData);
	slider->SetMinData(_minData);
	slider->SetData(_data);
	slider->SetSizeBar(_widthBar, _heightBar);
	slider->SetSizeCursor(_widthCursor, _heightCursor);
	slider->SetCursorText(_fontSize);
	slider->SetTitleText();
	slider->SetPosition(_x, _y);

	return gameObject;
}

GameObject* BuilderGameObject::CreateInputGameObject(const std::string& _name, const float& _x, const float& _y)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	Input* input = gameObject->CreateComponent<Input>();
	input->SetInput(50);
	input->SetPosition(_x, _y);
	input->SetOrigin();
	input->SetSize(WindowManager::GetFloatWindowWidth() / 1.5, WindowManager::GetFloatWindowHeight() / 8);

	return gameObject;
}


GameObject* BuilderGameObject::CreateCharacterGameObject(const std::string& _name, float _x, float _y, const sf::Texture texture, float scalex, float scaley)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));


	Character* character = gameObject->CreateComponent<Character>();

	/*Armes* arme = gameObject->CreateComponent<Armes>();
	arme->SetDamage(player->GetDamage());*/

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	//Gravity* gravity = gameObject->CreateComponent<Gravity>();

	InputCharacter* inputCharacter = gameObject->CreateComponent<InputCharacter>();
	inputHandlerPlayer = inputCharacter;

	/*HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(player->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(player->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(sprite->GetBounds().y / 2 + 50.f);
	healthPointBar->SetSize(sprite->GetBounds().x, 5);
	healthPointBar->SetScale(scalex, scaley);
	healthPointBar->SetHealthPointBar();*/

	return gameObject;
}
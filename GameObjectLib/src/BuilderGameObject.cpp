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



//GAME ELEMENT

GameObject* BuilderGameObject::CreateButtonGameObject(const std::string& _name, const float& _x, const float& _y, const unsigned int& _fontSize)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	Button* button = gameObject->CreateComponent<Button>();
	button->SetPosition(_x, _y);
	button->SetFontSize(_fontSize);
	button->SetOrigin();

	return gameObject;
}

GameObject* BuilderGameObject::CreateBackgroundGameObject(const std::string& _name, const float& _x, const float& _y, const sf::Texture& _texture)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);

	float scalerX = (float)WindowManager::GetWindowWidth() / _texture.getSize().x;
	float scalerY = (float)WindowManager::GetWindowHeight() / _texture.getSize().y;
	sprite->SetScale(scalerX, scalerY);
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
#include "BuilderGameObject.h"
#include "Managers/SceneManager.h"
#include "Managers/WindowManager.h"

#include "Components/Entity.h"
#include "Components/HealthPointBar.h"
#include "Components/SpriteRenderer.h"
#include "Components/UIElements/Button.h"
#include "Components/UIElements/Input.h"
#include "Components/UIElements/Slider.h"
#include "Components/Shapes/Carre.h"



//GAME ELEMENT

GameObject* BuilderGameObject::CreateButtonGameObject(const std::string& _name, const float& _x, const float& _y, const float& _scaleX, const float& _scaleY, const float& _frameWidth, const float& _frameHeight, const float& _totalFrameWidth, const float& _totalFrameHeight, sf::Texture* _texture, const unsigned int& _fontSize)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetActive(true);
	gameObject->SetVisible(true);
	gameObject->SetLayer(LayerType::HUD);
	gameObject->SetDepth(1.f);
	gameObject->SetScale(Maths::Vector2f(_scaleX, _scaleY));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);
	sprite->SetScale(_scaleX, _scaleY);

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	rigidBody2D->SetIsGravity(false);

	sprite->SetRecTexture(_frameWidth, _frameHeight, sprite->GetBounds().x / _totalFrameWidth, sprite->GetBounds().y / _totalFrameHeight);

	Button* button = gameObject->CreateComponent<Button>();
	button->SetIsBackgroundNeeded(false);
	button->SetFontSize(_fontSize);
	button->SetPosition(sprite->GetPosition().x, sprite->GetPosition().y);
	button->SetText(_name, sf::Color::White);
	button->SetOrigin();

	return gameObject;
}


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


GameObject* BuilderGameObject::CreateBackgroundGameObject(const std::string& _name, const float& _x, const float& _y, const float& _scalex, const float& _scaley, sf::Texture* _texture)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetDepth(0.f);
	gameObject->SetScale(Maths::Vector2f(_scalex, _scaley));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);
	sprite->SetScale(_scalex, _scaley);

	float scalerX = (float)WindowManager::GetWindowWidth() / _texture->getSize().x;
	float scalerY = (float)WindowManager::GetWindowHeight() / _texture->getSize().y;
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
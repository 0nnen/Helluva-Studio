#include "BuilderGameObject.h"
#include "Managers/SceneManager.h"
#include "Managers/WindowManager.h"

#include "Components/Entity.h"
#include "Components/HealthPointBar.h"
#include "Components/SpriteRenderer.h"

#include "Components/UIElements/Button.h"
#include "Components/UIElements/Input.h"
#include "Components/UIElements/Slider.h"
#include "Components/UIElements/Text.h"

#include "Components/Shapes/Carre.h"
#include "Components/Shapes/Rectangle.h"



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

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);
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

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);
	rigidBody2D->SetSize(Maths::Vector2f(300, 100));

	Button* button = gameObject->CreateComponent<Button>();
	button->SetPosition(_x, _y);
	button->SetFontSize(_fontSize);
	button->SetText(_name, sf::Color::White);
	button->SetOrigin();

	return gameObject;
}

GameObject* BuilderGameObject::CreateButtonGameObject(const std::string& _name, const float& _x, const float& _y, const float& _width, const float& _height, const unsigned int& _fontSize)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetActiveAndVisible(true);
	gameObject->SetLayer(LayerType::HUD);
	gameObject->SetDepth(1.f);

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);
	rigidBody2D->SetSize(Maths::Vector2f(_width, _height));


	Button* button = gameObject->CreateComponent<Button>();
	button->SetPosition(_x, _y);
	button->SetFontSize(_fontSize);
	button->SetText(_name, sf::Color::White);
	button->SetOrigin();

	return gameObject;
}



GameObject* BuilderGameObject::CreateBackgroundGameObject(const std::string& _name, const float& _x, const float& _y, const float& _scalex, const float& _scaley, sf::Texture* _texture)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetDepth(0.f);
	gameObject->SetScale(Maths::Vector2f(_scalex, _scaley));

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);

	return gameObject;
}

GameObject* BuilderGameObject::CreateBackgroundGameObject(const std::string& _name, const float& _x, const float& _y, const Maths::Vector2f& _size, const float& _scalex, const float& _scaley, const LayerType& _layer, const sf::Color& _color)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetScale(Maths::Vector2f(_scalex, _scaley));
	gameObject->SetDepth(0.9f);
	gameObject->SetLayer(_layer);

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);
	rigidBody2D->SetSize(_size);

	Rectangle* rectangle = gameObject->CreateComponent<Rectangle>();
	rectangle->SetColor(_color);

	return gameObject;
}

GameObject* BuilderGameObject::CreateBackgroundGameObject(const std::string& _name, const float& _x, const float& _y, const float& _scalex, const float& _scaley, sf::Texture* _texture, int _number)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetDepth(0.f);
	gameObject->SetScale(Maths::Vector2f(_scalex, _scaley));

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);

	return gameObject;
}

GameObject* BuilderGameObject::CreateBackgroundGameObject(const std::string& _name, const float& _x, const float& _y, const float& _scalex, const float& _scaley, sf::Texture* _texture, int _number, const float& _depth)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetDepth(_depth);
	gameObject->SetScale(Maths::Vector2f(_scalex, _scaley));

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);

	return gameObject;
}

GameObject* BuilderGameObject::CreateSliderGameObject(const std::string& _name, const float& _x, const float& _y, const float& _widthBar, const float& _heightBar, const float& _widthCursor, const float& _heightCursor, const unsigned int& _fontSize, const float& _data, const float& _maxData)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);

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

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);

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

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);

	Input* input = gameObject->CreateComponent<Input>();
	input->SetInput(50);
	input->SetPosition(_x, _y);
	input->SetOrigin();
	input->SetSize(WindowManager::GetFloatWindowWidth() / 1.5, WindowManager::GetFloatWindowHeight() / 8);

	return gameObject;
}


GameObject* BuilderGameObject::CreateDropDownGameObject(const std::string& _name, const float& _x, const float& _y, std::vector<std::string>& _buttons, const unsigned int& _fontSize)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);

	Button* button = nullptr;

	for (const std::string& _button : _buttons)
	{
		button = gameObject->CreateComponent<Button>();
		button->SetPosition(_x, _y);
		button->SetFontSize(_fontSize);
		button->SetText(_button, sf::Color::White);
		button->SetOrigin();
	}

	return gameObject;
}

GameObject* BuilderGameObject::CreateTextDialogueGameObject(const std::string& _name, const std::string& _firstText, const float& _x, const float& _y, const float& _width, const float& _height, const unsigned int& _fontSize, const sf::Uint32& _style, const sf::Color& _color)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetScale(Maths::Vector2f(1.f, 1.f));
	gameObject->SetLayer(LayerType::HUD);
	gameObject->SetDepth(1.f);

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);
	rigidBody2D->SetSize(Maths::Vector2f(_width, _height));

	Rectangle* rectangle = gameObject->CreateComponent<Rectangle>();
	rectangle->SetColor(sf::Color(0, 0, 0, 112));

	sf::Uint32 styleBold = static_cast<sf::Uint32>(sf::Text::Bold);

	Text* text = gameObject->CreateComponent<Text>();
	text->SetTitle(_name, _fontSize + 12, styleBold, sf::Color::White);
	text->SetText(_firstText, _fontSize, _style, _color);
	text->SetPositionTitle(Maths::Vector2f(_x - _width / 2.f + 10.f, _y - _height / 2.f + 20.f));
	text->SetPositionText(Maths::Vector2f(_x - _width / 2.f + 10.f, _y));

	return gameObject;
}
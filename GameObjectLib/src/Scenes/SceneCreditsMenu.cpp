#include "Managers/SceneManager.h"
#include "Managers/WindowManager.h"
#include "Managers/AssetManager.h"

#include "Scenes/SceneMainMenu.h"
#include "Scenes/SceneCreditsMenu.h"
#include "Components/UIElements/Button.h"
#include "Components/SpriteRenderer.h"
#include "BuilderGameObject.h"

SceneCreditsMenu::SceneCreditsMenu(const std::string& _newName) : Scene(_newName)
{
	this->Awake();
	Scene::Create();
}

void SceneCreditsMenu::Create()
{
	Scene::Create();
	sf::Texture backgroundTexture2;

	GameObject* background2 = BuilderGameObject::CreateBackgroundGameObject("Background2", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, 1.0f, 1.0f, AssetManager::GetAsset("BackgroundCredits"));
	this->CreateSceneButtonsMenu();
	this->LoadCreditsTexture();
	imagesCredits.clear();
	texteCredits.clear();
}

void SceneCreditsMenu::Preload()
{
	AssetManager::AddAsset("BackgroundCredits", "Assets/Graphics/Backgrounds/bgMenu.png");

}

void SceneCreditsMenu::Render(sf::RenderWindow* _window)
{
	Scene::Render(_window);
}


void SceneCreditsMenu::CreateSceneButtonsMenu()
{
	creditsButton = BuilderGameObject::CreateButtonGameObject("Crédits", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 13, 50);
	backButton = BuilderGameObject::CreateButtonGameObject("Retour", WindowManager::GetWindowWidth() / 15, WindowManager::GetWindowHeight() / 13, 20);
}

void SceneCreditsMenu::LoadCreditsTexture()
{
	for (size_t i = 0; i < 6; i++)
	{
		//imagesCredits.push_back(BuilderGameObject::CreateDecorObject("TextureCredits1", WindowManager::GetWindowWidth() / 1.7, -500.0f, 0.5, 0.5, *AssetManager::GetAsset("credits" + std::to_string(i))));
		texteCredits.push_back(BuilderGameObject::CreateButtonGameObject(allTexteCredits[i], WindowManager::GetWindowWidth() / 1.7, -500.0f, 20));
	}
}

void SceneCreditsMenu::SetOrigin()
{
	text.setOrigin(sf::Vector2f(WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2));
}

void SceneCreditsMenu::AnimCredits(const float& _deltaSeconds, const float& _iteration, const int& _totalLoop)
{
	startPosFrancoisX = imagesCredits[0]->GetPosition().x;
	startPosFrancoisY = imagesCredits[0]->GetPosition().y;

	Maths::Vector2f pointA(startPosFrancoisX, startPosFrancoisY);
	Maths::Vector2f pointB(WindowManager::GetWindowWidth() / 1.7, 500.0f);

	Maths::Vector2f playerPosition = pointA;
	Maths::Vector2f displacement = pointB - pointA;

	if (_deltaSeconds < _totalLoop)
	{
		this->imagesCredits[0]->SetPosition(playerPosition += (displacement / 1.0f) * _deltaSeconds);
		this->texteCredits[0]->SetPosition(playerPosition += (displacement / 1.0f) * _deltaSeconds);
	}
	else if (_deltaSeconds > _totalLoop + 4)
	{
		if (startPosFrancoisX > -250.f)
		{
			this->imagesCredits[0]->SetPosition(playerPosition += (Maths::Vector2f::DiagonaleLeft / 0.5f) * _deltaSeconds);
			this->texteCredits[0]->SetPosition(playerPosition + Maths::Vector2f::DiagonaleLeft * _deltaSeconds);
		}
		else
		{
			imagesCredits.erase(imagesCredits.begin());
			texteCredits.erase(texteCredits.begin());
			goodPosCredits = true;
		}
	}
}

void SceneCreditsMenu::Update(const float& _delta)
{
	Scene::Update(_delta);

	deltaSeconds += _delta;

	if (goodPosCredits)
	{
		deltaSeconds = 0;
		goodPosCredits = false;
	}

	if (!imagesCredits.empty())
	{
		this->AnimCredits(deltaSeconds, iteration, totalLoop);
	}
	else if (imagesCredits.empty())
	{
		this->LoadCreditsTexture();
		this->AnimCredits(deltaSeconds, iteration, totalLoop);
	}

	if (backButton->GetComponent<Button>()->IsClicked())
	{
		SceneManager::RunScene("SceneMainMenu");
	}
}

GameObject* SceneCreditsMenu::CreateCreditsGameObject(const std::string& name, const float& _x, const float& _y, sf::Texture* texture, const float& scalex, const float& scaley)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	return gameObject;
}

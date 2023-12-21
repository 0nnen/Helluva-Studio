#include<iostream>
#include "Scenes/SceneOpening.h"
#include "Managers/WindowManager.h"
#include "Managers/AssetManager.h"
#include "Managers/SceneManager.h"

SceneOpening::SceneOpening() : Scene(std::string("SceneOpening")) {}
SceneOpening::SceneOpening(const std::string& _name) : Scene(_name){}

void SceneOpening::Preload()
{
    Scene::Preload();
    AssetManager::AddAsset("HelluvaStudioLogo", "Assets/Graphics/UI/Icons/Helluva_Logo.png");
    AssetManager::AddAsset("HellEngine", "Assets/Graphics/UI/Icons/HellEngine.png");
    AssetManager::AddAsset("Warning", "Assets/Graphics/UI/Icons/warning_content.jpg");
}

void SceneOpening::Create() 
{
    Scene::Create();
    const float widthWindow = WindowManager::GetFloatWindowWidth();
    const float heightWindow = WindowManager::GetFloatWindowHeight();
    sf::Sprite* spriteLogo = new sf::Sprite();
    spriteLogo->setTexture(*AssetManager::GetAsset("HelluvaStudioLogo"));
    spriteLogo->setPosition(widthWindow / 2, heightWindow / 2);
    spriteLogo->setOrigin(spriteLogo->getLocalBounds().width / 2, spriteLogo->getLocalBounds().height / 2);
    spriteLogo->setScale(1.2, 1.2);
    
   
    sf::Sprite* spriteEngine = new sf::Sprite();
    spriteEngine->setTexture(*AssetManager::GetAsset("HellEngine"));
    spriteEngine->setPosition(widthWindow / 2, heightWindow / 2);
    spriteEngine->setOrigin(spriteEngine->getLocalBounds().width / 2, spriteEngine->getLocalBounds().height / 2);
    spriteEngine->setScale(1.2, 1.2);

    sf::Sprite* spriteWarning = new sf::Sprite();
    spriteWarning->setTexture(*AssetManager::GetAsset("Warning"));
    spriteWarning->setPosition(widthWindow / 2, heightWindow / 2);
    spriteWarning->setOrigin(spriteWarning->getLocalBounds().width / 2, spriteWarning->getLocalBounds().height / 2);
    spriteWarning->setScale(1.3, 1.3);

    sprites.push_back(spriteLogo);
    sprites.push_back(spriteEngine);
    sprites.push_back(spriteWarning);
    fadeInTimeDefault = 0.2f;
    fadeOutTimeDefault = 0.3f;
    isFadeIn = true;
    isFadeOut = false;

    progressBar.setSize(sf::Vector2f(300, 20));
    progressBar.setPosition(widthWindow / 2 - 150, heightWindow - 50);
    progressBar.setFillColor(sf::Color::Green);
}

void SceneOpening::Delete()
{
	Scene::Delete();
    for (sf::Sprite* sprite : sprites)
    {
        if (sprite) delete sprite;
    }
    sprites.clear();
    AssetManager::DeleteAsset("HelluvaStudioLogo");
    AssetManager::DeleteAsset("HellEngine");
    AssetManager::DeleteAsset("Warning");
}

void SceneOpening::Awake()
{
	Scene::Awake();
}

void SceneOpening::Update(const float& _delta)
{
	Scene::Update(_delta);
    if (actualSprite < 3) {
        if (!isFadeOut && isFadeIn && !isPauseTime)
        {
            if (FadeIn(_delta))
            {
                isFadeOut = true;
                isPauseTime = true;
            }
        } 
        if (!isFadeIn && isFadeOut && !isPauseTime)
        {
            if (FadeOut(_delta))
            {
                isFadeIn = true;
                actualSprite++;
            }
        }
        if (isPauseTime)
        {
            actualTime += _delta;
            if (actualTime > pauseTime)
            {
                actualTime = 0.f;
                isPauseTime = false;
            }
        }
    }
    else
    {
        Delete();
        SceneManager::RunScene("SceneMainMenu");
    }

    float fillRate = 1.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        progressBarFill += fillRate * _delta;
        if (progressBarFill > 1.0f) {
            progressBarFill = 1.0f;
            Delete();
            SceneManager::RunScene("SceneMainMenu");
            return;
        }
    }
    else {
        progressBarFill -= fillRate * _delta;
        if (progressBarFill < 0.0f) progressBarFill = 0.0f;
    }

    progressBar.setSize(sf::Vector2f(300 * progressBarFill, 20));
}

void SceneOpening::Render(sf::RenderWindow* _window)
{
    if (actualSprite < 3) {
        _window->draw(*sprites[actualSprite]);
    }

    _window->draw(progressBar);

    Scene::Render(_window);
}
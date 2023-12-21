#include "Components/UIElements/Text.h"
#include "Managers/FontManager.h"

#include <iostream>
#include <fstream>

Text::Text()
{
	sf::Uint32 styleBold = static_cast<sf::Uint32>(sf::Text::Bold);
	sf::Uint32 styleRegular = static_cast<sf::Uint32>(sf::Text::Regular);
	displayText.setFont(*FontManager::GetFont("PixelNES"));
	title.setFont(*FontManager::GetFont("PixelNES"));
	SettingText(displayText, "", 16, styleRegular, sf::Color::White);
	SettingText(title, "", 28, styleBold, sf::Color::White);
}

void Text::SettingText(sf::Text& _text, const std::string& _string, const unsigned int& _fontSize, const sf::Uint32& _style, const sf::Color& _color)
{
	_text.setString(_string);
	_text.setCharacterSize(_fontSize);
	_text.setStyle(_style);
	_text.setFillColor(_color);
	_text.setOrigin(0, _text.getLocalBounds().height / 2);
}

void Text::SetTitle(const std::string& _text, const unsigned int& _fontSize, const sf::Uint32& _style, const sf::Color& _color)
{
	SettingText(title, _text, _fontSize, _style, _color);
}
void Text::SetText(const std::string& _text, const unsigned int& _fontSize, const sf::Uint32& _style, const sf::Color& _color)
{
	SettingText(displayText, "", _fontSize, _style, _color);
	finalTexts.push_back(_text);
}
void Text::LoadTextFromFile(const std::string& _fileName)
{

	std::ifstream file(_fileName);

	if (file.is_open()) {
		std::string line;

		// Boucle sur chaque ligne du file
		while (std::getline(file, line)) {
			finalTexts.push_back(line);
		}

		// Fermer le fichier une fois que vous avez fini de le lire
		file.close();
	}
	else
	{
		std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
	}

}

void Text::AddText(const std::string& _text)
{
	finalTexts.push_back(_text);
}

void Text::SetDisplayText(const std::string& _text)
{
	displayText.setString(_text);
}

void Text::Render(sf::RenderWindow* _window)
{
	const Maths::Vector2f scale = GetOwner()->GetScale();

	displayText.setPosition(sf::Vector2f(positionText.x, positionText.y));
	displayText.setScale(sf::Vector2f(scale.x, scale.y));

	title.setPosition(sf::Vector2f(positionTitle.x, positionTitle.y));
	title.setScale(sf::Vector2f(scale.x, scale.y));

	Component::Render(_window);
	_window->draw(displayText);
	_window->draw(title);
}

void Text::RenderGUI(sf::RenderWindow* _window)
{
	const Maths::Vector2f scale = GetOwner()->GetScale();

	displayText.setPosition(sf::Vector2f(positionText.x, positionText.y));
	displayText.setScale(sf::Vector2f(scale.x, scale.y));

	title.setPosition(sf::Vector2f(positionTitle.x, positionTitle.y));
	title.setScale(sf::Vector2f(scale.x, scale.y));

	Component::RenderGUI(_window);
	_window->draw(displayText);
	_window->draw(title);
}

void Text::Update(const float& _delta)
{
	if (textIndex < finalTexts.size())
	{
		std::string actualText = finalTexts[textIndex];
		totalDuration = actualText.length() * 0.03;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (!isDone)
			{
				displayText.setString(actualText);
				currentTime = 0.f;
				isDone = true;
				charIndex = 0;
			}
		}

		if (!isDone)
		{
			if (charIndex < actualText.length()) {
				// Calculer le pourcentage du temps écoulé par rapport à la durée totale
				float progress = currentTime / totalDuration;

				// Calculer le nombre de caractères à afficher en fonction du pourcentage de progression
				unsigned int charsToShow = static_cast<unsigned int>(progress * actualText.length());
				// Mettre à jour le texte avec les caractères à afficher
				displayText.setString(actualText.substr(0, charsToShow));
				charIndex = charsToShow;
			}
			else
			{
				displayText.setString(actualText);
				currentTime = 0.f;
				isDone = true;
				charIndex = 0;
			}
		}
		else
		{
			if (currentTime >= pauseDuration)
			{
				displayText.setString("");
				currentTime = 0.f;
				isDone = false;
				charIndex = 0;
				textIndex++;
			}
		}
	}
	else
	{
		if (currentTime >= pauseDuration)
		{
			GetOwner()->SetActiveAndVisible(false);
		}
	}
	currentTime += _delta;
}

Text::~Text() {}

#include "Managers/HUDManager.h"
#include "Managers/WindowManager.h"

 sf::View HUDManager::hudView;
 std::vector<GameObject* > HUDManager::hudGameObjects;

 std::vector<sf::Vector2f> HUDManager::line;
 std::vector<sf::Vector2f> HUDManager::column;
 float HUDManager::widthRectange = 0.f;
 float HUDManager::heightRectangle = 0.f;
 std::map<std::string, sf::Vector2f> HUDManager::centerRectangle;
 bool HUDManager::isShown = false;


 void HUDManager::Init(sf::RenderWindow* _window)
 {
	 HUDManager::hudView = _window->getDefaultView();
 }
 void HUDManager::Preload()
 {
	 int width = WindowManager::GetWindowWidth();
	 int height = WindowManager::GetWindowHeight();
	 HUDManager::GetHud().setSize(width, height);
	 HUDManager::GetHud().setCenter(width / 2, height / 2);
	 for (int i = 0; i < 16; i++)
	 {
		 HUDManager::column.push_back(sf::Vector2f(width / 16 * i, width / 16 * (i + 1)));
	 }
	 for (int i = 0; i < 9; i++)
	 {
		 HUDManager::line.push_back(sf::Vector2f(height / 9 * i, height / 9 * (i + 1)));
	 }
	 HUDManager::widthRectange = HUDManager::column[0].y;
	 HUDManager::heightRectangle = HUDManager::line[0].y;
	 int j = 0;
	 for (sf::Vector2f line_ : HUDManager::line)
	 {
		 for (sf::Vector2f column_ : HUDManager::column)
		 {
			 HUDManager::centerRectangle.insert(std::make_pair(std::to_string(j), sf::Vector2f(line_.x + (line_.y - line_.x) / 2, column_.x + (column_.y - column_.x) / 2)));
			 j++;
		 }
	 }
 }

 void HUDManager::Render(sf::RenderWindow* _window)
 {
	 if (HUDManager::isShown)
	 {
		 int j = 0;
		 for (sf::Vector2f line_ : HUDManager::line)
		 {
			 for (sf::Vector2f column_ : HUDManager::column)
			 {
				 const sf::Vector2f centerRectangleJ = HUDManager::centerRectangle.at(std::to_string(j));
				 sf::RectangleShape rectangle;
				 sf::Text text;
				 text.setCharacterSize(20);
				 text.setString(std::to_string(j));
				 text.setFillColor(sf::Color::Red);
				 text.setPosition(centerRectangleJ);
				 text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
				 rectangle.setPosition(centerRectangleJ);
				 rectangle.setOrigin(sf::Vector2f(HUDManager::widthRectange / 2, HUDManager::heightRectangle / 2));
				 rectangle.setSize(sf::Vector2f(HUDManager::widthRectange, HUDManager::heightRectangle));
				 rectangle.setOutlineColor(sf::Color::Red);
				 rectangle.setOutlineThickness(2);
				 rectangle.setFillColor(sf::Color::Transparent);
				 _window->setView(HUDManager::GetHud());
				 _window->draw(rectangle);
				 _window->draw(text);
				 j++;
			 }
		 }
	 }
 }

HUDManager::HUDManager() {}
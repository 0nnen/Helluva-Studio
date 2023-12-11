#include "Scenes/SceneOpening.h"
#include "Managers/WindowManager.h"
#include "Managers/WindowManager.h"

SceneOpening::SceneOpening() : Scene(std::string("SceneOpening")) {}
SceneOpening::SceneOpening(const std::string& _name) : Scene(_name){}

void SceneOpening::Create() {}

int SceneOpening::showOpening(sf::RenderWindow* w) {

       // sf::RenderWindow* f = new sf::RenderWindow(sf::VideoMode(1080, 1000), "Opening Helluva", sf::Style::Fullscreen);
        sf::Texture* textureLogo = new sf::Texture(),
            * texturePegi_16 = new sf::Texture(),
            * textureWarning = new sf::Texture(),
            * textureMenu = new sf::Texture();

        sf::Sprite* spriteLogo = new sf::Sprite(),
            * spritePegi_16 = new sf::Sprite(),
            * spriteWarning = new sf::Sprite(),
            * spriteMenu = new sf::Sprite();

        sf::Color colorSprite;

        int alphaLogo = 0, alphaPegi_16 = 0, alphaMenu = 0, alphaWarning = 0,
            opacityLogo = 255, opacityPegi_16 = 255, opacityWarning = 255, opacityMenu = 255;

        int quit = 0;
        /*int decompte = 10, timeDuration;
        sf::Clock time;*/


        if (!textureLogo->loadFromFile("../Assets/Helluva_Logo2.png")) {
         //   delete f;
            delete textureLogo;
            delete textureWarning;
            delete textureMenu;
            delete texturePegi_16;
            delete spriteLogo;
            delete spritePegi_16;
            delete spriteWarning;
            delete spriteMenu;
            return -1;
        }

        if (!texturePegi_16->loadFromFile("../Assets/PEGI_16.png")) {
           // delete f;
            delete textureWarning;
            delete textureMenu;
            delete texturePegi_16;
            delete spriteLogo;
            delete spritePegi_16;
            delete spriteWarning;
            delete spriteMenu;
            return -1;
        }

        if (!textureWarning->loadFromFile("../Assets/warning2.jpg")) {
            //delete f;
            delete textureWarning;
            delete textureMenu;
            delete spriteLogo;
            delete spritePegi_16;
            delete spriteWarning;
            delete spriteMenu;
            return -1;
        }

        if (!textureMenu->loadFromFile("../Assets/BgMenu.png")) {
            //delete f;
            delete textureMenu;
            delete spriteLogo;
            delete spritePegi_16;
            delete spriteWarning;
            delete spriteMenu;
            return -1;
        }


        spriteLogo->setTexture(*textureLogo);
        spriteLogo->setPosition(700., 300.);
        spriteLogo->setScale(0.7, 0.7);

        spritePegi_16->setTexture(*texturePegi_16);
        spritePegi_16->setPosition(750.,300.);
        spritePegi_16->setScale(0.3, 0.3);

        spriteWarning->setTexture(*textureWarning);
        spriteWarning->setPosition(500, 270.);
        spriteWarning->setScale(1.3, 1.3);

        spriteMenu->setTexture(*textureMenu);
        spriteMenu->setPosition(0., 0.);
        spriteMenu->setScale(1.4, 1.4);
        std::cout << "taile w :" << w->getSize().x << " "<<w->getSize().y << std::endl;
        while (w->isOpen()) {
            sf::Event event;
            while (w->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    w->close();
                }

            }
            /*affiche le logo avec une transparence qui diminue*/
            if (alphaLogo <= 255) {
                colorSprite = spriteLogo->getColor();
                spriteLogo->setColor(sf::Color(colorSprite.r, colorSprite.g, colorSprite.b, alphaLogo));
                alphaLogo = alphaLogo + 15;
                //std::cout << "alphaLogo:" << static_cast<int>(spriteLogo->getColor().a) << " alphaLogo =" << alphaLogo << std::endl;

            }
            if (alphaLogo == 255) {
                sf::sleep(sf::milliseconds(700));
                std::cout << "sleep logo" << std::endl;
            }
            /*affiche le logo avec une transparence qui augmente*/
            if (alphaLogo >= 255) {
                colorSprite = spriteLogo->getColor();
                spriteLogo->setColor(sf::Color(colorSprite.r, colorSprite.g, colorSprite.b, opacityLogo));
                opacityLogo = opacityLogo - 15;
            }
            /*affiche le Pegi 16 avec une transparence qui diminue*/
            if (opacityLogo <= 0) {
                colorSprite = spritePegi_16->getColor();
                spritePegi_16->setColor(sf::Color(colorSprite.r, colorSprite.g, colorSprite.b, alphaPegi_16));
                alphaPegi_16 = alphaPegi_16 + 15;
            }
            if (alphaPegi_16 == 255) {
                sf::sleep(sf::milliseconds(700));
                std::cout << "sleep pegi" << std::endl;
            }
            /*affiche le Pegi 16 avec une transparence qui augmente*/
            if (alphaPegi_16 >= 255) {
                colorSprite = spritePegi_16->getColor();
                spritePegi_16->setColor(sf::Color(colorSprite.r, colorSprite.g, colorSprite.b, opacityPegi_16));
                opacityPegi_16 = opacityPegi_16 - 15;
            }
            /*affiche le message de warning avec une transparence qui diminue*/
            if (opacityPegi_16 <= 0) {
                colorSprite = spriteWarning->getColor();
                spriteWarning->setColor(sf::Color(colorSprite.r, colorSprite.g, colorSprite.b, alphaWarning));
                alphaWarning = alphaWarning + 15;
            }
            if (alphaWarning == 255) {
                sf::sleep(sf::milliseconds(700));
                std::cout << "sleep warning" << std::endl;
            }
            /*affiche le message de warning avec une transparence qui augmente*/
            if (alphaWarning >= 255) {
                colorSprite = spriteWarning->getColor();
                spriteWarning->setColor(sf::Color(colorSprite.r, colorSprite.g, colorSprite.b, opacityWarning));
                opacityWarning = opacityWarning - 15;
            }
            /*affiche le menu avec une transparence qui diminue*/
            if (opacityWarning <= 0) {
                colorSprite = spriteMenu->getColor();
                spriteMenu->setColor(sf::Color(colorSprite.r, colorSprite.g, colorSprite.b, alphaMenu));
                alphaMenu = alphaMenu + 15;
            }
            if (alphaMenu >= 255) {
                alphaMenu = 255;
            }

            sf::sleep(sf::milliseconds(90));
            w->clear(sf::Color::Black);
            if (opacityLogo >= 0) {
                w->draw(*spriteLogo);
            }
            if ((opacityPegi_16 >= 0) && (opacityLogo <= 0)) {
                w->draw(*spritePegi_16);
            }
            if ((opacityWarning >= 0) && (opacityPegi_16 <= 0) && (opacityLogo <= 0)) {
                w->draw(*spriteWarning);
            }
            if ((opacityWarning <= 0) && (opacityPegi_16 <= 0) && (opacityLogo <= 0)) {
               // w->draw(*spriteMenu);
                //quit = 1;
                //w->display();
                //sf::sleep(sf::milliseconds(1400));
                //w->clear();
                //break;
               
            }
            if (alphaMenu >= 255) {
                //sf::sleep(sf::milliseconds(200));
                break;
            }

            w->display();
       
        }


        delete spriteLogo;
        delete spritePegi_16;
        delete spriteWarning;
        delete spriteMenu;
        delete textureLogo;
        delete textureWarning;
        delete textureMenu;
        delete texturePegi_16;
        //delete f;
        std::cout << "liberation opening";


	return 0;
}

void SceneOpening::Delete()
{
	Scene::Delete();
}

void SceneOpening::Awake()
{
	Scene::Awake();
}

void SceneOpening::Update(const float& _delta)
{
	Scene::Update(_delta);
}

void SceneOpening::Render(sf::RenderWindow* _window)
{
}
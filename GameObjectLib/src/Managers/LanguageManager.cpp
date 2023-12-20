#include "Managers/LanguageManager.h"

#include <iostream>
#include <fstream>

LanguageManager* LanguageManager::instance = nullptr;

LanguageManager* LanguageManager::GetInstance()
{
	if (instance == nullptr)
		instance = new LanguageManager();

	return instance;
}

void LanguageManager::RecoverLanguages(const std::string& _fileName)
{
    std::ifstream fichier(_fileName);

    // Vérifier si l'ouverture a réussi
    if (fichier.is_open()) {
        std::string ligne;

        // Boucle sur chaque ligne du fichier
        while (std::getline(fichier, ligne)) {
            languages.push_back(ligne);
        }

        if (languages.size() > 0) language = languages[0];

        // Fermer le fichier une fois que vous avez fini de le lire
        fichier.close();
    }
    else
    {
        std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
    }
}
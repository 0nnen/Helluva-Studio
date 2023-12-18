#include "TileMap/TileMap.h"

TileMap::TileMap() {}
TileMap::TileMap(const std::string& _jsonFileName, const std::string& _tilesetFileName)
{
	LoadTile(_jsonFileName, _tilesetFileName);
}


void TileMap::LoadTile(const std::string& _jsonFileName, const std::string& _tilesetFileName)
{
	// Lire le fichier JSON de la TileMap
	std::ifstream file(_jsonFileName);
	if (!file.is_open()) {
		std::cerr << "Impossible d'ouvrir le fichier JSON." << std::endl;
		return;
	}

	json tilemapData;
	file >> tilemapData;
	//file.close();

	// Charger le tileset (image des tuiles)
	if (!tileset.loadFromFile(_tilesetFileName)) {
		std::cerr << "Impossible de charger le tileset." << std::endl;
		return;
	}

	// Initialiser la taille des tuiles
	tileWidth = tilemapData["tilewidth"];
	tileHeight = tilemapData["tileheight"];

	sf::Vector2f tileSize = sf::Vector2f(tileWidth, tileHeight);

	// Parcourir les couches de la TileMap et remplir les données de la carte
	for (const auto& layer : tilemapData["layers"]) {
		const auto& name = layer["name"];
		const auto& tiles = layer["data"];
		int width = layer["width"];
		int height = layer["height"];

		sf::VertexArray* layer_vertices = new sf::VertexArray;

		layer_vertices->setPrimitiveType(sf::Quads);
		layer_vertices->resize(width * height * 4);
		// on remplit le tableau de vertex, avec un quad par tuile
		for (unsigned int i = 0; i < width; ++i)
			for (unsigned int j = 0; j < height; ++j)
			{
				// on récupère le numéro de tuile courant
				int tileNumber = tiles[i + j * width] - 1;

				if (tileNumber >= 0) {
					// on en déduit sa position dans la texture du tileset
					int tu = tileNumber % (int)(tileset.getSize().x / tileSize.x);
					int tv = tileNumber / (tileset.getSize().x / tileSize.x);

					// on récupère un pointeur vers le quad à définir dans le tableau de vertex
					sf::Vertex* quad = &(*layer_vertices)[(i + j * width) * 4];

					// on définit ses quatre coins
					quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
					quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
					quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

					// on définit ses quatre coordonnées de texture
					quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
					quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
					quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
					quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
					if (name == "Collision" || name == std::string("Collision") && tileNumber > 0)
					{
						const float marge = 5.f;
						const float factor = 2.f;
						const float epaisseur = marge * factor;
						SquareCollider* squareColliderTop = new SquareCollider();
						squareColliderTop->SetWidthCollider(tileWidth - marge);
						squareColliderTop->SetHeightCollider(epaisseur);
						squareColliderTop->SetPosition(Maths::Vector2f(i * tileSize.x + tileWidth / 2, j * tileSize.y + marge / factor));
						collisionsTop.push_back(squareColliderTop);

						SquareCollider* squareColliderBottom = new SquareCollider();
						squareColliderBottom->SetWidthCollider(tileWidth - marge);
						squareColliderBottom->SetHeightCollider(epaisseur);
						squareColliderBottom->SetPosition(Maths::Vector2f(i * tileSize.x + tileWidth / 2, j * tileSize.y + tileHeight - marge / factor));
						collisionsBottom.push_back(squareColliderBottom);

						SquareCollider* squareColliderLeft = new SquareCollider();
						squareColliderLeft->SetWidthCollider(epaisseur);
						squareColliderLeft->SetHeightCollider(tileHeight - epaisseur);
						squareColliderLeft->SetPosition(Maths::Vector2f(i * tileSize.x + marge , j * tileSize.y + tileHeight / 2));
						collisionsLeft.push_back(squareColliderLeft);

						SquareCollider* squareColliderRight = new SquareCollider();
						squareColliderRight->SetWidthCollider(epaisseur);
						squareColliderRight->SetHeightCollider(tileHeight - epaisseur);
						squareColliderRight->SetPosition(Maths::Vector2f(i * tileSize.x + tileWidth - marge, j * tileSize.y + tileHeight / 2));
						collisionsRight.push_back(squareColliderRight);
					}
				}
			}
		if (name != "Collision")
		{
			mapData.push_back(layer_vertices);
		}
	}
}

void TileMap::Render(sf::RenderWindow* _window) {
	for (int i = 0; i < mapData.size(); ++i) {
		// Appliquer la texture actuelle

		// Dessiner le vertexArray
		_window->draw(*mapData[i], &tileset);
	}
	for (SquareCollider* collision : collisionsRight)
	{
		collision->Render(_window);
	}
	for (SquareCollider* collision : collisionsTop)
	{
		collision->Render(_window);
	}
	for (SquareCollider* collision : collisionsLeft)
	{
		collision->Render(_window);
	}
	for (SquareCollider* collision : collisionsBottom)
	{
		collision->Render(_window);
	}
}
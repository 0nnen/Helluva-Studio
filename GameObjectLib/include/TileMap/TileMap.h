#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Component.h"
#include "Components/RigidBody2D.h"
#include "Components/SquareCollider.h"
using json = nlohmann::json;


class TileMap : public Component {

public:
	TileMap();
	TileMap(const std::string& _jsonFileName, const std::string& _tilesetFileName);

	void LoadTile(const std::string& _jsonFileName, const std::string& _tilesetFileName);
	void Render(sf::RenderWindow* _window) override;


	bool CheckCollisionAbove(const SquareCollider& _entity) {
		for (SquareCollider* collision : collisionsTop)
		{
			if (SquareCollider::IsColliding(*collision, _entity)) return true;
		}
		return false;
	}

	bool CheckCollisionLeft(const SquareCollider& _entity) {
		for (SquareCollider* collision : collisionsLeft)
		{
			if (SquareCollider::IsColliding(*collision, _entity)) return true;
		}
		return false;
	}

	bool CheckCollisionRight(const SquareCollider& _entity) {
		for (SquareCollider* collision : collisionsRight)
		{
			if (SquareCollider::IsColliding(*collision, _entity)) return true;
		}
		return false;
	}

	bool CheckCollisionBelow(const SquareCollider& _entity) {
		for (SquareCollider* collision : collisionsBottom)
		{
			if (SquareCollider::IsColliding(*collision, _entity)) return true;
		}
		return false;
	}

private:
	sf::Texture tileset;
	std::string jsonFile;
	std::vector<sf::VertexArray*> mapData;
	std::vector<SquareCollider*> collisionsTop;
	std::vector<SquareCollider*> collisionsBottom;
	std::vector<SquareCollider*> collisionsLeft;
	std::vector<SquareCollider*> collisionsRight;
	int tileWidth = 0;
	int tileHeight = 0;
};
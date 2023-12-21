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
	TileMap(const std::string& _jsonFileName, const std::string& _tilesetFileName, const int& _idEmptyCollision);

	void LoadTile(const std::string& _jsonFileName, const std::string& _tilesetFileName);
	void LoadIdCollision(const int& _idEmpty);
	void Render(sf::RenderWindow* _window) override;


	SquareCollider* CheckCollisionAbove(const SquareCollider& _entity) {
		for (SquareCollider* collision : collisionsTop)
		{
			if (SquareCollider::IsColliding(*collision, _entity)) return collision;
		}
		return nullptr;
	}

	SquareCollider* CheckCollisionLeft(const SquareCollider& _entity) {
		for (SquareCollider* collision : collisionsLeft)
		{
			if (SquareCollider::IsColliding(*collision, _entity)) return collision;
		}
		return nullptr;
	}

	SquareCollider* CheckCollisionRight(const SquareCollider& _entity) {
		for (SquareCollider* collision : collisionsRight)
		{
			if (SquareCollider::IsColliding(*collision, _entity)) return collision;
		}
		return nullptr;
	}

	SquareCollider* CheckCollisionBelow(const SquareCollider& _entity) {
		for (SquareCollider* collision : collisionsBottom)
		{
			if (SquareCollider::IsColliding(*collision, _entity)) return collision;
		}
		return nullptr;
	}

private:

	inline bool ContainId(std::vector<int> _vectorId, int _id)
	{
		for (const int& id : _vectorId)
		{
			if (_id == id) return true;
		}
		return false;
	}

	sf::Texture tileset;
	std::string jsonFile;
	std::vector<sf::VertexArray*> mapData;
	std::vector<SquareCollider*> collisionsTop;
	std::vector<int> idCollisionsTop;
	std::vector<SquareCollider*> collisionsBottom;
	std::vector<int> idCollisionsBottom;
	std::vector<SquareCollider*> collisionsLeft;
	std::vector<int> idCollisionsLeft;
	std::vector<SquareCollider*> collisionsRight;
	std::vector<int> idCollisionsRight;
	int tileWidth = 0;
	int tileHeight = 0;
};
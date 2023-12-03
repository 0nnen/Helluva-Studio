#pragma once

#include <string>
#include <vector>

#include "Maths/Vector2.h"
#include "Component.h"

enum class LayerType {
	Normal,
	HUD,
	Background
};

class Component;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = default;

	inline std::string GetName() const { return name; }
	inline void SetName(const std::string& _newName) { name = _newName; }

	inline Maths::Vector2f GetPosition() const { return position; }
	inline void SetPosition(Maths::Vector2f _newPosition) { position = _newPosition; }

	inline Maths::Vector2<float> GetScale() const { return scale; }
	inline void SetScale(Maths::Vector2f _newScale) { scale = _newScale; }

	inline float GetRotation() const { return rotation; }
	inline void SetRotation(float _newRotation) { rotation = _newRotation; }

	inline void SetActive(const bool& _state) { isActive = _state; }
	inline bool GetActive() const { return isActive; }

	inline bool GetVisible() const { return isVisible; }
	inline void SetVisible(const bool& _state) { isVisible = _state; }

	inline LayerType GetLayer() const { return layerType; }
	inline void SetLayer(const LayerType& _layerType) { layerType = _layerType; }

	inline float GetDepth() const { return depth; }
	void SetDepth(const float& _depth);

	void AddComponent(Component* _component);

	template<typename T>
	inline T* CreateComponent()
	{
		T* component = new T();
		component->SetOwner(this);
		components.push_back(component);
		return component;
	}


	template<typename T>
	inline T* GetComponent() {
		for (size_t i = 0; i < components.size(); i++) {
			// Vérifie si le composant est un Collider
			T* componentResult = dynamic_cast<T*>(components[i]);
			if (componentResult) {
				return componentResult; // Renvoie le Collider trouvé
			}
		}
		return nullptr; // Renvoie nullptr si aucun Collider n'est trouvé
	}

	void RemoveComponent(Component* _component);

	virtual void Start();
	void Update(const float& _delta) const;
	void Render(sf::RenderWindow* _window) const;

protected:
	std::string name = "GameObject";
	Maths::Vector2f position = Maths::Vector2f::Zero;
	Maths::Vector2f scale = Maths::Vector2f::One;
	float rotation = 0.f;
	std::vector<Component*> components;

	//Quel est le layer du gameObject
	LayerType layerType = LayerType::Normal;
		
	//Plus c'est proche de 1, plus le GameObject sera proche de l'écran
	float depth = 0.f;

	bool isActive = true;
	bool isVisible = true;
};
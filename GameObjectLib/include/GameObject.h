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

class Transform;

class GameObject
{
public:
	GameObject();
	~GameObject();

	inline std::string GetName() const { return name; }
	inline void SetName(const std::string& _newName) { name = _newName; }

	Transform* GetTransform() const;

	 Maths::Vector2f GetPosition() const;
	 void SetPosition(Maths::Vector2f _newPosition);

	 Maths::Vector2<float> GetScale() const;
	 void SetScale(Maths::Vector2f _newScale);

	 float GetRotation() const;
	 void SetRotation(float _newRotation);

	inline void SetActive(const bool& _state) { isActive = _state; }
	inline bool GetActive() const { return isActive; }

	inline bool GetVisible() const { return isVisible; }
	inline void SetVisible(const bool& _state) { isVisible = _state; }

	inline void SetActiveAndVisible(const bool& _state) { isActive = _state; isVisible = _state; }

	inline LayerType GetLayer() const { return layerType; }
	inline void SetLayer(const LayerType& _layerType) { layerType = _layerType; }

	inline float GetDepth() const { return depth; }
	void SetDepth(const float& _depth);

	void AddComponent(Component* _component);

	template<typename T>
	T* CreateComponent()
	{
		T* component = new T();
		component->SetOwner(this);
		components.push_back(component);
		return component;
	}

	inline std::vector<Component*> GetComponents() { return components; }

	template<typename T>
	T* GetComponent() {
		for (size_t i = 0; i < components.size(); i++) {
			// Vérifie si le composant est un Component
			T* componentResult = dynamic_cast<T*>(components[i]);
			if (componentResult) {
				return componentResult; // Renvoie le Component trouvé
			}
		}
		return nullptr; // Renvoie nullptr si aucun Component n'est trouvé
	}

	template<typename T>
	std::vector<T*> GetComponentsByType() {
		std::vector<T*> componentsByType;
		for (size_t i = 0; i < components.size(); i++) {
			// Vérifie si le composant est un Component
			T* componentResult = dynamic_cast<T*>(components[i]);
			if (componentResult) {
				componentsByType.push_back(componentResult); // Ajout le Component trouvé
			}
		}
		return componentsByType;
	}

	void RemoveComponent(Component* _component);

	virtual void Start();
	void Update(const float& _delta) const;
	void Render(sf::RenderWindow* _window) const;

protected:
	std::string name = "GameObject";
	std::vector<Component*> components;

	Transform* transform = nullptr;
	//Quel est le layer du gameObject
	LayerType layerType = LayerType::Normal;

	//Plus c'est proche de 1, plus le GameObject sera proche de l'écran
	float depth = 0.f;

	bool isActive = true;
	bool isVisible = true;
};

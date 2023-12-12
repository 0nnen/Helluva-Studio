#pragma once

#include <iostream>
#include <cmath>
#include "Maths/Vector2.h"

#include "Component.h"

class Transform final: public Component
{
public: 
	// Méthode pour récupérer et définir la position
	inline Maths::Vector2f GetPosition() const { return position; }
	inline void SetPosition(const float& _x, const float& _y) { position = Maths::Vector2f(_x, _y); }
	inline void SetPosition(const Maths::Vector2f& _position) { position = _position; }

	// Méthode pour récupérer et définir la rotation en utilisant un angle
	inline float GetRotation() const { return rotation; }
	inline void SetRotation(float angle) { rotation = angle; }

	// Méthode pour récupérer et définir l'échelle
	inline Maths::Vector2f GetScale() const { return scale; }
	inline void SetScale(const float& _scaleX, const float& _scaleY) { scale = Maths::Vector2f(_scaleX, _scaleY); }
	inline void SetScale(const Maths::Vector2f& _scale) { scale = _scale; }

	Maths::Vector2f TransformPoint() const
	{
		float cosTheta = std::cos(rotation);
		float sinTheta = std::sin(rotation);

		// Matrice de transformation
		float m00 = cosTheta;
		float m01 = -sinTheta;
		float m10 = sinTheta;
		float m11 = cosTheta;
		float m20 = 0.0f;
		float m21 = 0.0f;
		float m22 = 1.0f;

		// Calcul de la transformation
		float x = position.x * m00 + position.y * m01 ;
		float y = position.x * m10 + position.y * m11 ;

		return Maths::Vector2f(x, y);
	}
	// Méthode pour afficher les propriétés du Transform
	void Display();

private:
	Maths::Vector2f position = Maths::Vector2f::Zero;
	Maths::Vector2f scale = Maths::Vector2f::One;
	float rotation = 0.f;
};


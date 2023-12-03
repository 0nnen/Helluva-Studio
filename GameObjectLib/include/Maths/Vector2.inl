#pragma once

#include <cmath>

#pragma warning(push)
#pragma warning(disable : 4244)

namespace Maths
{

	template<typename T>
	Vector2<T>::Vector2() : x(0), y(0) {}

	template<typename T>
	Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

	template<typename T>
	T Vector2<T>::operator[](int& index) const
	{
		if (index == 0)
		{
			return x;
		}
		else if (index == 1)
		{
			return y;
		}
		else
		{
			return 0;
		}
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator+(const Vector2& rhs)
	{
		return Vector2(x + rhs.x, y + rhs.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator-(const Vector2& rhs)
	{
		return Vector2(x - rhs.x, y - rhs.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator-() const
	{
		return Vector2(-x, -y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator*(const Vector2& rhs) const
	{
		return Vector2(x * rhs.x, y * rhs.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator/(const Vector2& rhs) const
	{
		return Vector2(x / rhs.x, y / rhs.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator*(const T& rhs) const
	{
		return Vector2(x * rhs, y * rhs);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator/(const T& rhs) const
	{
		return Vector2(x / rhs, y / rhs);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator+=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator-=(const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator*=(const Vector2& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator/=(const Vector2& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator*=(const T& rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator/=(const T& rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	template<typename T>
	float Vector2<T>::Dot(const Vector2& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	template<typename T>
	float Vector2<T>::Cross(const Vector2& rhs) const
	{
		return x * rhs.y - y * rhs.x;
	}

	template<typename T>
	float Vector2<T>::Magnitude() const
	{
		return sqrt(x * x + y * y);
	}

	template<typename T>
	float Vector2<T>::MagnitudeSquared() const
	{
		return x * x + y * y;
	}

	template<typename T>
	Vector2<T> Vector2<T>::Normalize() const
	{
		return Vector2(x / Magnitude(), y / Magnitude());
	}

	template<typename T>
	float Vector2<T>::Distance(const Vector2<T>& rhs) const
	{
		return std::sqrt((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y));
	}

	template<typename T>
	float Vector2<T>::DistanceSquared(const Vector2& rhs) const
	{
		return (x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y);
	}

	template<typename T>
	float Vector2<T>::Angle(const Vector2& rhs) const
	{
		return std::acos(this->Dot(rhs) / (Magnitude() * rhs.Magnitude()));
	}

	template<typename T>
	Vector2<T> Vector2<T>::Rotate(const T& angle) const
	{
		return Vector2(x * std::cos(angle) - y * std::sin(angle), x * std::sin(angle) + y * std::cos(angle));
	}

	template<typename T>
	float Vector2<T>::Dot(const Vector2& lhs, const Vector2& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	template<typename T>
	Vector2<T> Vector2<T>::Lerp(const Vector2& lhs, const Vector2<T>& rhs, const T& alpha)
	{
		return Vector2(lhs.x * (1 - alpha) + rhs.x * alpha, lhs.y * (1 - alpha) + rhs.y * alpha);
	}

	template<typename T>
	Vector2<T> Vector2<T>::LerpUnclamped(const Vector2& vector2_1, const Vector2& vector2_2, double t)
	{
		T interpolatedX = (1 - t) * vector2_1.x + t * vector2_2.x;
		T interpolatedY = (1 - t) * vector2_1.y + t * vector2_2.y;

		return Vector2(interpolatedX, interpolatedY);
	}

	template<typename T>
	Vector2<T> Vector2<T>::ClampMagnitude(const Vector2& vector, double maxMagnitude)
	{
		double currentMagnitude = vector.Magnitude();

		if (currentMagnitude > maxMagnitude) {
			double scaleFactor = maxMagnitude / currentMagnitude;

			return Vector2(vector.x * scaleFactor, vector.y * scaleFactor);
		}
		return Vector2(vector.x, vector.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::Max(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x > rhs.x ? lhs.x : rhs.x, lhs.y > rhs.y ? lhs.y : rhs.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::Min(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x < rhs.x ? lhs.x : rhs.x, lhs.y < rhs.y ? lhs.y : rhs.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::Reflect(const Vector2& vector2, const Vector2& normal)
	{
		T dotProduct = Dot(vector2, normal);
		T reflectX = vector2.x - 2 * dotProduct * normal.x;
		T reflectY = vector2.y - 2 * dotProduct * normal.y;

		return Vector2(reflectX, reflectY);
	}

	template<typename T>
	Vector2<T> Vector2<T>::Perpendicular(const Vector2& vector2) {
		return Vector2(-vector2.y, vector2.x);
	}

	template<typename T>
	Vector2<T> Vector2<T>::Scale(const Vector2& vector2_1, const Vector2& vector2_2) {
		return Vector2(vector2_1.x * vector2_2.x, vector2_1.y * vector2_2.y);
	}

	template<typename T>
	double Vector2<T>::SignedAngle(const Vector2& from, const Vector2& to) {
		double angle = std::atan2(from.y, from.x) - atan2(to.y, to.x);
		return angle;
	}

	template<typename T>
	T Vector2<T>::GetX()
	{
		return x;
	}

	template<typename T>
	T Vector2<T>::GetY()
	{
		return y;
	}

	template<typename T>
	void Vector2<T>::SetX(const T& new_x)
	{
		x = new_x;
	}

	template<typename T>
	void Vector2<T>::SetY(const T& new_y)
	{
		y = new_y;
	}

	template<typename T>
	void Vector2<T>::SetXY(const T& new_x, const T& new_y)
	{
		x = new_x;
		y = new_y;
	}

	template<typename T>
	void Vector2<T>::SetXY(const Vector2& rhs)
	{
		x = rhs.x;
		y = rhs.y;
	}

	template<typename T>
	const Vector2<T> Vector2<T>::Zero(0, 0);

	template<typename T>
	const Vector2<T> Vector2<T>::One(1, 1);

	template<typename T>
	const Vector2<T> Vector2<T>::UnitX(1, 0);

	template<typename T>
	const Vector2<T> Vector2<T>::UnitY(0, 1);

	template<typename T>
	const Vector2<T> Vector2<T>::Up(0, 1);

	template<typename T>
	const Vector2<T> Vector2<T>::Down(0, -1);

	template<typename T>
	const Vector2<T> Vector2<T>::Left(-1, 0);

	template<typename T>
	const Vector2<T> Vector2<T>::Right(1, 0);

	template<typename T>
	const Vector2<T> Vector2<T>::DiagonaleLeft(-1, 1);


}

#pragma warning(pop)
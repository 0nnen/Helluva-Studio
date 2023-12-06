#include "Components/RigidBody2D.h"


RigidBody2D::RigidBody2D()
{

	gravity = Maths::Vector2f(0.f, -9.8f);
	velocity = Maths::Vector2f::Zero;
	isAffectedByGravity = true;
}
void RigidBody2D::Update(const float& _delta)
{
	if (isAffectedByGravity) 
	{
		Gravity();
		GetOwner()->SetPosition(GetOwner()->GetPosition() + velocity * _delta);
	}

}

void RigidBody2D::Gravity()
{
	velocity += gravity;
}

bool RigidBody2D::IsColliding(const RigidBody2D& _rigidBody2DA, const RigidBody2D& _rigidBody2DB)
{
	const Maths::Vector2f positionA = _rigidBody2DA.GetOwner()->GetPosition();
	const Maths::Vector2f positionB = _rigidBody2DB.GetOwner()->GetPosition();
	return (positionA.x - _rigidBody2DA.GetWidthCollider() / 2 < positionB.x + _rigidBody2DB.GetWidthCollider() / 2 && positionA.x + _rigidBody2DA.GetWidthCollider() / 2 > positionB.x - _rigidBody2DB.GetWidthCollider() / 2 && positionA.y - _rigidBody2DA.GetHeightCollider() / 2 < positionB.y + _rigidBody2DB.GetHeightCollider() / 2 && positionA.y + _rigidBody2DA.GetHeightCollider() / 2 > positionB.y - _rigidBody2DB.GetHeightCollider() / 2);
}

bool RigidBody2D::IsAbove(const RigidBody2D& _rigidBody2DA, const RigidBody2D& _rigidBody2DB)
{
	const Maths::Vector2f positionA = _rigidBody2DA.GetOwner()->GetPosition();
	const Maths::Vector2f positionB = _rigidBody2DB.GetOwner()->GetPosition();
	return positionA.y + _rigidBody2DA.GetHeightCollider() / 2 < positionB.y - _rigidBody2DB.GetHeightCollider() / 2;
}

bool RigidBody2D::IsLeft(const RigidBody2D& _rigidBody2DA, const RigidBody2D& _rigidBody2DB)
{
	const Maths::Vector2f positionA = _rigidBody2DA.GetOwner()->GetPosition();
	const Maths::Vector2f positionB = _rigidBody2DB.GetOwner()->GetPosition();
	return positionA.x + _rigidBody2DA.GetWidthCollider() / 2 < positionB.x - _rigidBody2DB.GetWidthCollider() / 2;
}

bool RigidBody2D::IsRight(const RigidBody2D& _rigidBody2DA, const RigidBody2D& _rigidBody2DB)
{
	const Maths::Vector2f positionA = _rigidBody2DA.GetOwner()->GetPosition();
	const Maths::Vector2f positionB = _rigidBody2DB.GetOwner()->GetPosition();
	return positionA.x - _rigidBody2DA.GetWidthCollider() / 2 > positionB.x + _rigidBody2DB.GetWidthCollider() / 2;
}

bool RigidBody2D::IsBelow(const RigidBody2D& _rigidBody2DA, const RigidBody2D& _rigidBody2DB)
{
	const Maths::Vector2f positionA = _rigidBody2DA.GetOwner()->GetPosition();
	const Maths::Vector2f positionB = _rigidBody2DB.GetOwner()->GetPosition();
	return positionA.y - _rigidBody2DA.GetHeightCollider() / 2 > positionB.y + _rigidBody2DB.GetHeightCollider() / 2;
}
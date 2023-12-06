#include "Components/Transform.h"

void Transform::Display() {
	std::cout << "Position: (" << position.x << ", " << position.y << ")\n";
	std::cout << "Rotation: " << rotation << " degrees\n";
	std::cout << "Scale: (" << scale.x << ", " << scale.y << ")\n";
}
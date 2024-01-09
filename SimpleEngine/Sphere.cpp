#include "Sphere.h"

Sphere::Sphere(const Vector3& pCenter, float pRadius): center(pCenter), radius(pRadius)
{
}

bool Sphere::contains(const Vector3& point) const
{
	float distSq = (center - point).lengthSq();

	return distSq <= (radius * radius);
}

#pragma once
#include "Vector3.h"
#include "Quaternion.h"

struct AABB
{
	AABB(const Vector3& pMin, const Vector3& pMax);

	void updateMinMax(const Vector3& point);
	void rotate(const Quaternion& q);

	bool contains(const Vector3& point) const;
	float minDistSq(const Vector3& point) const;

	Vector3 min;
	Vector3 max;

};


#pragma once
#include "Vector3.h"
#include "LineSegment.h"
#include <functional>
#include <vector>

using std::vector;

class PhysicsSystem
{
public:
	struct CollisionInfo
	{
		// Point of collision
		Vector3 point;
		// Normal at collision
		Vector3 normal;
		// Component collided with
		class BoxCollisionComponent* box;
		// Owning actor of component
		class Actor* actor;

		float distance;
	};


public:
	PhysicsSystem();

	void addBox(class BoxCollisionComponent* box);
	void removeBox(class BoxCollisionComponent* box);
	bool segmentCast(const LineSegment& l, CollisionInfo& outColl);

	// Tests collisions using naive pairwise
	void testPairwise(std::function<void(class Actor*, class Actor*)> f);
	// Test collisions using sweep and prune
	void testSweepAndPrune(std::function<void(class Actor*, class Actor*)> f);

private:
	vector<class BoxCollisionComponent*> boxes;

};


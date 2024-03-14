#include "PhysicsSystem.h"
#include "Collisions.h"
#include "BoxCollisionComponent.h"
#include <algorithm>

PhysicsSystem::PhysicsSystem()
{
}

void PhysicsSystem::addBox(BoxCollisionComponent* box)
{
	boxes.emplace_back(box);
}

void PhysicsSystem::removeBox(BoxCollisionComponent* box)
{
	auto iter = std::find(begin(boxes), end(boxes), box);
	if (iter != end(boxes))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, boxes.end() - 1);
		boxes.pop_back();
	}
}

bool PhysicsSystem::segmentCast(const LineSegment& l, CollisionInfo& outColl)
{
	bool collided = false;
	// Initialize closestT to infinity, so first
	// intersection will always update closestT
	float closestT = Maths::infinity;
	Vector3 norm;
	// Test against all boxes
	for (auto box : boxes)
	{
		float t;
		// Does the segment intersect with the box?
		if (Collisions::intersect(l, box->getWorldBox(), t, norm))
		{
			// Is this closer than previous intersection?
			if (t < closestT)
			{
				outColl.point = l.pointOnSegment(t);
				outColl.normal = norm;
				outColl.box = box;
				outColl.actor = &box->getOwner();

				// distance to point
				float dx = outColl.point.x - l.start.x;
				float dy = outColl.point.y - l.start.y;
				float dz = outColl.point.z - l.start.z;
				float dist = sqrt(dx * dx + dy * dy + dz * dz);
				outColl.distance = dist;

				collided = true;
			}
		}
	}
	return collided;
}

void PhysicsSystem::testPairwise(std::function<void(Actor*, Actor*)> f)
{
	// Naive implementation O(n^2)
	for (size_t i = 0; i < boxes.size(); i++)
	{
		// Don't need to test vs itself and any previous i values
		for (size_t j = i + 1; j < boxes.size(); j++)
		{
			BoxCollisionComponent* a = boxes[i];
			BoxCollisionComponent* b = boxes[j];
			if (Collisions::intersect(a->getWorldBox(), b->getWorldBox()))
			{
				// Call supplied function to handle intersection
				f(&a->getOwner(), &b->getOwner());
			}
		}
	}
}

void PhysicsSystem::testSweepAndPrune(std::function<void(Actor*, Actor*)> f)
{
	// Sort by min.x
	std::sort(begin(boxes), end(boxes),
		[](BoxCollisionComponent* a, BoxCollisionComponent* b) {
			return a->getWorldBox().min.x < b->getWorldBox().min.x;
		});

	for (size_t i = 0; i < boxes.size(); i++)
	{
		// Get max.x for current box
		BoxCollisionComponent* a = boxes[i];
		float max = a->getWorldBox().max.x;
		for (size_t j = i + 1; j < boxes.size(); j++)
		{
			BoxCollisionComponent* b = boxes[j];
			// If AABB[j] min is past the max bounds of AABB[i],
			// then there aren't any other possible intersections
			// against AABB[i]
			if (b->getWorldBox().min.x > max)
			{
				break;
			}
			else if (Collisions::intersect(a->getWorldBox(), b->getWorldBox()))
			{
				f(&a->getOwner(), &b->getOwner());
			}
		}
	}
}
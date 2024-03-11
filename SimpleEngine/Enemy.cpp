#include "Enemy.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "BoxCollisionComponent.h"
#include "LineSegment.h"
#include "PhysicsSystem.h"
#include "Game.h"
#include "PlaneActor.h"

Enemy::Enemy()
{
	setRotation(Quaternion(Vector3::unitZ, Maths::pi));

	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Target"));

	BoxCollisionComponent* bc = new BoxCollisionComponent(this);
	bc->setObjectBox(Assets::getMesh("Mesh_Target").getBox());

	sphere = new SphereActor();
	sphere->setScale(5.0f);
	
}

void Enemy::updateActor(float dt)
{
	// Construct segment in direction of travel
	const float segmentLength = 2000.0f;
	Vector3 start = getPosition() + getForward() * 10.0f;
	Vector3 dir = getForward();
	Vector3 end = start + dir * segmentLength;

	//std::cout << start.x << ", " << start.y << ", " << start.z << std::endl;

	//sphere->setPosition(getPosition());

	// Create line segment
	LineSegment l(start, end);

	// Test segment vs world
	PhysicsSystem::CollisionInfo info;
	// (Don't collide vs player)
	if (getGame().getPhysicsSystem().segmentCast(l, info) && info.actor != this)
	{
		//// If we collided, reflect the ball about the normal
		//dir = Vector3::reflect(dir, info.normal);
		//rotateToNewForward(dir);
		//// Did we hit a target?
		//Enemy* target = dynamic_cast<Enemy*>(info.actor);
		//if (target)
		//{
		//	//static_cast<BallActor*>(&owner)->hitTarget();
		//}
		//std::cout << info.point.x << ", "<< info.point.y << std::endl;

		Character* target = dynamic_cast<Character*>(info.actor);
		if (target)
		{
			std::cout << "player" << std::endl;
		}

		sphere->setPosition(info.point);
		//std::cout << info.point.x << ", " << info.point.y << std::endl;
	}
}

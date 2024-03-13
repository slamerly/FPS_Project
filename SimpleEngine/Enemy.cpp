#include "Enemy.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "BoxCollisionComponent.h"
#include "LineSegment.h"
#include "PhysicsSystem.h"
#include "Game.h"
#include "MoveComponent.h"

Enemy::Enemy()
{
	setRotation(Quaternion(Vector3::unitZ, Maths::pi));

	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Lemon"));

	BoxCollisionComponent* bc = new BoxCollisionComponent(this);
	bc->setObjectBox(Assets::getMesh("Mesh_Lemon").getBox());

	//sphere = new SphereActor();
	//sphere->setScale(5.0f);
	moveComponent = new MoveComponent(this);
	moveComponent->setForwardSpeed(400.0f);
}

void Enemy::updateActor(float dt)
{
	// Construct segment in direction of travel
	const float segmentLength = 200.0f;
	Vector3 start = getPosition() + getForward() * 100.0f;
	Vector3 dir = getForward();
	Vector3 end = start + dir * segmentLength;

	//sphere->setPosition(getPosition() +  getForward() * 100);

	// Create line segment
	LineSegment l(start, end);

	// Test segment vs world
	PhysicsSystem::CollisionInfo info;
	// (Don't collide vs player)
	if (getGame().getPhysicsSystem().segmentCast(l, info) && info.actor != this)
	{
		//Character* target = dynamic_cast<Character*>(info.actor);

		std::cout << info.distance << std::endl;
		PlaneActor* mur = dynamic_cast<PlaneActor*>(info.actor);
		if (mur)
		{
			std::cout << "mur" << std::endl;
			moveComponent->setForwardSpeed(0);
		}

		//sphere->setPosition(info.point);
	}
}

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

	sphereR = new SphereActor();
	sphereR->setScale(5.0f);
	sphereL = new SphereActor();
	sphereL->setScale(5.0f);

	moveComponent = new MoveComponent(this);
	moveComponent->setForwardSpeed(fowardSpeed);

	srand(time(nullptr));
}

void Enemy::updateActor(float dt)
{
	const float segmentLength = 1000.0f;
	Vector3 start = getPosition() + getForward() * 100.0f;
	Vector3 dir = getForward();
	Vector3 end = start + dir * segmentLength;

	//sphere->setPosition(getPosition() +  getForward() * 100);

	LineSegment l(start, end);

	PhysicsSystem::CollisionInfo info;
	if (getGame().getPhysicsSystem().segmentCast(l, info) && info.actor != this)
	{
		//Character* target = dynamic_cast<Character*>(info.actor);
		PlaneActor* mur = dynamic_cast<PlaneActor*>(info.actor);
		if (mur && info.distance < 200)
		{
			//std::cout << "mur" << std::endl;
			moveComponent->setForwardSpeed(0);
			if (!sensChoiced)
			{
				sens = rand() % 2;
				sensChoiced = true;
			}

			if(sens == 0)
				moveComponent->setAngularSpeed(-1.f);
			else
				moveComponent->setAngularSpeed(1.f);
		}
	}

	if (sensChoiced)
	{
		if (newDirection())
		{
			moveComponent->setAngularSpeed(0);
			moveComponent->setForwardSpeed(fowardSpeed);
			sensChoiced = false;
			Rclear = false;
			Lclear = false;
		}
	}

	//std::cout << newDirection() << std:: endl;
}

bool Enemy::newDirection()
{
	const float segmentLength = 1000.0f;
	Vector3 dir = getForward();

	Vector3 startR = getPosition() + getRight() * 100.0f;
	Vector3 endR = startR + getRight() * 200.0f  + dir * segmentLength;
	Vector3 startL = getPosition() + getRight() * -1.f * 100.0f;
	Vector3 endL = startL + getRight() * -200.0f + dir * segmentLength;

	// Create line segment
	LineSegment lR(startR, endR);
	LineSegment lL(startL, endL);

	// Test segment vs world
	PhysicsSystem::CollisionInfo infoR;
	if (getGame().getPhysicsSystem().segmentCast(lR, infoR) && infoR.actor != this)
	{
		PlaneActor* mur = dynamic_cast<PlaneActor*>(infoR.actor);
		if (mur)
		{
			//std::cout << "R : mur" << std::endl;
			Rclear = false;
		}

		sphereR->setPosition(infoR.point);
	}
	else
	{
		//std::cout << "R : nothing" << std::endl;
		Rclear = true;
	}

	PhysicsSystem::CollisionInfo infoL;
	if (getGame().getPhysicsSystem().segmentCast(lL, infoL) && infoL.actor != this)
	{
		PlaneActor* mur = dynamic_cast<PlaneActor*>(infoL.actor);
		if (mur)
		{
			//std::cout << "L : mur" << std::endl;
			Lclear = false;
		}

		sphereL->setPosition(infoL.point);
	}
	else
	{
		//std::cout << "L : nothing" << std::endl;
		Lclear = true;
	}

	return Rclear && Lclear;
}

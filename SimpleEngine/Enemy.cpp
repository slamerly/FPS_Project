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

	//sphereR = new SphereActor();
	//sphereR->setScale(5.0f);
	//sphereL = new SphereActor();
	//sphereL->setScale(5.0f);

	moveComponent = new MoveComponent(this);
	//moveComponent->setForwardSpeed(fowardSpeed);
	moveComponent->setForwardSpeed(0);

	srand(time(nullptr));

	getGame().addMovableActor(this);
}

Enemy::~Enemy()
{
	getGame().removeMovableActor(this);
}

void Enemy::updateActor(float dt)
{
	const float segmentLength = 1000.0f;
	Vector3 start = getPosition() + getForward() * 100.0f;
	Vector3 dir = getForward();
	Vector3 end = start + dir * segmentLength;

	RBorder = start + getRight() * 500.0f + dir * (segmentLength * 0.5f);
	LBorder = start + getRight() * -500.0f + dir * (segmentLength * 0.5f);

	/*startR = getPosition() + getRight() * 100.0f;
	endR = startR + getRight() * 400.0f + dir * (segmentLength * 0.75f);
	startL = getPosition() + getRight() * -1.f * 100.0f;
	endL = startL + getRight() * -400.0f + dir * (segmentLength * 0.75f);*/

	//sphere->setPosition(end);

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
		//sphere->setPosition(info.point);
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
	else
	{
		detection();
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

	LineSegment lR(startR, endR);
	LineSegment lL(startL, endL);

	PhysicsSystem::CollisionInfo infoR;
	if (getGame().getPhysicsSystem().segmentCast(lR, infoR) && infoR.actor != this)
	{
		PlaneActor* mur = dynamic_cast<PlaneActor*>(infoR.actor);
		if (mur)
		{
			Rclear = false;
		}

		//sphereR->setPosition(infoR.point);
	}
	else
	{
		Rclear = true;
	}

	PhysicsSystem::CollisionInfo infoL;
	if (getGame().getPhysicsSystem().segmentCast(lL, infoL) && infoL.actor != this)
	{
		PlaneActor* mur = dynamic_cast<PlaneActor*>(infoL.actor);
		if (mur)
		{
			Lclear = false;
		}

		//sphereL->setPosition(infoL.point);
	}
	else
	{
		Lclear = true;
	}

	return Rclear && Lclear;
}

bool Enemy::detection()
{
	distMtBMax = dist3D(getPosition(), RBorder);
	distBtBMax = dist3D(RBorder, LBorder);
	float distance = INFINITY;
	for( auto movableActor : getGame().getMovableActors())
	{
		float currentDistance = dist3D(getPosition(), movableActor->getPosition());

		//if (currentDistance <= focusDistance && currentDistance < distance && movableActor != this)
		if (currentDistance <= focusDistance && 
			currentDistance < distance && 
			movableActor != this)
		{
			distance = currentDistance;
			actorDetected = movableActor;
		}
	}

	if (actorDetected != nullptr && dist3D(getPosition(), actorDetected->getPosition()) > focusDistance)
	{
		actorDetected = nullptr;
	}

	if (actorDetected != nullptr)
	{
		Vector3 startDetect = getPosition() + getForward() * 100.0f;
		Vector3 endDetect = actorDetected->getPosition();

		LineSegment lDetect(startDetect, endDetect);

		//sphere->setPosition(endDetect);

		PhysicsSystem::CollisionInfo infoDetect;

		if (getGame().getPhysicsSystem().segmentCast(lDetect, infoDetect) && infoDetect.actor != this)
		{
			float distRBtP = dist3D(RBorder, actorDetected->getPosition());
			float distLBtP = dist3D(LBorder, actorDetected->getPosition());
			float distMtP = dist3D(getPosition(), actorDetected->getPosition());

			if (distRBtP < distBtBMax && distLBtP < distBtBMax && distMtP < distMtBMax)
			{
				Character* player = dynamic_cast<Character*>(infoDetect.actor);
				if (player)
				{
					std::cout << "Detected: " << 
						actorDetected->getPosition().x << ", " << 
						actorDetected->getPosition().y << ", " <<
						actorDetected->getPosition().z << std::endl;
				}
				//sphere->setPosition(infoDetect.point);
			}
		}
	}

	return false;
}

float Enemy::dist3D(Vector3 start, Vector3 end)
{
	float dx = end.x - start.x;
	float dy = end.y - start.y;
	float dz = end.z - start.z;

	return sqrt(dx * dx + dy * dy + dz * dz);
}

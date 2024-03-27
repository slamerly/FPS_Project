#include "BallActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "MoveComponent.h"
#include "LineSegment.h"
#include "PhysicsSystem.h"
#include "Game.h"
#include "Enemy.h"
#include "BallMoveComponent.h"
#include "BulletHole.h"
/*
BallActor::BallActor() : Actor(), lifetimeSpan(2.0f), player(nullptr), ballMove(nullptr)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
	ballMove = new MoveComponent(this);
	ballMove->setForwardSpeed(1500.0f);
}

void BallActor::updateActor(float dt)
{
	Actor::updateActor(dt);

	lifetimeSpan -= dt;
	if (lifetimeSpan < 0.0f)
	{
		setState(ActorState::Dead);
	}

	// Construct segment in direction of travel
	const float segmentLength = 30.0f;
	Vector3 start = getPosition();
	Vector3 dir = getForward();
	Vector3 end = start + dir * segmentLength;

	// Create line segment
	LineSegment l(start, end);

	// Test segment vs world
	PhysicsSystem::CollisionInfo info;
	// (Don't collide vs player)

	/*if (getGame().getPhysicsSystem().segmentCast(l, info) && info.actor == player)
	{
		hitTarget();
	}

	if (getGame().getPhysicsSystem().segmentCast(l, info) && info.actor != player)
	{
		// If we collided, reflect the ball about the normal
		dir = Vector3::reflect(dir, info.normal);
		rotateToNewForward(dir);
		// Did we hit a target?
		Enemy* target = dynamic_cast<Enemy*>(info.actor);
		if (target)
		{
			hitTarget();
		}
	}

	// Base class update moves based on forward speed
	ballMove->update(dt);
}

void BallActor::setPlayer(Actor* pPlayer)
{
	player = pPlayer;
}

void BallActor::hitTarget()
{
	std::cout << "hit" << std::endl;
}
*/
BallActor::BallActor() : Actor(), lifetimeSpan(2.0f), ballMove(nullptr)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
	//audio = new AudioComponent(this);

	setScale(0.5f);
	ballMove = new BallMoveComponent(this);
	ballMove->setForwardSpeed(1500.0f);
}

void BallActor::updateActor(float dt)
{
	Actor::updateActor(dt);

	lifetimeSpan -= dt;
	if (lifetimeSpan < 0.0f)
	{
		setState(ActorState::Dead);
	}
}

void BallActor::setPlayer(Actor* player)
{
	ballMove->setPlayer(player);
}

void BallActor::hitTarget()
{
	/*BulletHole* impact = new BulletHole();
	impact->setPosition(this->getPosition());*/
	std::cout << "hit" << std::endl;
	//audio->playEvent("event:/Ding");
}

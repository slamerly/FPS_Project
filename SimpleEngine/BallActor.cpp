#include "BallActor.h"
#include "Assets.h"
#include "MoveComponent.h"
#include "LineSegment.h"
#include "PhysicsSystem.h"
#include "Game.h"
#include "Enemy.h"
#include "BallMoveComponent.h"

BallActor::BallActor(float pDmg) : Actor(), lifetimeSpan(2.0f), ballMove(nullptr), dmg(pDmg)
{
	mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));

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

void BallActor::hitTarget(Enemy* target)
{
	target->setLife(dmg);
	std::cout << "Enemy life:" << target->getLife() << std::endl;
}

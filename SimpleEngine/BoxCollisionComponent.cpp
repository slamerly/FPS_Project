#include "BoxCollisionComponent.h"
#include "Actor.h"
#include "Game.h"

BoxCollisionComponent::BoxCollisionComponent(Actor* ownerP, int updateOrderP) :
	Component(ownerP, updateOrderP),
	objectBox(Vector3::zero, Vector3::zero),
	worldBox(Vector3::zero, Vector3::zero),
	shouldRotate(true)
{
	Game::instance().getPhysicsSystem().addBox(this);
}

BoxCollisionComponent::~BoxCollisionComponent()
{
	Game::instance().getPhysicsSystem().removeBox(this);
}

void BoxCollisionComponent::setObjectBox(const AABB& objectBoxP)
{
	objectBox = objectBoxP;
}

void BoxCollisionComponent::setShouldRotate(bool shouldRotateP)
{
	shouldRotate = shouldRotateP;
}

void BoxCollisionComponent::onUpdateWorldTransform()
{
	// Reset to object space box
	worldBox = objectBox;

	worldBox.min *= owner.getScale();
	worldBox.max *= owner.getScale();
	if (shouldRotate)
	{
		worldBox.rotate(owner.getRotation());
	}
	worldBox.min += owner.getPosition();
	worldBox.max += owner.getPosition();
}

#pragma once
#include "Actor.h"
#include "SphereActor.h"

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy();

	void updateActor(float dt) override;

private:
	SphereActor* sphere;
	SphereActor* sphereR;
	SphereActor* sphereL;
	class MoveComponent* moveComponent;

	float fowardSpeed = 400.0f;

	// Rotation
	bool newDirection();
	bool Rclear = false;
	bool Lclear = false;

	int sens = 0;
	bool sensChoiced = false;

	//Vector3 startR, startL, endR, endL;
	//PhysicsSystem::CollisionInfo info, infoR, infoL, infoDetect;

	// Detection system
	bool detection();
	Actor* actorDetected = nullptr;
	float focusDistance = 1000;
	Vector3 RBorder, LBorder;
	float distMtBMax, distBtBMax;

	float dist3D(Vector3 start, Vector3 end);
};


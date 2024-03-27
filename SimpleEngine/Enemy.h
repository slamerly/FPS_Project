#pragma once
#include "Actor.h"
#include "SphereActor.h"
#include "PhysicsSystem.h"

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy();

	void setLife(int dm);

	void updateActor(float dt) override;

private:
	SphereActor* sphere;
	SphereActor* sphereR;
	SphereActor* sphereL;
	class MoveComponent* moveComponent;

	float fowardSpeed = 300.0f;

	// Rotation
	bool newDirection();
	bool Rclear = false;
	bool Lclear = false;

	const float segmentLength = 1000.0f;
	int sens = 0;
	bool sensChoiced = false;

	//Vector3 startR, startL, endR, endL;
	//PhysicsSystem::CollisionInfo info, infoR, infoL, infoDetect;

	// Detection system
	bool detection();
	Actor* actorDetected = nullptr;
	const float focusDistance = 1000;
	Vector3 RBorder, LBorder;
	float distMtBMax, distBtBMax;
	PhysicsSystem::CollisionInfo infoDetect;

	void dodge(float distBA);

	// Fight
	void fight(float distR, float distL, float distM);
	void shoot(PhysicsSystem::CollisionInfo targetInfo);
	const float cooldownShoot = 1.f;
	float currentCooldownShoot = 0.0f;

	// Life
	int life = 30;


	float dist3D(Vector3 start, Vector3 end);
};


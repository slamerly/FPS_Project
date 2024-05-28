#pragma once
#include "Actor.h"
#include "SphereActor.h"
#include "PhysicsSystem.h"
#include "MeshComponent.h"

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy();

	float getLife() { return life; }
	void setLife(int dm);

	void updateActor(float dt) override;

private:
	SphereActor* sphere;
	SphereActor* sphereR;
	SphereActor* sphereL;
	class MoveComponent* moveComponent;
	MeshComponent* mc;

	// voir aussi animation
	float fowardSpeed = 300.0f;

	// Rotation
	bool newDirection();
	bool Rclear = false;
	bool Lclear = false;

	const float segmentLength = 1000.0f;
	int sens = 0;
	bool sensChoiced = false;

	// Detection system
	bool detection();
	Actor* actorDetected = nullptr;
	const float focusDistance = 1000;
	Vector3 RBorder, LBorder;
	float distMtBMax, distBtBMax;
	PhysicsSystem::CollisionInfo infoDetect;

	void animation(float dt);


	// Dodge
	bool isSaveDir = false;
	bool isdodging = false;
	Vector3 saveDir;
	void dodge(float distBA);

	// Fight
	bool fighting = false;
	void fight(float distR, float distL, float distM);
	void shoot(PhysicsSystem::CollisionInfo targetInfo);
	const float cooldownShoot = 1.f;
	float currentCooldownShoot = 0.0f;

	// Life
	float life = 30;
	bool takingDamage = false;
	const float timeSlow = 0.25f;
	float currentTimeSlow = .0f;
	float saveSpeedTurn = 0;
	float saveSpeed = 0;
	bool isDead = false;

	// Animation
	bool topHeight = false;
	bool topBig = false;
	bool topFinal = false;

	// Debug
	//Vector3 startR, startL, endR, endL;
	//PhysicsSystem::CollisionInfo infoR, infoL;
	//bool segCastR = false;
	//bool segCastL = false;


	float dist3D(Vector3 start, Vector3 end);
};


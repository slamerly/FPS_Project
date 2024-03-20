#pragma once
#include "Actor.h"

class Character : public Actor
{
public:
	Character();
	~Character();

	void actorInput(const struct InputState& inputState) override;
	void updateActor(float dt) override;

	void shoot();
	void reload();

	void fixCollisions();

private:
	class MoveComponent* moveComponent;
	class MeshComponent* mc;
	class Camera* cameraComponent;
	class Actor* FPSModelRifle;

	float sensitiveRota = Maths::twoPi;
	class BoxCollisionComponent* boxComponent;

	int magazineMax = 15;
	int currentMagazine = 0;

	//Reload
	bool isReloading = false;
	bool decending = true;
	float finalAngle = 0.35f;
	float currentAngle = 0.0f;
	float timeReload = 2.5f;
	float currentTimeReload = 0.0f;

	bool isShooting = false;
	float cooldownShoot = 0.15f;
	float currentCooldownShoot = 0.f;
};

const Vector3 MODEL_OFFSET = Vector3(20.0f, 30.0f, 10.0f);
#pragma once
#include "Actor.h"
#include "SphereActor.h"

class Enemy : public Actor
{
public:
	Enemy();

	void updateActor(float dt) override;

private:
	SphereActor* sphere;
	SphereActor* sphereR;
	SphereActor* sphereL;
	class MoveComponent* moveComponent;

	float fowardSpeed = 400.0f;

	bool newDirection();
	bool Rclear = false;
	bool Lclear = false;

	int sens = 0;
	bool sensChoiced = false;
};


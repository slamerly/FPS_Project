#pragma once
#include "Actor.h"
#include "SphereActor.h"

class Enemy : public Actor
{
public:
	Enemy();

	void updateActor(float dt) override;

private:
	//SphereActor* sphere;
	class MoveComponent* moveComponent;
};


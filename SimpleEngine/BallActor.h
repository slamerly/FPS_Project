#pragma once
#include "Actor.h"
#include "Enemy.h"
#include "MeshComponent.h"

class BallActor : public Actor
{
public:
	BallActor(float pDmg);

	void updateActor(float dt) override;
	void setPlayer(Actor* pPlayer);
	void hitTarget(Enemy* target);
	MeshComponent* getMeshComponent() { return mc; }

private:
	class Actor* player;
	class BallMoveComponent* ballMove;
	float lifetimeSpan;
	float dmg;
	MeshComponent* mc;
};


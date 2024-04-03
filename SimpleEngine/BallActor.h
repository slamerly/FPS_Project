#pragma once
#include "Actor.h"
#include "Enemy.h"

class BallActor : public Actor
{
public:
	BallActor(float pDmg);

	void updateActor(float dt) override;
	void setPlayer(Actor* pPlayer);
	void hitTarget(Enemy* target);

private:
	class Actor* player;
	class BallMoveComponent* ballMove;
	float lifetimeSpan;
	float dmg;
};


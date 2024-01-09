#pragma once
#include "Actor.h"

class BallActor : public Actor
{
public:
	BallActor();

	void updateActor(float dt) override;
	void setPlayer(Actor* pPlayer);
	void hitTarget();

private:
	class MoveComponent* ballMove;
	class Actor* player;
	float lifetimeSpan;
};


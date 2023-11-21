#pragma once
#include "Actor.h"

class Character : public Actor
{
public:
	Character();

	void actorInput(const struct InputState& inputState) override;

private:
	class MoveComponent* moveComponent;
	class MeshComponent* mc;

	float sensitiveRota = Maths::twoPi;
};

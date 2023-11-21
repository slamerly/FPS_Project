#pragma once
#include "Actor.h"

class Character : public Actor
{
public:
	Character();

	void actorInput(const struct InputState& inputState) override;
	void updateActor(float dt) override;

private:
	class MoveComponent* moveComponent;
	class MeshComponent* mc;
	class Camera* cameraComponent;
	class Actor* FPSModelRifle;

	float sensitiveRota = Maths::twoPi;
};

const Vector3 MODEL_OFFSET = Vector3(10.0f, 10.0f, 10.0f);
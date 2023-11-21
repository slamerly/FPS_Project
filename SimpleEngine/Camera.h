#pragma once
#include "Actor.h"
#include "Subject.h"

class Camera : public Actor, public Subject
{
public:
	Camera();

	void updateActor(float deltaTime) override;

	// Spring Arm
	float getPitchSpeed() const { return pitchSpeed; } // Orbiting & FPS

	void setCharacter(class Character* characterP) { character = characterP; }
	void setPitchSpeed(float newPitchSpeed); // Orbiting & FPS

	// FPS camera
	float getPitch() const { return pitch; }
	float getMaxPitch() const { return maxPitch; }
	bool getFPScam() const { return fpsCam; }

	void setMaxPitch(float pitch);
	void setFPSCam(bool fpsCamP);

private:
	class MoveComponent* moveComponent;

	// Offset
	Vector3 offset;
	// Up vector of camera
	Vector3 up;

	// Spring Arm
	class Character* character;
	float pitchSpeed; // Orbiting & FPS

	// FPS camera
	bool fpsCam = true;
	float maxPitch;
	float pitch;
};

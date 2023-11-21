#pragma once
#include "Actor.h"
#include "Subject.h"

class Camera : public Actor, public Subject
{
public:
	Camera();

	void updateActor(float deltaTime) override;
	void actorInput(const struct InputState& inputState) override;

	// Spring Arm
	float getPitchSpeed() const { return pitchSpeed; } // Orbiting & FPS

	void setCharacter(class Character* characterP) { character = characterP; }
	void setPitchSpeed(float newPitchSpeed); // Orbiting & FPS

	// Orbiting camera
	float getYawSpeed() const { return yawSpeed; }
	//bool useControlRotation() const { return controlRotation; }

	void setYawSpeed(float newYawSpeed);
	void setControlRotation(bool useControlRotation);

	// Following camera
	void snap();

	void setHorizontalDist(float distance);
	void setVerticalDist(float distance);
	void setTargetDist(float distance);
	void setSpringConst(float springConstP);
	void setFollowCam(bool followCamP);

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

	// Orbiting camera
	bool controlRotation = true;
	float mouseSensitivity = 500.0f;
	float yawSpeed;

	// Folowing camera
	Vector3 computeCamPos() const;

	bool followCam = false;
	Vector3 actualPosition;
	Vector3 velocity;
	float horizontalDist;
	float verticalDist;
	float targetDist;
	float springConst;

	// FPS camera
	bool fpsCam = false;
	float maxPitch;
	float pitch;

	//float sensitiveRota = Maths::twoPi;
};

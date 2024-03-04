#pragma once
#include "Component.h"
#include "Matrix4.h"

class Camera : public Component
{
public:
	Camera(class Actor* owner);

	void update(float deltaTime) override;

	// Spring Arm
	float getPitchSpeed() const { return pitchSpeed; } // Orbiting & FPS

	void setPitchSpeed(float newPitchSpeed); // Orbiting & FPS

	// FPS camera
	float getPitch() const { return pitch; }
	float getMaxPitch() const { return maxPitch; }
	bool getFPScam() const { return fpsCam; }

	void setMaxPitch(float pitch);
	void setFPSCam(bool fpsCamP);

	// Movement Shake
	void setShakeSpeed(float isActive);

protected:
	void setViewMatrix(const Matrix4& view);

private:
	// Offset
	Vector3 offset;
	// Up vector of camera
	Vector3 up;

	// Spring Arm
	float pitchSpeed; // Orbiting & FPS

	// FPS camera
	bool fpsCam = true;
	float maxPitch;
	float pitch;

	// Movement Shake
	float cpt = 0;
	float shakeSpeed = 0.18f;
};

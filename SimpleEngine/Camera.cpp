#include "Camera.h"
#include "MoveComponent.h"
#include "Game.h"

Camera::Camera() : Actor(), moveComponent(nullptr), character(nullptr)
{
	up = Vector3::unitZ;
	setPosition(Vector3(0.0f, 0.0f, -100.0f));
	pitchSpeed = 0.0f;

	// --- FPS camera ---
	maxPitch = Maths::pi / 3.0f;
	pitch = 0.0f;
}

void Camera::updateActor(float deltaTime)
{
	Actor::updateActor(deltaTime);

	// --- Default values ---
	Vector3 cameraPos = getPosition();
	Vector3 target = character->getPosition();

	// --- FPS camera ---
	if (fpsCam)
	{
		cameraPos = character->getPosition() + Vector3(0.0f, 0.0f, 30.0f);
		pitch += pitchSpeed * deltaTime;
		pitch = Maths::clamp(pitch, -maxPitch, maxPitch);
		Quaternion q{ character->getRight(), pitch };
		Vector3 viewForward = Vector3::transform(character->getForward(), q);

		target = cameraPos + viewForward * 100.0f;
		up = Vector3::transform(Vector3::unitZ, q);
	}
	// --- End FPS camera ---

	// View Matrix
	Matrix4 view = Matrix4::createLookAt(cameraPos, target, up);
	getGame().getRenderer().setViewMatrix(view);
}

void Camera::setPitchSpeed(float newPitchSpeed)
{
	pitchSpeed = newPitchSpeed;
}

void Camera::setMaxPitch(float pitch)
{
	maxPitch = pitch;
}

void Camera::setFPSCam(bool fpsCamP)
{
	fpsCam = fpsCamP;
	// Achivement
	if (fpsCam)
		notify(Event::IN_HEAD);
}
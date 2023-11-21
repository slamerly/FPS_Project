#include "Camera.h"
#include "MoveComponent.h"
#include "Game.h"

Camera::Camera() : Actor(), moveComponent(nullptr), character(nullptr)
{
	up = Vector3::unitZ;
	setPosition(Vector3(0.0f, 0.0f, -100.0f));
	pitchSpeed = 0.0f;

	// --- Obiting camera ---
	offset = Vector3(-300.0f, 0.0f, 0.0f);
	yawSpeed = 0.0f;

	// --- Following camera ---
	horizontalDist = 350.0f;
	verticalDist = 150.0f;
	targetDist = 100.0f;
	springConst = 64.0f;

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


	// --- Obiting camera ---
	if (controlRotation)
	{
		Quaternion yaw{ Vector3::unitZ, yawSpeed * deltaTime };
		offset = Vector3::transform(offset, yaw);
		up = Vector3::transform(up, yaw);

		// Forward owner.position - (owner.position + offset) = - offset
		Vector3 forward = -1.0f * offset;
		forward.normalize();
		Vector3 right = Vector3::cross(up, forward);
		right.normalize();

		Quaternion pitch{ right, pitchSpeed * deltaTime };
		offset = Vector3::transform(offset, pitch);
		up = Vector3::transform(up, pitch);

		target = character->getPosition();
		cameraPos = target + offset;
	}
	// --- End Obiting camera ---

	// --- Follow Camera ---
	if (followCam)
	{
		float dampening = 2.0f * Maths::sqrt(springConst);
		Vector3 idealPosition = computeCamPos();
		Vector3 diff = actualPosition - idealPosition;
		Vector3 accel = -springConst * diff - dampening * velocity;
		velocity += accel * deltaTime;
		actualPosition += velocity * deltaTime;

		cameraPos = actualPosition;
		target = character->getPosition() + character->getForward() * targetDist;
	}
	// --- End Follow Camera ---

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

// Move only the camera
void Camera::actorInput(const struct InputState& inputState)
{
	if (controlRotation)
	{
		Vector2 mousePosition = inputState.mouse.getPosition();
		float x = mousePosition.x;
		float y = mousePosition.y;

		if (controlRotation)
		{
			const float maxMouseSpeed = 500.0f;
			const float maxOrbitSpeed = Maths::pi * 8;

			float newYawSpeed = 0.0f;
			if (!Maths::nearZero(x))
			{
				newYawSpeed = x / maxMouseSpeed;
				newYawSpeed *= maxOrbitSpeed;
			}
			yawSpeed = newYawSpeed;

			float newPitchSpeed = 0.0f;
			if (!Maths::nearZero(y))
			{
				newPitchSpeed = y / maxMouseSpeed;
				newPitchSpeed *= maxOrbitSpeed;
			}
			pitchSpeed = newPitchSpeed;
		}
	}
}

void Camera::setPitchSpeed(float newPitchSpeed)
{
	pitchSpeed = newPitchSpeed;
}

void Camera::setYawSpeed(float newYawSpeed)
{
	yawSpeed = newYawSpeed;
}

void Camera::setControlRotation(bool useControlRotation)
{
	controlRotation = useControlRotation;
	// Achivement
	if(controlRotation)
		notify(Event::AROUND_THE_WORLD);
}

void Camera::snap()
{
	actualPosition = computeCamPos();
	velocity = Vector3::zero;
	Vector3 target = character->getPosition() + character->getPosition() * targetDist;

	Matrix4 view = Matrix4::createLookAt(actualPosition, target, Vector3::unitZ);
	getGame().getRenderer().setViewMatrix(view);
}

void Camera::setHorizontalDist(float distance)
{
	horizontalDist = distance;
}

void Camera::setVerticalDist(float distance)
{
	verticalDist = distance;
}

void Camera::setTargetDist(float distance)
{
	targetDist = distance;
}

void Camera::setSpringConst(float springConstP)
{
	springConst = springConstP;
}

void Camera::setFollowCam(bool followCamP)
{
	followCam = followCamP;
	// Achivement
	if(followCam)
		notify(Event::FOLLOW_CHARA);

	snap();
	up = Vector3::unitZ;
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

Vector3 Camera::computeCamPos() const
{
	Vector3 camPos = character->getPosition();
	camPos -= character->getForward() * horizontalDist;
	camPos += Vector3::unitZ * verticalDist;
	return camPos;
}

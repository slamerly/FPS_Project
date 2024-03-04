#include "Camera.h"
#include "Game.h"

Camera::Camera(Actor* owner) : Component(owner)
{
	up = Vector3::unitZ;
	//setPosition(Vector3(0.0f, 0.0f, -100.0f));
	pitchSpeed = 0.0f;
	
	// --- FPS camera ---
	maxPitch = Maths::pi / 3.0f;
	pitch = 0.0f;
}

void Camera::update(float deltaTime)
{
	Component::update(deltaTime);

	cpt+= shakeSpeed;

	// --- Default values ---
	Vector3 cameraPos = owner.getPosition();
	Vector3 target = owner.getPosition();

	// --- FPS camera ---
	if (fpsCam)
	{
		cameraPos = owner.getPosition() + Vector3(0.0f, 0.0f, 30.0f);
		pitch += pitchSpeed * deltaTime;
		pitch = Maths::clamp(pitch, -maxPitch, maxPitch);
		Quaternion q{ owner.getRight(), pitch };
		Vector3 viewForward = Vector3::transform(owner.getForward(), q);

		// Movement shake
		cameraPos += Vector3(owner.getRight().x * cos(cpt) * 0.1f, owner.getRight().y * cos(cpt) * 0.1f, sin(cpt) * 0.33f);

		//std::cout << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << std::endl;

		target = cameraPos + viewForward * 100.0f;
		up = Vector3::transform(Vector3::unitZ, q);
	}
	// --- End FPS camera ---



	// View Matrix
	Matrix4 view = Matrix4::createLookAt(cameraPos, target, up);
	setViewMatrix(view);
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
}

void Camera::setShakeSpeed(float isActive)
{
	shakeSpeed = isActive;
}

void Camera::setViewMatrix(const Matrix4& view)
{
	Game& game = owner.getGame();
	game.getRenderer().setViewMatrix(view);
}

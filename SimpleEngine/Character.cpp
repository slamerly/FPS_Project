#include "Character.h"
#include "MoveComponent.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "Game.h"
#include "Cube.h"

Character::Character() : Actor(), moveComponent(nullptr)
{
	moveComponent = new MoveComponent(this);
	mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Cube"));
}

void Character::actorInput(const struct InputState& inputState)
{
	//std::cout << getPosition().x << ", " << getPosition().y << std::endl;
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	float strafeSpeed = 0.0f;

	// wasd movement
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_W))
	{
		forwardSpeed += 300.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_S))
	{
		forwardSpeed -= 300.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_A))
	{
		if (getGame().getCamera()->getFPScam())
			strafeSpeed -= 250.0f;
		else
			angularSpeed -= sensitiveRota;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_D))
	{
		if(getGame().getCamera()->getFPScam())
			strafeSpeed += 250.0f;
		else
			angularSpeed += sensitiveRota;
	}

	moveComponent->setForwardSpeed(forwardSpeed);
	moveComponent->setAngularSpeed(angularSpeed);
	moveComponent->setStrafeSpeed(strafeSpeed);

	if (!Maths::nearZero(forwardSpeed))
		getGame().getCamera()->setHorizontalDist(400.0f);
	else
		getGame().getCamera()->setHorizontalDist(300.0f);

	// FPS Camera
	if (getGame().getCamera()->getFPScam())
	{
		Vector2 mousePosition = inputState.mouse.getPosition();
		float x = mousePosition.x;
		float y = mousePosition.y;

		const float maxMouseSpeed = 500.0f;
		const float maxAngularSpeed = Maths::pi * 8;

		float angularSpeed = 0.0f;
		if (x != 0)
		{
			angularSpeed = x / maxMouseSpeed;
			angularSpeed *= maxAngularSpeed;
		}
		moveComponent->setAngularSpeed(angularSpeed);

		const float maxPitchSpeed = Maths::pi * 8;
		float pitchSpeed = 0.0f;
		if (y != 0)
		{
			pitchSpeed = y / maxMouseSpeed;
			pitchSpeed *= maxPitchSpeed;
		}
		getGame().getCamera()->setPitchSpeed(pitchSpeed);
	}
}

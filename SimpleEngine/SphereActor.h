#pragma once
#include "Actor.h"
#include "MeshComponent.h"

class SphereActor : public Actor
{
public:
	SphereActor();

	MeshComponent* getMeshComponent() { return mc; }

private:
	MeshComponent* mc;
};


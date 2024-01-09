#pragma once
#include "Actor.h"
class PlaneActor : public Actor
{
public:
	PlaneActor();
	~PlaneActor();
	class BoxCollisionComponent* getBox() { return box; }

private:
	class BoxCollisionComponent* box;
};


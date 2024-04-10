#pragma once
#include "Actor.h"
#include "Mesh.h"
class PlaneActor : public Actor
{
public:
	PlaneActor();
	~PlaneActor();
	class BoxCollisionComponent* getBox() { return box; }

	void changeMesh(Mesh* newMesh);

private:
	class BoxCollisionComponent* box;
	MeshComponent* mc;
	Mesh* mesh;
};


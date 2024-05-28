#include "SphereActor.h"
#include "Assets.h"

SphereActor::SphereActor() : Actor()
{
	mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
}

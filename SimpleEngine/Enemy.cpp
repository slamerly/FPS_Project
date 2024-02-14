#include "Enemy.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "BoxCollisionComponent.h"

Enemy::Enemy()
{
	setRotation(Quaternion(Vector3::unitZ, Maths::pi));

	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Target"));

	BoxCollisionComponent* bc = new BoxCollisionComponent(this);
	bc->setObjectBox(Assets::getMesh("Mesh_Target").getBox());
}

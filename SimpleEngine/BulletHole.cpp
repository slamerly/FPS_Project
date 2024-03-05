#include "BulletHole.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "MeshComponent.h"

BulletHole::BulletHole() : Actor(), lifeTime(2.0f)
{
	MeshComponent* mc = new MeshComponent(this); 
	mc->setMesh(Assets::getMesh("Mesh_BulletHole"));
	std::cout << "hit" << std::endl;
	//setScale(100.0f);
}

void BulletHole::updateActor(float dt)
{
	Actor::updateActor(dt);

	lifeTime -= dt;
	if (lifeTime < 0.0f)
	{
		//setState(ActorState::Dead);
	}
}

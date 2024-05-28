#include "Enemy.h"
#include "Assets.h"
#include "BoxCollisionComponent.h"
#include "LineSegment.h"
#include "Game.h"
#include "MoveComponent.h"
#include "BallActor.h"

Enemy::Enemy()
{
	setRotation(Quaternion(Vector3::unitZ, Maths::pi));

	mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Lemon"));

	BoxCollisionComponent* bc = new BoxCollisionComponent(this);
	bc->setObjectBox(Assets::getMesh("Mesh_Lemon").getBox());

	//sphere = new SphereActor();
	//sphere->setScale(5.0f);
	/*
	sphereR = new SphereActor();
	sphereR->setScale(5.0f);
	sphereR->getMeshComponent()->setTextureIndex(3);
	sphereL = new SphereActor();
	sphereL->setScale(5.0f);
	sphereL->getMeshComponent()->setTextureIndex(3);
	*/

	moveComponent = new MoveComponent(this);
	moveComponent->setForwardSpeed(fowardSpeed);
	//moveComponent->setForwardSpeed(0);

	srand(time(nullptr));

	getGame().addMovableActor(this);
}

Enemy::~Enemy()
{
	//sphere->setState(Actor::ActorState::Dead);
	//sphereR->setState(Actor::ActorState::Dead);
	//sphereL->setState(Actor::ActorState::Dead);
	getGame().removeMovableActor(this);
}

void Enemy::setLife(int dm)
{
	if (!isDead)
	{
		life -= dm;

		takingDamage = true;
		fowardSpeed /= 2;
		moveComponent->setForwardSpeed(fowardSpeed);

		saveSpeedTurn = moveComponent->getAngularSpeed();
		if (moveComponent->getAngularSpeed() == -1 || moveComponent->getAngularSpeed() == 1)
		{
			moveComponent->setAngularSpeed(0.5f);
		}

		mc->setTextureIndex(1);

		currentTimeSlow = timeSlow;
	}
	
	if (life <= 0)
	{
		isDead = true;
		//setState(ActorState::Dead);
	}
}

void Enemy::updateActor(float dt)
{
	currentCooldownShoot -= dt;
	currentTimeSlow -= dt;
	Vector3 start = getPosition() + getForward() * 100.0f;
	Vector3 dir = getForward();
	Vector3 end = start + dir * segmentLength;

	RBorder = start + getRight() * 500.0f + dir * (segmentLength * 0.5f);
	LBorder = start + getRight() * -500.0f + dir * (segmentLength * 0.5f);

	//sphere->setPosition(end);

	LineSegment l(start, end);

	PhysicsSystem::CollisionInfo info;
	if (getGame().getPhysicsSystem().segmentCast(l, info) && info.actor != this)
	{
		//Character* target = dynamic_cast<Character*>(info.actor);
		PlaneActor* mur = dynamic_cast<PlaneActor*>(info.actor);
		if (mur && info.distance < 400)
		{
			//std::cout << "mur" << std::endl;
			moveComponent->setForwardSpeed(0);
			if (!sensChoiced)
			{
				sens = rand() % 2;
				sensChoiced = true;
			}

			if(sens == 0)
				moveComponent->setAngularSpeed(-1.f);
			else
				moveComponent->setAngularSpeed(1.f);
		}
		//sphere->setPosition(info.point);
	}

	// --- Debug ---
	/*
	startR = getPosition() + getRight() * 100.0f;
	endR = startR + getRight() * 390.0f + getForward() * segmentLength;
	startL = getPosition() + getRight() * -1.f * 100.0f;
	endL = startL + getRight() * -390.0f + getForward() * segmentLength;

	LineSegment lR(startR, endR);
	LineSegment lL(startL, endL);

	segCastR = getGame().getPhysicsSystem().segmentCast(lR, infoR);
	segCastL = getGame().getPhysicsSystem().segmentCast(lL, infoL);
	
	if (segCastR && infoR.actor != this)
	{
		sphereR->setPosition(infoR.point);
		sphereR->getMeshComponent()->setTextureIndex(3);
	}
	else
	{
		sphereR->setPosition(endR);
		sphereR->getMeshComponent()->setTextureIndex(4);
	}

	if (segCastL && infoL.actor != this)
	{
		sphereL->setPosition(infoL.point);
		sphereL->getMeshComponent()->setTextureIndex(3);
	}
	else
	{
		sphereL->setPosition(endL);
		sphereL->getMeshComponent()->setTextureIndex(4);
	}
	*/
	// --- End Debug ---

	if (sensChoiced && !isdodging)
	{
		if (newDirection())
		{
			moveComponent->setAngularSpeed(0);
			moveComponent->setForwardSpeed(fowardSpeed);
			sensChoiced = false;
			Rclear = false;
			Lclear = false;
		}
	}
	else
	{
		if(!isDead)
			detection();
		//sphereL->setPosition(Vector3(0, 0, -1500));
		//sphereR->setPosition(Vector3(0, 0, -1500));
	}
	//std::cout << newDirection() << std:: endl;
	animation(dt);
}

bool Enemy::newDirection()
{
	//const float segmentLength = 1000.0f;
	//Vector3 dirD = getForward();

	Vector3 startR = getPosition() + getRight() * 100.0f;
	Vector3 endR = startR + getRight() * 390.0f  + getForward() * segmentLength;
	Vector3 startL = getPosition() + getRight() * -1.f * 100.0f;
	Vector3 endL = startL + getRight() * -390.0f + getForward() * segmentLength;

	LineSegment lR(startR, endR);
	LineSegment lL(startL, endL);

	PhysicsSystem::CollisionInfo infoR;
	if (getGame().getPhysicsSystem().segmentCast(lR, infoR) && infoR.actor != this)
	{
		PlaneActor* mur = dynamic_cast<PlaneActor*>(infoR.actor);
		if (mur)
		{
			Rclear = false;
		}

		//sphereR->setPosition(infoR.point);
		//sphereR->getMeshComponent()->setTextureIndex(3);
	}
	else
	{
		//sphereR->setPosition(endR);
		//sphereR->getMeshComponent()->setTextureIndex(4);
		Rclear = true;
	}

	PhysicsSystem::CollisionInfo infoL;
	if (getGame().getPhysicsSystem().segmentCast(lL, infoL) && infoL.actor != this)
	{
		PlaneActor* mur = dynamic_cast<PlaneActor*>(infoL.actor);
		if (mur)
		{
			Lclear = false;
		}

		//sphereL->setPosition(infoL.point);
		//sphereL->getMeshComponent()->setTextureIndex(3);
	}
	else
	{
		//sphereL->setPosition(endL);
		//sphereL->getMeshComponent()->setTextureIndex(4);
		Lclear = true;
	}

	return Rclear && Lclear;
}

bool Enemy::detection()
{
	distMtBMax = dist3D(getPosition(), RBorder);
	distBtBMax = dist3D(RBorder, LBorder);
	float distance = INFINITY;
	for( auto movableActor : getGame().getMovableActors())
	{
		float currentDistance = dist3D(getPosition(), movableActor->getPosition());

		//if (currentDistance <= focusDistance && currentDistance < distance && movableActor != this)
		if (currentDistance <= focusDistance && 
			currentDistance < distance && 
			movableActor != this)
		{
			distance = currentDistance;
			actorDetected = movableActor;
		}
	}

	if (actorDetected != nullptr && dist3D(getPosition(), actorDetected->getPosition()) > focusDistance)
	{
		actorDetected = nullptr;
	}

	if (actorDetected != nullptr)
	{
		Vector3 startDetect = getPosition() + getForward() * 100.0f;
		Vector3 endDetect = actorDetected->getPosition();

		LineSegment lDetect(startDetect, endDetect);

		//sphere->setPosition(endDetect);

		if (getGame().getPhysicsSystem().segmentCast(lDetect, infoDetect) && infoDetect.actor != this)
		{
			float distRBtP = dist3D(RBorder, actorDetected->getPosition());
			float distLBtP = dist3D(LBorder, actorDetected->getPosition());
			float distMtP = dist3D(getPosition(), actorDetected->getPosition());

			if (distRBtP < distBtBMax && distLBtP < distBtBMax && distMtP < distMtBMax)
			{
				
				// Player
				Character* player = dynamic_cast<Character*>(infoDetect.actor);
				if (player)
				{
					if (takingDamage)
					{
						mc->setTextureIndex(1);
					}
					else
					{
						mc->setTextureIndex(2);
					}
					
					fighting = true;
					fight(distRBtP, distLBtP, distMtP);
				}
				
			}
			else
			{
				fighting = false;

				if (takingDamage)
				{
					mc->setTextureIndex(1);
				}
				else
				{
					mc->setTextureIndex(0);
				}

				moveComponent->setAngularSpeed(0);
				moveComponent->setForwardSpeed(fowardSpeed);
			}

			// Enemy
			Enemy* enemy = dynamic_cast<Enemy*>(infoDetect.actor);
			if (enemy)
			{
				if ((infoDetect.distance < 500 && !fighting) || infoDetect.distance < 200)
					isdodging = true;
			}
		}
	}
	// Dodging
	if (isdodging)
	{
		if (!isSaveDir)
		{
			saveDir = getForward();
			isSaveDir = true;
		}
		dodge(infoDetect.distance);
	}

	return false;
}

void Enemy::animation(float dt)
{
	// --- Slow move ---
	if (currentTimeSlow <= 0 && takingDamage)
	{
		if (saveSpeedTurn != 0)
		{
			moveComponent->setAngularSpeed(saveSpeedTurn);
		}
		else
		{
			fowardSpeed = 300.0f;
			moveComponent->setForwardSpeed(fowardSpeed);
		}
		mc->setTextureIndex(0);
		takingDamage = false;
	}

	// --- Death ---
	if (isDead)
	{
		mc->setTextureIndex(1);
		moveComponent->setForwardSpeed(0);
		moveComponent->setAngularSpeed(0);

		if (getScaleV3().z < 1.5f && !topHeight && !topFinal)
		{
			setScale(Vector3(getScaleV3().x, getScaleV3().y, getScaleV3().z + dt));
			if (getScaleV3().z > 1.12f)
			{
				topBig = true;
			}
		}
		else
		{
			topHeight = true;
		}

		if (getScaleV3().x < 2.f && topBig && !topFinal)
		{
			setScale(Vector3(getScaleV3().x + dt, getScaleV3().y + dt, getScaleV3().z));			
		}

		if (topHeight && getScaleV3().z > 0.75f && !topFinal)
		{
			setScale(Vector3(getScaleV3().x, getScaleV3().y, getScaleV3().z - dt));
		}

		if (getScaleV3().z <= 0.75f)
		{
			topFinal = true;
		}

		if (topFinal)
		{
			if (getScaleV3().x > 0 || getScaleV3().y > 0 || getScaleV3().z > 0)
			{
				setScale(Vector3(getScaleV3().x - (dt * 2.66f), getScaleV3().y - (dt * 2.66f), getScaleV3().z - dt));
			}
			else
			{
				setState(ActorState::Dead);
			}
		}
	}
}

void Enemy::dodge(float distBA)
{
	if ((round(getForward().x * 100) >= round(-saveDir.x * 100 - 5)) && (round(getForward().x * 100) <= round(-saveDir.x * 100 + 5))
		&& (round(getForward().y * 100) >= round(-saveDir.y * 100 - 5)) && (round(getForward().y * 100) <= round(-saveDir.y * 100 + 5)))
	{
		moveComponent->setForwardSpeed(fowardSpeed);
		moveComponent->setAngularSpeed(0.f);
		isdodging = false;
		isSaveDir = false;
	}
	else
	{
		moveComponent->setForwardSpeed(0);
		moveComponent->setAngularSpeed(1.f);
	}
}

void Enemy::fight(float distR, float distL, float distM)
{
	if (distM > distMtBMax * 0.75f)
	{
		moveComponent->setForwardSpeed(fowardSpeed);
	}
	/*else if (distM < distMMax * 0.5f)
	{
		moveComponent->setForwardSpeed(-fowardSpeed/2);
	}*/
	else
	{
		moveComponent->setForwardSpeed(0);
	}


	if (distL > distR - 10 && distL < distR + 10)
	{
		moveComponent->setAngularSpeed(0);
		if (currentCooldownShoot <= 0)
		{
			shoot(infoDetect);
		}
	}
	else if (distL > distR)
	{
		moveComponent->setAngularSpeed(1);
	}
	else if (distL < distR)
	{
		moveComponent->setAngularSpeed(-1);
	}
}

void Enemy::shoot(PhysicsSystem::CollisionInfo targetInfo)
{
	Vector3 start = getPosition() + getForward() * 100.0f + Vector3(0, 0, 35);
	Vector3 end = targetInfo.point;
	// Get direction vector
	Vector3 dir = end - start;
	dir.normalize();
	// Spawn a ball
	BallActor* ball = new BallActor(0);
	ball->getMeshComponent()->setTextureIndex(2);
	ball->setPlayer(this);
	ball->setPosition(start + dir * 20.0f);
	// Rotate the ball to face new direction
	ball->rotateToNewForward(dir);

	currentCooldownShoot = cooldownShoot;
}

float Enemy::dist3D(Vector3 start, Vector3 end)
{
	float dx = end.x - start.x;
	float dy = end.y - start.y;
	float dz = end.z - start.z;

	return sqrt(dx * dx + dy * dy + dz * dz);
}

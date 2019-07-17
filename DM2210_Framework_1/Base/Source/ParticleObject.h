#pragma once
#include "GameObject.h"

class ParticleObject : public GameObject
{
public:

	float f_lifespan; // timer before the particle expires.

	float rotation; // rotation of particle
	float rotationspeed; // rotational speed of the particle

	ParticleObject();
	ParticleObject(GameObject::GAMEOBJECT_TYPE);
	~ParticleObject();
};
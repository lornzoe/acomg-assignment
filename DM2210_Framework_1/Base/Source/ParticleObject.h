#pragma once
#include "GameObject.h"

class ParticleObject : public GameObject
{
public:

	float f_lifespan; // timer before the particle expires.
	float f_timeElapsed; // a usable float variable.
	float rotation; // rotation of particle
	float rotationspeed; // rotational speed of the particle

	ParticleObject(GEOMETRY_TYPE);
	~ParticleObject();
};
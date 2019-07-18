#include "ParticleObject.h"

ParticleObject::ParticleObject(GameObject::GAMEOBJECT_TYPE typeValue = GameObject::GO_NIL) // defaults to a nil
	: GameObject(typeValue),
	f_lifespan(0.f),
	rotation(0.f),
	rotationspeed(0.f)
{
	// w/e
}

ParticleObject::~ParticleObject()
{
}

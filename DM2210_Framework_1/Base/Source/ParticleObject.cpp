#include "ParticleObject.h"

ParticleObject::ParticleObject(GameObject::GAMEOBJECT_TYPE typeValue = GameObject::GO_NIL) // defaults to a nil
	: GameObject(typeValue),
	rotation(0.f),
	rotationspeed(0.f)
{
}

ParticleObject::~ParticleObject()
{
}

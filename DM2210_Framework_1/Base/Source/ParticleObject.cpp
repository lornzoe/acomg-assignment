#include "ParticleObject.h"

ParticleObject::ParticleObject(GameObject::GAMEOBJECT_TYPE typeValue =  GameObject::GO_NIL) // defaults to a nil
	:	GameObject(typeValue)
{
}

ParticleObject::~ParticleObject()
{
}

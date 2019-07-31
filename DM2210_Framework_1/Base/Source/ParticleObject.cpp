	#include "ParticleObject.h"

ParticleObject::ParticleObject(GEOMETRY_TYPE typeValue = GEO_SAMPLEOBJ) // defaults to a nil
	: GameObject(typeValue),
	f_lifespan(0.f),
	f_timeElapsed(0.f),
	rotation(0.f),
	rotationspeed(0.f)
{
	// w/e
}

ParticleObject::~ParticleObject()
{
}

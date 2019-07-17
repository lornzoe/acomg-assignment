#include "GameObject.h"

//Vector3 GameObject::s_v_playerPos = Vector3(0.f, 0.f, 0.f);

Vector3 GameObject::s_v_gravity = Vector3(0.f, -9.8f, 0.f);

GameObject::GameObject(GAMEOBJECT_TYPE typeValue = GO_NIL)
	:	b_active(false),
		e_goType(typeValue),
		v_pos(0, 0, 0),
		v_vel(0, 0, 0),
		v_dir(0, 0, 0),
		v_scale(1, 1, 1),
		b_isAnimation(false),
		b_isBillboard(false)
{
}

GameObject::~GameObject()
{
}

void GameObject::SetPlayerPosition(Vector3 &v_newPosition)
{
	s_v_playerPos = &v_newPosition; // playerpos will point to the address of the camera's position vector3.
}

bool GameObject::UpdatePlayerPosition(Vector3 v_newPosition)
{
	if (s_v_playerPos != v_newPosition)
	{
		s_v_playerPos = v_newPosition;
		s_b_playerPosChanged = true;

		return true;
	}
		return false;
}

void GameObject::SetGravity(Vector3 v_newGravity)
{
	s_v_gravity = v_newGravity;
}


#pragma once
#include "Vector3.h"
#include "Mesh.h"

#ifndef GAMEOBJ_H
#define GAMEOBJ_H

class GameObject
{
public:
	enum GAMEOBJECT_TYPE
	{
		GO_NIL,
		GO_2D, // covers 2d quads, particle effects
		GO_3D, // covers 3d objects
		GO_OTHERS,

		GO_TOTAL
	};

	bool b_active;
	GAMEOBJECT_TYPE e_goType;
	Vector3 v_pos;
	Vector3 v_vel;
	Vector3 v_scale;
	Vector3 v_dir;

	bool b_isAnimation;
	bool b_isBillboard;

	//bool b_isCollidable;
	// also maybe insert in future: collision comoponent pointer.

	GameObject(GAMEOBJECT_TYPE typeValue);
	~GameObject();

	static void SetPlayerPosition(Vector3 &v_newPosition); // use only when initialising
	static bool UpdatePlayerPosition(Vector3 v_newPosition);

	static void SetGravity(Vector3 v_newGravity);
private: // we don't want to touch these values through a member.
	static Vector3 * s_v_playerPos; // pointer to the player camera's position.

	static Vector3 s_v_gravity;
};

#endif

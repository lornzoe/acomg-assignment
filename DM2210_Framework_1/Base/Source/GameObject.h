#pragma once
#include "Vector3.h"
#include "Mesh.h"

#ifndef GAMEOBJ_H
#define GAMEOBJ_H

struct GameObject
{

	enum GAMEOBJECT_TYPE
	{
		GO_NONE,

		GO_2D, // covers 2d quads, particle effects
		GO_3D, // covers 3d objects

		GO_TOTAL
	};

	Vector3 v_pos;
	Vector3 v_vel;
	Vector3 v_scale;
	Vector3 v_dir;

	Mesh* m_meshPointer;

	bool b_isAnimation;
	bool b_isBillboard;

	bool b_isCollidable;
	// also insert in future: collision comoponent pointer.

	GameObject();
	~GameObject();

	virtual void Update(double dt);

private:
	static Vector3 s_v_playerPos;
	static bool s_b_playerPosChanged;
	void UpdatePlayerPosition(Vector3 v_newPosition);
};

#endif

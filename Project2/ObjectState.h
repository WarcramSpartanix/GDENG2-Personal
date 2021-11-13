#pragma once
#include "Vector3D.h"

class ObjectState
{
public:
	ObjectState(Vector3D pos, Vector3D rot, Vector3D scl): position(pos), rotation(rot), scale(scl)
	{	};
	ObjectState()
	{	};
	~ObjectState()
	{	};

	Vector3D position, rotation, scale;
};
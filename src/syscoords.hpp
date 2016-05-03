#pragma once
#include"vector3f.h"

enum turnType
{
	negative,
	positive
};
struct SysCoords
{
	Vector3f axisX;
	Vector3f axisY;
	Vector3f axisZ;
	Vector3f point;
	
	SysCoords(Vector3f axisX, Vector3f axisY, Vector3f axisZ, Vector3f point);

	void Rotate(Vector3f axis, turnType type);
};
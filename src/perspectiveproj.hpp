#pragma once
#include<iostream>

struct Column
{
	float q1;
	float q2;
	float q3;
	float q4;
};

struct Matrix4x4f
{
	Column column1;
	Column column2;
	Column column3;
	Column column4;
	Matrix4x4f( float q11, float q12, float q13, float q14,
				float q21, float q22, float q23, float q24,
				float q31, float q32, float q33, float q34,
				float q41, float q42, float q43, float q44);
	Matrix4x4f();
	void InitPerspectiveProj(float ar, float zNear, float zFar, float vertAng);
};

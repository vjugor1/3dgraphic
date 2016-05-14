#include"perspectiveproj.hpp"
Matrix4x4f::Matrix4x4f(float q11, float q12, float q13, float q14,
	float q21, float q22, float q23, float q24,
	float q31, float q32, float q33, float q34,
	float q41, float q42, float q43, float q44)
{
	this->column1.q1 = q11;
	this->column1.q2 = q21;
	this->column1.q3 = q31;
	this->column1.q4 = q41;
	this->column2.q1 = q12;
	this->column2.q2 = q22;
	this->column2.q3 = q32;
	this->column2.q4 = q42;
	this->column3.q1 = q13;
	this->column3.q2 = q23;
	this->column3.q3 = q33;
	this->column3.q4 = q43;
	this->column4.q1 = q14;
	this->column4.q2 = q24;
	this->column4.q3 = q34;
	this->column4.q4 = q44;
}

Matrix4x4f::Matrix4x4f()
{
	this->column1.q1 = 0.0f;
	this->column1.q2 = 0.0f;
	this->column1.q3 = 0.0f;
	this->column1.q4 = 0.0f;
	this->column2.q1 = 0.0f;
	this->column2.q2 = 0.0f;
	this->column2.q3 = 0.0f;
	this->column2.q4 = 0.0f;
	this->column3.q1 = 0.0f;
	this->column3.q2 = 0.0f;
	this->column3.q3 = 0.0f;
	this->column3.q4 = 0.0f;
	this->column4.q1 = 0.0f;
	this->column4.q2 = 0.0f;
	this->column4.q3 = 0.0f;
	this->column4.q4 = 0.0f;
}

void Matrix4x4f::InitPerspectiveProj(float ar, float zNear, float zFar, float vertAng)
{
	float zRange = zNear - zFar;
	float tanHalfFOV = tanf(vertAng / 2.0f);

	this->column1.q1 = 1.0f / (tanHalfFOV * ar);
	this->column2.q1 = 0.0f;
	this->column3.q1 = 0.0f;
	this->column4.q1 = 0.0f;

	this->column1.q2 = 0.0f;
	this->column2.q2 = 1.0f / tanHalfFOV;
	this->column3.q2 = 0.0f;
	this->column4.q2 = 0.0f;

	this->column1.q3 = 0.0f;
	this->column2.q3 = 0.0f;
	this->column3.q3 = (-zNear - zFar) / zRange;
	this->column4.q3 = 2.0f * zFar * zNear / zRange;

	this->column1.q4 = 0.0f;
	this->column2.q4 = 0.0f;
	this->column3.q4 = 1.0f;
	this->column4.q4 = 0.0f;

}
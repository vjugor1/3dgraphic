#pragma once
#include <iostream>
struct Vector3f
{
  float x, y, z;

  Vector3f();

  Vector3f(float x, float y, float z);
  

  Vector3f operator *=(float d);
  Vector3f operator +=(Vector3f right);
  Vector3f operator -=(Vector3f right);
  float SquareLength();
  float Length();
  float GetAng(Vector3f v1);
  Vector3f GetNorm();
  Vector3f GetXYProj(); //attention! return (x,y,0)^T
  Vector3f GetXZProj();
  Vector3f GetYZProj();
 // Vector3f Rotate(Vector3f axis, float ang);
  void Print();
};

Vector3f operator +(Vector3f left, Vector3f right);
Vector3f operator -(Vector3f left, Vector3f right);
Vector3f operator *(Vector3f v, float d);
Vector3f operator *(float d, Vector3f v);
//float operator ^(Vector3f v0, Vector3f v1);
float operator *(Vector3f v1, Vector3f v2);

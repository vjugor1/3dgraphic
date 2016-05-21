#include "Vector3f.h"
Vector3f::Vector3f()
{
  this->x = 0;
  this->y = 0;
  this->z = 0;
}

Vector3f::Vector3f(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector3f Vector3f::operator *=(float d)
{
  this->x *= d;
  this->y *= d;
  this->z *= d;
  return *this;
}
Vector3f Vector3f::operator +=(Vector3f right)
{
  this->x += right.x;
  this->y += right.y;
  this->z += right.z;
  return *this;
}
Vector3f Vector3f::operator -=(Vector3f right)
{
  this->x -= right.x;
  this->y -= right.y;
  this->z -= right.z;
  return *this;
}
float Vector3f::SquareLength()
{
  return x * x + y * y + z * z;
}
float Vector3f::Length()
{
  return std::sqrt(SquareLength());
}

void Vector3f::Print()
{
  std::cout << "x: " << this->x << "y: " << this->y << "z: " << this->z << "\n";
}

Vector3f operator +(Vector3f left, Vector3f right)
{
  Vector3f result;

  result.x = left.x + right.x;
  result.y = left.y + right.y;
  result.z = left.z + right.z;
  return result;
}

Vector3f operator -(Vector3f left, Vector3f right)
{
  Vector3f result;

  result.x = left.x - right.x;
  result.y = left.y - right.y;
  result.z = left.z - right.z;

  return result;
}

Vector3f operator *(Vector3f v, float d)
{
  Vector3f result;

  result.x = v.x * d;
  result.y = v.y * d;
  result.z = v.z * d;
  return result;
}

Vector3f operator *(float d, Vector3f v)
{
  return v * d;
}


float operator *(Vector3f v1, Vector3f v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
Vector3f operator ^(Vector3f v1, Vector3f v2)
{
		return (Vector3f(v1.y * v2.z - v1.z * v2.y,
				v1.z * v2.x - v1.x * v2.z,
				v1.x * v2.y - v1.y * v2.x));

}
Vector3f Vector3f::GetNorm()
{
	
	
	if ((*this).x == 0.0f && (*this).y == 0.0f && (*this).z == 0.0f)
	{
		return Vector3f(0.0f, 0.0f, 0.0f);
	}
	else
	{
		return (*this) * (1.0f / (*this).Length());
	}
}



float Vector3f::GetAng(Vector3f v2)
{
	if ((*this).GetNorm() * v2.GetNorm() > 1.0f)
	{
		std::cout << "WARNING\n";	//LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOL!!!!!!!!!!!!!!!!!!
		return acosf(floorf((*this).GetNorm() * v2.GetNorm()));
	}
	return acosf((*this).GetNorm() * v2.GetNorm());
}

Vector3f Vector3f::GetXYProj()
{
	return Vector3f((*this).x,
					(*this).y,
					0.0f);
}

Vector3f Vector3f::GetXZProj()
{
	return Vector3f((*this).x,
					0.0f,
					(*this).z);
}

Vector3f Vector3f::GetYZProj()
{
	return Vector3f(0.0f,
					(*this).y,
					(*this).z);
}
void Vector3f::Rotate(Vector3f axis)
{
	Vector3f currVec = (*this);
	Vector3f axisNorm = axis.GetNorm();
	/*std::cout << "axisNorm: \n";
	axisNorm.Print();
	std::cout << "\n";*/
	Vector3f vecAxisProj = ((*this) * axisNorm) * axisNorm;
	/*std::cout << "vecAxisProj: \n";
	vecAxisProj.Print();
	std::cout << "\n";*/
	Vector3f vecDiff = (*this) - vecAxisProj;
	/*std::cout << "DOT(AXISPROJ , VECDIFF) = " << vecDiff * vecAxisProj << std::endl;*/
	float vecDiffLen = vecDiff.Length();
	/*std::cout << "vecDiff: \n";
	vecDiff.Print();
	std::cout << "\n";*/
	Vector3f vecDiffPerpendicular = (axis ^ vecDiff);
	/*std::cout << "vecDiffPerpendicular: \n";
	vecDiffPerpendicular.Print();
	std::cout << "\n";*/
	Vector3f newVecDiff = (vecDiff.GetNorm() * cosf(axis.Length()) - vecDiffPerpendicular.GetNorm() * sinf(axis.Length())).GetNorm() * vecDiffLen;
	/*std::cout << "newVecDiff: \n";
	newVecDiff.Print();
	std::cout << "\n";
	std::cout << "res: \n";
	(vecAxisProj + newVecDiff).GetNorm().Print();*/
	
	(*this) =  (vecAxisProj + newVecDiff);
}


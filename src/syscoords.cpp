#include"syscoords.hpp"

SysCoords::SysCoords(Vector3f axisX, Vector3f axisY, Vector3f axisZ, Vector3f point)
{
	this->axisX = axisX;
	this->axisY = axisY;
	this->axisZ = axisZ;
	this->point = point;
}
//void Vector3f Rotate(Vector3f axis)
//{
//}

void SysCoords::Rotate(Vector3f rotPoint, Vector3f rotAxis)
{
	//Vector3f rotAxisXY = rotAxis.GetXYProj();
	// Test change

	//move in XY 
	float firstMoveAng = axisX.GetAng(rotAxis);
	
	Vector3f pointVec = point - rotPoint;

	//std::cout << "firstmoveang = " << firstMoveAng << "\n";
	//rotAxisXY.Print();
	 
	std::cout << "AXISX\n";
	axisX.Rotate(rotAxis);
	std::cout << "AXISY\n";
	axisY.Rotate(rotAxis);
	std::cout << "AXISZ\n";
	axisZ.Rotate(rotAxis);
	
	
}
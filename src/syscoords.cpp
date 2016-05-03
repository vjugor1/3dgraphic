#include"syscoords.hpp"

SysCoords::SysCoords(Vector3f axisX, Vector3f axisY, Vector3f axisZ, Vector3f point)
{
	this->axisX = axisX;
	this->axisY = axisY;
	this->axisZ = axisZ;
	this->point = point;
}


void SysCoords::Rotate(Vector3f rotAxis, turnType type)
{
	//Vector3f rotAxisXY = rotAxis.GetXYProj();

	//move in XY 
	float firstMoveAng = axisX.GetAng(rotAxis);
	
	//std::cout << "firstmoveang = " << firstMoveAng << "\n";
	//rotAxisXY.Print();
	Vector3f newAxisX = Vector3f(axisX.x * cosf(firstMoveAng) + axisY.x * sin(firstMoveAng),
								 axisX.y * cosf(firstMoveAng) + axisY.y * sin(firstMoveAng),
 								 axisX.z * cosf(firstMoveAng) + axisY.z * sin(firstMoveAng));
	Vector3f newAxisY = Vector3f(axisX.x * (-sinf(firstMoveAng)) + axisY.x * cosf(firstMoveAng),
								 axisX.y * (-sinf(firstMoveAng)) + axisY.y * cosf(firstMoveAng),
								 axisX.z * (-sinf(firstMoveAng)) + axisY.z * cosf(firstMoveAng));
	Vector3f newAxisZ = axisZ;

	axisX = newAxisX.GetNorm();
	axisY = newAxisY.GetNorm();
	axisZ = newAxisZ.GetNorm();
	//axisX.Print();
	//axisY.Print();
	//axisZ.Print();

	//std::cout << "XY OVERED\n";
	//move in XY overed
	//Vector3f rotAxisAfterFirstMove = Vector3f(1.0f, rotAxis.y, rotAxis.z);
	
	//move in XZ
	//std::cout << "XZ STARTED\n";
	//Vector3f rotAxisYZ = rotAxis.GetYZProj();
	float secondMoveAng = axisZ.GetAng(rotAxis);
	
	//std::cout << "secondmoveang = " << secondMoveAng << "\n";
//	rotAxisYZ.Print();


	newAxisX =			Vector3f(axisX.x * cosf(secondMoveAng) + axisZ.x * sin(secondMoveAng),
								 axisX.y * cosf(secondMoveAng) + axisZ.y * sin(secondMoveAng),
								 axisX.z * cosf(secondMoveAng) + axisZ.z * sin(secondMoveAng));
	newAxisY =			axisY;
	newAxisZ =			Vector3f(axisX.x * (-sinf(secondMoveAng)) + axisZ.x * cosf(secondMoveAng),
			 					 axisX.y * (-sinf(secondMoveAng)) + axisZ.y * cosf(secondMoveAng),
								 axisX.z * (-sinf(secondMoveAng)) + axisZ.z * cosf(secondMoveAng));

	axisX = newAxisX.GetNorm();
	axisY = newAxisY.GetNorm();
	axisZ = newAxisZ.GetNorm();
	//axisX.Print();
	//axisY.Print();
	//axisZ.Print();
	//std::cout <<  " XZ OVERED\n";
	//move in XZ overed

	//hero of the occasion
	float ang = rotAxis.Length()/50.0f;
	if (type)
		ang = -ang;
	newAxisX =			Vector3f(axisX.x * cosf(ang) + axisY.x * sin(ang),
								 axisX.y * cosf(ang) + axisY.y * sin(ang),
								 axisX.z * cosf(ang) + axisY.z * sin(ang));
	newAxisY =			Vector3f(axisX.x * (-sinf(ang)) + axisY.x * cosf(ang),
								 axisX.y * (-sinf(ang)) + axisY.y * cosf(ang),
								 axisX.z * (-sinf(ang)) + axisY.z * cosf(ang));
	newAxisZ =			axisZ;

	axisX = newAxisX.GetNorm();
	axisY = newAxisY.GetNorm();
	axisZ = newAxisZ.GetNorm();

	//over
	//now, lets roll back

	newAxisX = Vector3f(axisX.x * cosf(-secondMoveAng) + axisZ.x * sin(-secondMoveAng),
						axisX.y * cosf(-secondMoveAng) + axisZ.y * sin(-secondMoveAng),
						axisX.z * cosf(-secondMoveAng) + axisZ.z * sin(-secondMoveAng));
	newAxisY =			axisY;
	newAxisZ = Vector3f(axisX.x * (-sinf(-secondMoveAng)) + axisZ.x * cosf(-secondMoveAng),
						axisX.y * (-sinf(-secondMoveAng)) + axisZ.y * cosf(-secondMoveAng),
						axisX.z * (-sinf(-secondMoveAng)) + axisZ.z * cosf(-secondMoveAng));

	axisX = newAxisX.GetNorm();
	axisY = newAxisY.GetNorm();
	axisZ = newAxisZ.GetNorm();
	//XZ back
	//XY back
	newAxisX = Vector3f(axisX.x * cosf(-firstMoveAng) + axisY.x * sin(-firstMoveAng),
					 			 axisX.y * cosf(-firstMoveAng) + axisY.y * sin(-firstMoveAng),
								 axisX.z * cosf(-firstMoveAng) + axisY.z * sin(-firstMoveAng));
	newAxisY = Vector3f(axisX.x * (-sinf(-firstMoveAng)) + axisY.x * cosf(-firstMoveAng),
								 axisX.y * (-sinf(-firstMoveAng)) + axisY.y * cosf(-firstMoveAng),
								 axisX.z * (-sinf(-firstMoveAng)) + axisY.z * cosf(-firstMoveAng));
	newAxisZ =					 axisZ;

	axisX = newAxisX.GetNorm();
	axisY = newAxisY.GetNorm();
	axisZ = newAxisZ.GetNorm();
	//axisX.Print();
	//axisY.Print();
	//axisZ.Print();

	//XY back

}
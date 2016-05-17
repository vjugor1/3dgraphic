//GLSL

//uniform vec2 mousePosUniform;
uniform vec3 newXVec;
uniform vec3 newYVec;
uniform vec3 newZVec;
uniform vec3 coordPoint;
//uniform vec4 testVec4;
uniform float scrWidth;
uniform float scrLen;
uniform vec4 projVec1;
uniform vec4 projVec2;
uniform vec4 projVec3;
uniform vec4 projVec4;
float FuncSin(vec2 point)
{
	return (0.25*sin(50.0*(point.x + point.y)));
}
float FuncCos(vec2 point)
{
	return (0.25*cos(50.0*(point.x + point.y)));
}

float sqr(vec3 vec)
{
	return dot(vec, vec);
}

float FuncBall(vec3 point)
{
	//return point.x;
	//return log(abs(point.x*point.x + point.y*point.y)) - point.z ;
	//return (120.0*cos(20.0*(point.x + point.y)) - point.z);
	//return dot((point - vec3(0.5, 0.5, 0.0)), (point - vec3(0.5, 0.5, 0.0))) - 0.2;
	return 1.0 / sqr(point - vec3(0.5, 0.5, 0.0)) + 1.0 / sqr(point - vec3(0.9, 0.5, 0.0)) - 1.0 / 0.025;
	//return 0.25*sin(log(point.x*point.y)) - point.z; //!!!!!
	//return 0.25 * sin(point.x) * cos(point.y) - point.z;
	//return 0.25 * cos(point.x * point.y) - point.z;
	//return 0.00001*tan(0.25 * sin(point.x) * cos(point.y) - point.z);
	//return 0.25 * (point.x * point.x + point.y * point.y - point.z * point.z);
	//<FUNCTION>
}



struct CastRes
{
	vec3 point;
	vec3 normal;
	bool exist;

};

struct LightPoint
{
	vec3 geomPos;
	vec3 normal;
	vec3 color;
	bool resExist;
};

//можно сделать тени например

LightPoint GetCrossPoint(vec3 rayDir, vec3 rayOrigin, float param, float paramStep, vec3 coordPoint)
{
	LightPoint pt;
	vec3 geomPosition;
	CastRes res;
	for (int i = 0; i < 50; i++)
	{
		

		
		//8float eps = 0.01f;
		//if (FuncBall((rayOrigin + rayDir * param) - vec3(0.0,0.0,eps)) * FuncBall(rayOrigin + rayDir * param) <= 0.0)
		if (FuncBall(rayOrigin + rayDir * param) * FuncBall(rayOrigin + rayDir * (param + paramStep)) <= 0)
		{
			res.exist = true;
			res.point = rayOrigin + rayDir * param;
			
			
			float currPoint = FuncBall(res.point.xyz);
			res.normal = normalize(vec3(
				FuncBall(res.point.xyz + vec3(paramStep, 0.0, 0.0)) - currPoint,
				FuncBall(res.point.xyz + vec3(0.0, paramStep, 0.0)) - currPoint,
				FuncBall(res.point.xyz + vec3(0.0, 0.0, paramStep)) - currPoint));
		///////////////////
			
		}
		else
		{
			res.exist = false;
			gl_FragColor.rgba = vec4(0.7, 0.7, 0.3, 1.0);
		}

		

		if (res.exist) 
		{
			pt.geomPos = res.point;
			pt.normal = res.normal;
			pt.color = vec3(0.0, 0.0, 1.0);
			pt.resExist = true;
			break;
			//gl_FragColor = vec4(color, 1.0);
		}
		else
		{
			pt.resExist = false;
		}
		//texCoord = texCoord + vec3(0.0, 0.0, -epsMove);
		//paramStep = (abs(FuncBall(rayOrigin + rayDir * param)) - (rayOrigin + rayDir * param).z) / 2.0;
		param = param + paramStep * abs(FuncBall(rayOrigin + rayDir * param));

	}
	//pt.geomPos = vec3(pt.geomPos.xy + coordPoint.xy, pt.geomPos.z);
	return pt;
}

////////////
void LightThisShit(LightPoint pt, vec2 windowSize, vec3 normal)
{
	if (pt.resExist)
	{
		vec3 lightPos1 = vec3(10.0, 10.0, 10.0);
		lightPos1 = normalize(newXVec) * lightPos1.x + normalize(newYVec) * lightPos1.y + normalize(newZVec) * lightPos1.z;// +vec3(0.5, 0.5, 0.0);

		vec3 lightDir1 = normalize(pt.geomPos - lightPos1);
		

		float diffuse1 = max(0.0, (dot(normal, lightDir1))); //scalar multipl
		
		vec3 lightColor = vec3(1.0, 1.0, 1.0);

		/*gl_FragColor.rgb = normal;
		gl_FragColor.a = 1.0;*/
		gl_FragColor.rgba = vec4(pt.color *
			lightColor * (diffuse1 * 0.8 + 0.2), 1.0);
		
	}
	else
	{
		
		//gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);

	}
	
}


void main()
{
	//
	vec2 windowSize = vec2(scrWidth, scrLen);
	vec2 texCoord = vec2(gl_FragCoord.xy / windowSize);
	//vec2 mousePos = mousePosUniform;
	//mousePos = normalize(newXVec.xy) * mousePos.x + normalize(newYVec.xy) * mousePos.y;
	
	//vec3 rayOrigin = vec3(texCoord, 0.0);
	//vec3 rayDir = vec3(0.0, 0.0, 1.0);

	float fov = 10.0;

	vec3 rayOrigin = coordPoint;// - vec3(0.5, 0.5, 0.0);// look all the way
	vec3 rayDir = vec3(texCoord - vec2(0.5, 0.5), -1.0);// *fov * 3.14 / 180.0;
	//rayOrigin = normalize(newXVec) * rayOrigin.x + normalize(newYVec) * rayOrigin.y + normalize(newZVec) * rayOrigin.z;
	rayDir = normalize(newXVec) * rayDir.x + normalize(newYVec) * rayDir.y + normalize(newZVec) * rayDir.z;
	

	//rayDir = (projVec1 * rayDir.x + projVec2 * rayDir.y + projVec3 * rayDir.z + projVec4 * 1.0).xyz;
	//rayOrigin = (projVec1 * rayOrigin.x + projVec2 * rayOrigin.y + projVec3 * rayOrigin.z + projVec4 * 1.0).xyz;

	/*rayOrigin = vec3(rayOrigin.x * newXVec.x + rayOrigin.y * newYVec.x + rayOrigin.z * newZVec.x,
		rayOrigin.x * newXVec.y + rayOrigin.y * newYVec.y + rayOrigin.z * newZVec.y,
		rayOrigin.x * newXVec.z + rayOrigin.y * newYVec.z + rayOrigin.z * newZVec.z);
	
	rayDir = vec3(rayDir.x * newXVec.x + rayDir.y * newYVec.x + rayDir.z * newZVec.x,
		rayDir.x * newXVec.y + rayDir.y * newYVec.y + rayDir.z * newZVec.y,
		rayDir.x * newXVec.z + rayDir.y * newYVec.z + rayDir.z * newZVec.z);
	*/
	float param = 0.02;
	float paramStep = 0.002;
	
	
	
	//CastRes res = GetFuncCast(rayOrigin, rayDir, param);
	




	LightPoint pt = GetCrossPoint(rayDir, rayOrigin, param, paramStep, coordPoint);

	//TurnThisShit(pt);
	

	//pt.geomPos = (projVec1 * pt.geomPos.x + projVec2 * pt.geomPos.y + projVec3 * pt.geomPos.z + projVec4 * 1.0).xyz;
	LightThisShit(pt, windowSize, pt.normal); //должна возвращать цвет
	
	


	/*if (Func(rayOrigin + rayDir/0.9) >= 0)
	{
		gl_FragColor.rgba = vec4(1.0, 0.0, 0.0, 1.0);
	}
	if (Func(rayOrigin + rayDir / 0.9) < 0)
	{
		gl_FragColor.rgba = vec4(0.0, 1.0, 0.0, 1.0);
	}*/

	//gl_FragColor.rgba = testVec4;
	//gl_FragColor.rgb = projVec1.xyz;
}
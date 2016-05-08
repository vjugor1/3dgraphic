//GLSL

uniform vec2 mousePosUniform;
uniform vec3 newXVec;
uniform vec3 newYVec;
uniform vec3 newZVec;
uniform vec3 coordPoint;
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
	//return log(abs(point.x + point.y)) ;
	//return (0.1*cos(20.0*(point.x + point.y)) + point.z);
	//return dot((point - vec3(0.7, 0.5, 0.0)), (point - vec3(0.7, 0.5, 0.0))) - 0.2;
	return 1.0 / sqr(point - vec3(0.5, 0.5, 0.0)) + 1.0 / sqr(point - vec3(0.9, 0.5, 0.0)) - 1.0 / 0.025;
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
	for (int i = 0; i < 100; i++)
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
		param = param + paramStep;

	}
	//pt.geomPos = vec3(pt.geomPos.xy + coordPoint.xy, pt.geomPos.z);
	return pt;
}

////////////
void LightThisShit(LightPoint pt, vec2 windowSize, vec2 mousePos, vec3 normal)
{
	if (pt.resExist)
	{
		vec3 lightPos1 = vec3(mousePos / windowSize, 1.0);
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
	vec2 windowSize = vec2(800.0, 600.0);
	vec2 texCoord = vec2(gl_FragCoord.xy / windowSize);
	vec2 mousePos = mousePosUniform;
	//mousePos = normalize(newXVec.xy) * mousePos.x + normalize(newYVec.xy) * mousePos.y;
	
	//vec3 rayOrigin = vec3(texCoord, 0.0);
	//vec3 rayDir = vec3(0.0, 0.0, 1.0);

	vec3 rayOrigin = coordPoint;// look all the way
	vec3 rayDir = vec3(texCoord, -1.0);
	rayOrigin = normalize(newXVec) * rayOrigin.x + normalize(newYVec) * rayOrigin.y + normalize(newZVec) * rayOrigin.z;
	rayDir = normalize(newXVec) * rayDir.x + normalize(newYVec) * rayDir.y + normalize(newZVec) * rayDir.z;
	
	/*rayOrigin = vec3(rayOrigin.x * newXVec.x + rayOrigin.y * newYVec.x + rayOrigin.z * newZVec.x,
		rayOrigin.x * newXVec.y + rayOrigin.y * newYVec.y + rayOrigin.z * newZVec.y,
		rayOrigin.x * newXVec.z + rayOrigin.y * newYVec.z + rayOrigin.z * newZVec.z);
	
	rayDir = vec3(rayDir.x * newXVec.x + rayDir.y * newYVec.x + rayDir.z * newZVec.x,
		rayDir.x * newXVec.y + rayDir.y * newYVec.y + rayDir.z * newZVec.y,
		rayDir.x * newXVec.z + rayDir.y * newYVec.z + rayDir.z * newZVec.z);
	*/
	float param = 0.02;
	float paramStep = 0.02;
	
	
	
	//CastRes res = GetFuncCast(rayOrigin, rayDir, param);
	




	LightPoint pt = GetCrossPoint(rayDir, rayOrigin, param, paramStep, coordPoint);

	//TurnThisShit(pt);
	
	LightThisShit(pt, windowSize, mousePos, pt.normal); //должна возвращать цвет

	


	/*if (Func(rayOrigin + rayDir/0.9) >= 0)
	{
		gl_FragColor.rgba = vec4(1.0, 0.0, 0.0, 1.0);
	}
	if (Func(rayOrigin + rayDir / 0.9) < 0)
	{
		gl_FragColor.rgba = vec4(0.0, 1.0, 0.0, 1.0);
	}*/


}
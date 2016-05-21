//GLSL

//uniform vec2 mousePosUniform;
uniform vec3 newXVec;
uniform vec3 newYVec;
uniform vec3 newZVec;
uniform vec3 coordPoint;
uniform vec3 gotColor;
uniform vec3 looseColor; 

uniform float scrWidth;
uniform float scrLen;




float FuncPool(vec3 point)
{
	
	//return 15.0 * log(abs(point.x*point.x + point.y*point.y)) - point.z ;
	//return 30.0*(0.25*cos(7.0*(point.x + point.y)) - point.z);
	//return dot((point - vec3(0.5, 0.5, 0.0)), (point - vec3(0.5, 0.5, 0.0))) - 0.2;
	//return (1.0 / sqrt(point - vec3(0.5, 0.5, 0.0)) + 1.0 / sqrt(point - vec3(0.9, 0.5, 0.0)) - 1.0 / 0.025);
	return 100.0 * (0.25*sin(log(point.x*point.y)) - point.z); //!!!!!
	//return 0.25 * sin(point.x) * cos(point.y) - point.z;
	//return 0.25 * cos(point.x * point.y) - point.z;
	//return 0.00001*tan(0.25 * sin(point.x) * cos(point.y) - point.z);
	//return 0.25 * (point.x * point.x + point.y * point.y - point.z * point.z);
	//return  10.0 * (0.05* cos( 50.0 * point.x * point.y) - point.z);
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
	for (int i = 0; i < 150; i++)
	{
		if (FuncPool(rayOrigin + rayDir * param) * FuncPool(rayOrigin + rayDir * (param + paramStep)) <= 0)
		{
			res.exist = true;
			res.point = rayOrigin + rayDir * (param - paramStep / 2.0);
					
			float currPoint = FuncPool(res.point.xyz);
			res.normal = normalize(vec3(
				FuncPool(res.point.xyz + vec3(paramStep, 0.0, 0.0)) - currPoint,
				FuncPool(res.point.xyz + vec3(0.0, paramStep, 0.0)) - currPoint,
				FuncPool(res.point.xyz + vec3(0.0, 0.0, paramStep)) - currPoint));
			
		}
		else
		{
			res.exist = false;
			
		}

		

		if (res.exist) 
		{
			pt.geomPos = res.point;
			pt.normal = res.normal;
			pt.color = gotColor;
			pt.resExist = true;
			break;
			//gl_FragColor = vec4(color, 1.0);
		}
		else
		{
			pt.resExist = false;
			gl_FragColor.rgb = looseColor; //vec4(0.7, 0.7, 0.3, 1.0);
		}
		param = param + paramStep;// *abs(FuncPool(rayOrigin + rayDir * param));
		

	}
	
	return pt;
}

////////////
vec3 LightThisBuddy(LightPoint pt, vec2 windowSize, vec3 normal)
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
		
		return pt.color;
	}
	else
	{
		
		//gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
		return looseColor;
	}
	
}


void main()
{
	
	vec2 windowSize = vec2(scrWidth, scrLen);
	vec2 texCoord = vec2(gl_FragCoord.xy / windowSize);
	
	
	
	float fov = 10.0;

	vec3 rayOrigin = coordPoint;// - vec3(0.5, 0.5, 0.0);// look all the way
	vec3 rayDir = vec3(texCoord - vec2(0.5, 0.5), -1.0);// *fov * 3.14 / 180.0;
	
	rayDir = normalize(newXVec) * rayDir.x + normalize(newYVec) * rayDir.y + normalize(newZVec) * rayDir.z;
	
	

	
	float param = 0.02;
	float paramStep = 0.02;
	
	
	
	

	


	LightPoint pt = GetCrossPoint(rayDir, rayOrigin, param, paramStep, coordPoint);

	
	
	
	LightThisBuddy(pt, windowSize, pt.normal); 
	
	


	}
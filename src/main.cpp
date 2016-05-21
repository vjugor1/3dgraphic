#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "syscoords.hpp"

//#include "matrix_transform.hpp"
//#include <GL\glew.h>

void RenderFullScreenQuad(sf::RenderWindow* wnd)
{
	sf::Vertex vertices[4];
	for (int i = 0; i < 4; i++)
	{
		vertices[i].color = sf::Color::Red;

	}
	vertices[1].color = sf::Color::Green;
	float w = float(wnd->getSize().x);
	float h = float(wnd->getSize().y);

	vertices[0].position = sf::Vector2f(0.0f, 0.0f);
	vertices[1].position = sf::Vector2f(w, 0.0f);
	vertices[2].position = sf::Vector2f(w, h);
	vertices[3].position = sf::Vector2f(0.0f, h);
	wnd->draw(vertices, 4, sf::Quads);
}


#define SCREENWIDTH 1260.0f
#define SCREENLENGTH 768.0f


//GLSL - OpenGl
//HLSL -DirectX
//Cg - NVidia
//3d->2d vertex shader projection
//fragment shader color filling
//today 2d/3d fragment shader

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREENWIDTH, SCREENLENGTH), "Awesome window");

	sf::Texture tex;
	//if (!tex.loadFromFile("data/chesterfield-normal.png"))
	if (!tex.loadFromFile("C:\\Users\\HP\\Desktop\\CPP projectz\\hometask130416(openglfunc) - sfml - copy\\bin\\data\\zazaka.png"))
	{
		std::cout << "Error: atlas not loaded" << std::endl;
	}
	else
	{
		std::cout << "Atlas loaded\n";
	}
	tex.setSmooth(true);//сглаживание

	

	sf::Shader shader;
	//shader.loadFromFile("data\\shaders\\fragmentshader.frag", sf::Shader::Fragment);
	shader.loadFromFile("C:\\Users\\HP\\Desktop\\CPP projectz\\hometask130416(openglfunc) - sfml - copy\\bin\\data\\shaders\\fragmentshader.frag", sf::Shader::Fragment);
	sf::Shader::bind(&shader);

	sf::Vector2f minPoint(-1.0f, -1.0f);
	sf::Vector2f maxPoint(1.0f, 1.0f);
	sf::Vector2f delta;

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame;
	timePerFrame = sf::seconds(1.0f / 20.0f);
	float pi = 3.1415926535f;
	//float ang = pi / 20.0f;
	float angularVelocity = pi * 10.0f;
	float dt = 1e-3f;
	Vector3f newXVec(1.0f,
		0.0f,
		0.0f);
	Vector3f newYVec(0.0f,
		1.0f,
		0.0f);
	Vector3f newZVec(0.0f,
		0.0f,
		1.0f);
	Vector3f point(0.5f,
		0.5f,
		1.0f);
	SysCoords sys(newXVec, newYVec, newZVec, point);

	sf::Vector2f currMousePos = (sf::Vector2f)(sf::Mouse::getPosition(window));
	sf::Vector2f prevMousePos = (sf::Vector2f)(sf::Mouse::getPosition(window));

	sf::Vector3f gotColor(72.0f / 255.0f, 91.0f / 255.0f, 178.0f / 255.0f);
	sf::Vector3f looseColor(136.0f / 255.0f, 110.0f / 255.0f, 46.0f / 255.0f);
	while (window.isOpen())
	{
		currMousePos = (sf::Vector2f)(sf::Mouse::getPosition(window));
		timeSinceLastUpdate += clock.restart();
		sf::Event evt;
		while (window.pollEvent(evt))
		{

			if (evt.type == sf::Event::Closed)
			{
				window.close();
			}
		}


		window.clear();	
		

		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			//try to rotate reference to local axises, not global
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				sys.point = sys.point + sys.axisY * dt * 10.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				sys.point = sys.point - sys.axisY * dt * 10.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				sys.point = sys.point - sys.axisX * dt * 10.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				sys.point = sys.point + sys.axisX * dt * 10.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
			{
				sys.point = sys.point + sys.axisZ * dt * 10.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
			{
				sys.point = sys.point - sys.axisZ * dt * 10.0f;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				sys.Rotate(sys.point, sys.axisZ * angularVelocity * dt);

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				sys.Rotate(Vector3f(0.5, 0.5, 0.0), sys.axisZ * angularVelocity * (-dt));
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				
				sys.Rotate(Vector3f(0.5, 0.5, 0.0), sys.axisY * angularVelocity * dt);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				
				sys.Rotate(Vector3f(0.5, 0.5, 0.0), sys.axisY * angularVelocity * (-dt));
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			{
				
				sys.Rotate(Vector3f(0.5, 0.5, 0.0), sys.axisX * angularVelocity * dt);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				
				sys.Rotate(Vector3f(0.5, 0.5, 0.0), sys.axisX * angularVelocity * (-dt));
				//sys.point = sys.point - sys.axisY * angularVelocity * dt; //WIIIIIN
			}

			sf::Vector2f mouseDelta = currMousePos - prevMousePos;
			//std::cout << "currMousepos.x = " << currMousePos.x / window.getSize().x << "\ncurrMousePos.y = " << currMousePos.y / window.getSize().y << "\n";
			//std::cout << " mouseDelta.x = " << mouseDelta.x << "\n mouseDelta.y = " << mouseDelta.y;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (mouseDelta.x != 0.0f) && (mouseDelta.y != 0.0f))
			{
				//sys.Rotate(Vector3f(currMousePos.x / window.getSize().x, (window.getSize().y - currMousePos.y) / window.getSize().y, 0.0f), sys.axisX * mouseDelta.y * 0.001f);
				//sys.Rotate(Vector3f(currMousePos.x / window.getSize().x, (window.getSize().y - currMousePos.y) / window.getSize().y, 0.0f), Vector3f(0.0f, 1.0f, 0.0f) * mouseDelta.x * 0.001f);
				sys.Rotate(Vector3f(0.5, 0.5, 0.0), sys.axisX * mouseDelta.y * 0.001f);
				sys.Rotate(Vector3f(0.5, 0.5, 0.0), Vector3f(0.0f, 1.0f, 0.0f) * mouseDelta.x * 0.001f);
			}
			sf::Vector3f goX = sf::Vector3f(sys.axisX.x, sys.axisX.y, sys.axisX.z);
			sf::Vector3f goY = sf::Vector3f(sys.axisY.x, sys.axisY.y, sys.axisY.z);
			sf::Vector3f goZ = sf::Vector3f(sys.axisZ.x, sys.axisZ.y, sys.axisZ.z);
			sf::Vector3f goPoint = sf::Vector3f(sys.point.x, sys.point.y, sys.point.z);
			shader.setParameter("newXVec", sf::Vector3f(goX));
			shader.setParameter("newYVec", sf::Vector3f(goY));
			shader.setParameter("newZVec", sf::Vector3f(goZ));
			shader.setParameter("coordPoint", sf::Vector3f(goPoint));
			shader.setParameter("gotColor", gotColor);
			shader.setParameter("looseColor", looseColor);
			
			
			
			
			shader.setParameter("scrWidth", SCREENWIDTH);
			shader.setParameter("scrLen", SCREENLENGTH);
			prevMousePos = currMousePos;
		}
		RenderFullScreenQuad(&window);

		

		window.display();


	}
	return 0;
}

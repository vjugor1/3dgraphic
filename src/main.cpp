#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "syscoords.hpp"
#include "matrix_transform.hpp"
#include <GL\glew.h>
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

//GLSL - OpenGl
//HLSL -DirectX
//Cg - NVidia
//3d->2d vertex shader projection
//fragment shader color filling
//today 2d/3d fragment shader

int main()
{
	int check = 0;
	sf::RenderWindow window(sf::VideoMode(1200, 660), "Awesome window");

	sf::Texture tex;
	if (!tex.loadFromFile("data/chesterfield-normal.png"))
	{
		std::cout << "Error: atlas not loaded" << std::endl;
	}
	else
	{
		std::cout << "Atlas loaded\n";
	}
	tex.setSmooth(true);//сглаживание

	sf::Shader shader;
	shader.loadFromFile("data\\shaders\\fragmentshader.frag", sf::Shader::Fragment);
	
	sf::Vector2f minPoint (-1.0f, -1.0f);
	sf::Vector2f maxPoint(1.0f, 1.0f);
	sf::Vector2f delta;
	
	sf::Clock clock;
	float pi = 3.1415926535f;
	float ang = pi / 20.0f;
	Vector3f newXVec(1.0f,
		0.0f,
		0.0f);
	Vector3f newYVec(0.0f,
		1.0f,
		0.0f);
	Vector3f newZVec(0.0f,
		0.0f,
		1.0f);
	Vector3f point(0.0f,
		0.0f,
		1.0f);
	SysCoords sys(newXVec, newYVec, newZVec, point);

	 
	 
	 
	while (window.isOpen())
	{
	
		sf::Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		
		
		window.clear();
		float accuracy = 1e-2f;
		delta = maxPoint - minPoint;
		sf::Shader::bind(&shader);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			sys.point = sys.point + Vector3f(0.0f, 0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			sys.point = sys.point - Vector3f(0.0f, 0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			sys.point = sys.point - Vector3f(0.1f, 0.0f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			sys.point = sys.point + Vector3f(0.1f, 0.0f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		{
			sys.point = sys.point + Vector3f(0.0f, 0.0f, 0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			sys.point = sys.point - Vector3f(0.0f, 0.0f, 0.1f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			sys.Rotate(Vector3f(0.0f, 0.0f, 1.0f), positive);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
		

			sys.Rotate(Vector3f(0.0f, 0.0f, 1.0f), negative);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			

			sys.Rotate(Vector3f(0.0f, 1.0f, 0.0f), positive);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			

			sys.Rotate(Vector3f(0.0f, 1.0f, 0.0f), negative);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			

			sys.Rotate(Vector3f(1.0f, 0.0f, 0.0f), positive);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			sys.Rotate(Vector3f(1.0f, 0.0f, 0.0f), negative);
		}

		sf::Vector2f cursorPos=
		 (sf::Vector2f)sf::Mouse::getPosition(window);
			shader.setParameter("mousePos",
				sf::Vector2f(cursorPos.x, window.getSize().y - cursorPos.y));
			sf::Vector3f goX = sf::Vector3f(sys.axisX.x, sys.axisX.y, sys.axisX.z);
			sf::Vector3f goY = sf::Vector3f(sys.axisY.x, sys.axisY.y, sys.axisY.z);
			sf::Vector3f goZ = sf::Vector3f(sys.axisZ.x, sys.axisZ.y, sys.axisZ.z);
			sf::Vector3f goPoint = sf::Vector3f(sys.point.x, sys.point.y, sys.point.z);
		shader.setParameter("newXVec", sf::Vector3f(goX));
		shader.setParameter("newYVec", sf::Vector3f(goY));
		shader.setParameter("newZVec", sf::Vector3f(goZ));
		shader.setParameter("coordPoint", sf::Vector3f(goPoint));
		//shader.setParameter("Matrix", MVP);
		//GLuint matrixId = glGetUniformLocation()
		shader.setParameter("minPoint", sf::Vector2f(minPoint));
		shader.setParameter("maxPoint", sf::Vector2f(maxPoint));
		shader.setParameter("time", clock.getElapsedTime().asSeconds());
		shader.setParameter("testTex", tex);
		RenderFullScreenQuad(&window);
		window.display();
	}
	return 0;
}

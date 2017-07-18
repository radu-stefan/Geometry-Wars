#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateShip(std::string name, glm::vec3 color)
{

	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  0),  color),
		VertexFormat(glm::vec3(-1,  1,  0),  color),
		VertexFormat(glm::vec3(0,    0,  0),  color),
		VertexFormat(glm::vec3(1,  1,  0),  color),
		VertexFormat(glm::vec3(1, -1,  0),  color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,	// indices for first triangle
		2, 3, 4,	// indices for second triangle
	};


	Mesh* ship = new Mesh(name);
	ship->InitFromData(vertices, indices);

	return ship;
}

Mesh* Object2D::CreateProjectile(std::string name, glm::vec3 color)
{

	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-0.1, -0.4,  0),  color),
		VertexFormat(glm::vec3(-0.1,  0.4,  0),  color),
		VertexFormat(glm::vec3(0.1,    0.4,  0),  color),
		VertexFormat(glm::vec3(0.1,  -0.4,  0),  color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,	// indices for first triangle
		0, 2, 3,	// indices for second triangle
	};


	Mesh* projectile = new Mesh(name);
	projectile->InitFromData(vertices, indices);

	return projectile;
}


Mesh* Object2D::CreateLife(std::string name, glm::vec3 color)
{

	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-0.2, -0.8,  0),  color),
		VertexFormat(glm::vec3(-0.2,  0.8,  0),  color),
		VertexFormat(glm::vec3(0.2,    0.8,  0),  color),
		VertexFormat(glm::vec3(0.2,  -0.8,  0),  color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,	// indices for first triangle
		0, 2, 3,	// indices for second triangle
	};


	Mesh* projectile = new Mesh(name);
	projectile->InitFromData(vertices, indices);

	return projectile;
}
#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	Mesh * CreateShip(std::string name, glm::vec3 color);

	Mesh * CreateProjectile(std::string name, glm::vec3 color);

	Mesh * CreateLife(std::string name, glm::vec3 color);

}



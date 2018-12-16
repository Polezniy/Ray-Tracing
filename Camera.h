#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "Ray.h"

#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:

	std::shared_ptr<Ray> createRay(glm::ivec2 pos);
	//Ray createRay(glm::ivec2 pos); 

private:

	glm::mat4 viewMatrix; // Represent camera's Position and Orientation.
	glm::mat4 projMatrix; // Camera lens.
};
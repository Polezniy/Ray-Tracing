#include "Camera.h"

std::shared_ptr<Ray> Camera::createRay(glm::ivec2 pos)
{
	std::shared_ptr<Ray> r = std::make_shared<Ray>();
	r->origin.x = pos.x;
	r->origin.y = pos.y;
	r->origin.z = 0;

	r->dir = glm::vec3(0, 0, -1);

	return r;
}

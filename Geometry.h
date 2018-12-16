#pragma once
#include <glm/glm.hpp>
#include <memory>

#include "Ray.h"
#include <thread>

struct Intersection
{
	float hitDistance; // A distance from ray origin to intersection point.
	glm::vec3 intersectP; // Intersection point.
	bool hit = false;
};

class Geometry
{
public:

	glm::vec3 closestPoint(std::shared_ptr<Ray> r, glm::vec3 point); //Closest point on ray.

	Intersection intersectSphere(std::shared_ptr<Ray> r, glm::vec3 centre, float radius); //Ray-sphere intersection.

	//glm::vec3 normal(glm::vec3 centre, glm::vec3 point);
};


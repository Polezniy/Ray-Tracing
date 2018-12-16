#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "Ray.h"
#include "Sphere.h"
#include "Geometry.h"

class Sphere;
class Geometry;

class RayTracer
{
public:

	glm::vec3 Tracer(std::shared_ptr<Ray> r, int a); // Returns a color;
	void add_sceneObj(std::shared_ptr<Sphere> s); // Adds an object to the list.

private:

	std::vector<std::shared_ptr<Sphere>> sceneObjs; // A list of objects in the scene.
	std::shared_ptr<Geometry> geometry;
	//Geometry geometry;
};
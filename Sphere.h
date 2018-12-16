#pragma once
#include <glm/glm.hpp>
#include <memory>

#include "Ray.h"
#include "RayTracer.h"

class RayTracer;

class Sphere
{
public:

	// Setters and Getters for Position, Radius and Colour of sphere.
	void SetPos(glm::vec3 p); 
	void SetRadius(float rad);
	void SetColour(glm::vec3 colour);

	glm::vec3 GetPos();
	glm::vec3 GetColour();

	float GetRadius();

	glm::vec3 Shade(std::shared_ptr<Ray> r, RayTracer& t, glm::vec3 inter, int a);

	glm::vec3 GetNormal(glm::vec3 n);

private:

	glm::vec3 colour;
	glm::vec3 pos;


	float radius;
};
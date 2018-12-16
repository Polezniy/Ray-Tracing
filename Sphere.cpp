#include <glm/glm.hpp>

#include "Sphere.h"

glm::vec3 Sphere::GetNormal(glm::vec3 n)
{
	return (n - pos) / radius;
}

void Sphere::SetPos(glm::vec3 p)
{
	pos = p;
}

void Sphere::SetRadius(float rad)
{
	radius = rad;
}

void Sphere::SetColour(glm::vec3 col)
{
	colour = col;
}

glm::vec3 Sphere::GetPos()
{
	return pos;
}

float Sphere::GetRadius()
{
	return radius;
}

glm::vec3 Sphere::GetColour()
{
	return colour;
}

glm::vec3 Sphere::Shade(std::shared_ptr<Ray> r, RayTracer& t, glm::vec3 inter, int a)
{
	glm::vec3 color = GetColour();
	glm::vec3 lightDirection = { 1.0f, 1.0f, -1.0f };
	glm::vec3 lightColor = { 1.0f, 1.0f, 1.0f };
	glm::vec3 pointLight = glm::vec3(100, 100, -100) - inter;

	float specularInt = 1.0f;

	// Ambient
	glm::vec3 ambientCol = glm::vec3(1.0f, 0.0f, 0.0f);
	float ambientstrength = 0.1f;
	glm::vec3 ambient = ambientstrength * color;

	// Diffuse
	lightDirection = glm::normalize(lightDirection);
	glm::vec3 surfaceNormal = glm::normalize(inter - pos);
	float diffuseColor = glm::max(glm::dot(lightDirection, surfaceNormal), 0.0f);

	// Point light diffuse
	pointLight = glm::normalize(pointLight);
	float pointLightDiffuseColor = glm::max(glm::dot(pointLight, surfaceNormal), 0.0f);

	// Specular
	glm::vec3 reflect = glm::reflect(-lightDirection, surfaceNormal);
	glm::vec3 view = glm::normalize(-r->dir);
	float specularColour = glm::pow(glm::max(glm::dot(view, glm::normalize(reflect)), 0.0f), 50);
	specularColour *= specularInt;

	// Point light specular
	glm::vec3 pointLightReflect = glm::reflect(-pointLight, surfaceNormal);
	float pointLightSpecularColour = glm::pow(glm::max(glm::dot(view, glm::normalize(pointLightReflect)), 0.0f), 50);
	pointLightSpecularColour *= specularInt;

	float dot = glm::dot(lightDirection, surfaceNormal);

	glm::vec3 reflectionColor;

	if (a > 0)
	{
		// Reflection
		std::shared_ptr<Ray> rayReflection = std::make_shared<Ray>();
		rayReflection->dir = glm::reflect(-r->dir, surfaceNormal);
		rayReflection->origin = inter + rayReflection->dir * 0.001f;
		reflectionColor = 0.5f * t.Tracer(rayReflection, a - 1);
	}

	glm::vec3 touchColor = (diffuseColor + pointLightDiffuseColor + specularColour + pointLightSpecularColour + ambient) * lightColor * color + reflectionColor;

	return glm::clamp(touchColor, glm::vec3(0), glm::vec3(1));
}

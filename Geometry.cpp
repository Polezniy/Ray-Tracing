#include "Geometry.h"
#include "Sphere.h"

#include <thread>

glm::vec3 Geometry::closestPoint(std::shared_ptr<Ray> r, glm::vec3 point)
{
	glm::vec3 origin = r->origin;
	glm::vec3 direction = r->dir;

	// ((P - a) * n) //
	float rayP = glm::dot(point - origin, direction); // Ray projection.	 

	// X = a + ((P - a) * n) * n //
	glm::vec3 X = origin + (direction * rayP); // The closest point.		

	return X;
}

Intersection Geometry::intersectSphere(std::shared_ptr<Ray> r, glm::vec3 centre, float radius)
{
	Intersection inter;;

	//a
	glm::vec3 origin = r->origin;

	//n
	glm::vec3 direction = r->dir;

	// P - a //
	glm::vec3 origToCentre = centre - origin; // A vector from origin of Ray to the centre of Sphere.

	// ((P - a) * n //
	float rayP = glm::dot(centre - origin, direction); // Ray projection.

	// d = || P - a - ((P - a)) * n )) n || //
	float d = glm::length(origToCentre - (rayP) * direction); // Distance from the closest point on Ray to the centre of Sphere.

	glm::vec3 X = closestPoint(r, centre); // Closest point on Ray to the centre of Sphere.

	if (d > radius) // If distance is bigger than radius, its not intersecting.
	{
		return inter;  // No intersection.
	}
	else
	{
		float X = sqrt(pow(radius, 2) - pow(d, 2)); // X

		// First intersection
		inter.hitDistance = rayP - X; // ((P - a) * n) - X // 
		glm::vec3 intersectPoint = origin + inter.hitDistance * direction; // a + (((P - a) * n) - X) * n //
		inter.hit = true;

		return inter; // Intersection.
	}
}
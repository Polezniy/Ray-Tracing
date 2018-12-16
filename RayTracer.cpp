#include "RayTracer.h"

glm::vec3 RayTracer::Tracer(std::shared_ptr<Ray> r, int a)
{
	glm::vec3 colour = glm::vec3(0, 0, 0);
	std::shared_ptr<Sphere> closestObj = nullptr;
	float distToPoint = INFINITY;
	glm::vec3 intersectPoint;

	for (size_t i = 0; i < sceneObjs.size(); i++) // Go through every object in the scene.
	{
		Intersection sphereInter = geometry->intersectSphere(r, sceneObjs.at(i)->GetPos(), sceneObjs.at(i)->GetRadius()); // Ray-sphere intersection function.
		
		if (sphereInter.hit)
		{
			if (sphereInter.hitDistance < distToPoint)
			{
				distToPoint = sphereInter.hitDistance;
				closestObj = sceneObjs.at(i);
				intersectPoint = sphereInter.intersectP;
			}
		}
		else
		{
			colour = glm::vec3(0, 0, 0); // Returning default colour if nothing was hit.
		}
	}

	if (closestObj != nullptr)
	{
		colour = closestObj->Shade(r, *this, intersectPoint, a);
	}

	return colour;
}

void RayTracer::add_sceneObj(std::shared_ptr<Sphere> s)
{
	sceneObjs.push_back(s);
}
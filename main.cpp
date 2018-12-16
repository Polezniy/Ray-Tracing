// File: main.cpp
// Author: Gleb Demenov.
// Program: Parallel Ray-tracing.

//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//
//								References:											//
//																					//
// Gabriel Gambetta - Computer Graphics from scratch.								//
// http://www.gabrielgambetta.com/computer-graphics-from-scratch/introduction.html	//
//																					//
// Scraththepixel - Volume 1: Foundations of 3D Rendering							//	
// http://www.scratchapixel.com/index.php?redirect									//
//																					//
// An Introduction to Parallel Computing in C++										//
// https://www.cs.cmu.edu/~15210/pasl.html#ch:fork-join								//
//																					//
//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <cmath>
#include <vector>
#include <exception>
#include <memory> 

#include "Ray.h"
#include "Camera.h"
#include "RayTracer.h"
#include "Sphere.h"

#include <thread> // Allows to launch different bits of code in different threads, thus speeding up the process.
#include <mutex> // Enables Mutual exclsuion.

#include <iostream> // For debug purposes.

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void thread1(std::shared_ptr<Camera> cam, SDL_Renderer* renderer, std::shared_ptr<RayTracer> rtrace); // A parallel thread.


int main(int argc, char* argv[]) // Main thread.
{
	std::mutex mtx; // Mutex for critical section.

	bool quit = false; // Flag to end the gameloop.

	SDL_Event event = { 0 };

	// Critical section //

	mtx.try_lock(); // Mutual exclusion, to lock data, until it is realeased, to avoid Race Conditions.

	SDL_Renderer *renderer;

	mtx.unlock();
	
	//	//	//	//	//	//

	//Camera* cam = new Camera; // testing //

	std::shared_ptr<Camera> cam = std::make_shared<Camera>();

	std::shared_ptr<RayTracer> rtrace = std::make_shared<RayTracer>();


	// SDL INITIALIZATION //
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::exception();
	}

	SDL_Window *window = SDL_CreateWindow("Ray_tracer",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// CREATING SPHERES //

	// Red sphere //
	std::shared_ptr<Sphere> redS = std::make_shared<Sphere>();
	redS->SetPos(glm::vec3(250, 100, -1.0f));
	redS->SetColour(glm::vec3(255, 0, 0));
	redS->SetRadius(50.0f);

	// Green sphere //
	std::shared_ptr<Sphere> greenS = std::make_shared<Sphere>();
	greenS->SetPos(glm::vec3(500, 100, -1.0f));
	greenS->SetColour(glm::vec3(0, 255, 0));
	greenS->SetRadius(50.0f);

	// Blue sphere //
	std::shared_ptr<Sphere> blueS = std::make_shared<Sphere>();
	blueS->SetPos(glm::vec3(375, 250, -1.0f));
	blueS->SetColour(glm::vec3(0, 0, 255));
	blueS->SetRadius(50.0f);

	// Adding all of spheres to the scene.
	rtrace->add_sceneObj(redS);
	rtrace->add_sceneObj(greenS);
	rtrace->add_sceneObj(blueS);

	std::thread t1(thread1, cam, renderer, rtrace); 

    t1.join(); // Launches another thread in parallel to the main.

	// Game loop //
	while (!quit)
	{
		//std::thread t1(thread1);

		//t1.join();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}

void thread1(std::shared_ptr<Camera> cam, SDL_Renderer* renderer, std::shared_ptr<RayTracer> rtrace)
{
	//std::cout << "THREAD!" << std::endl;
	for (int x = 0; x < WINDOW_WIDTH; x++)
	{
		for (int y = 0; y < WINDOW_HEIGHT; y++)
		{
			std::shared_ptr<Ray> ray = cam->createRay(glm::ivec2(x, y));
			/*Ray* r = new Ray;
			r = &cam->createRay(glm::ivec2(x, y));*/

			glm::vec3 colour = (rtrace->Tracer(ray, 2)* 255.0f);

			SDL_SetRenderDrawColor(renderer, colour.x, colour.y, colour.z, 255);
			SDL_RenderDrawPoint(renderer, x, y);

		}
	}
}
#include <SDL2/SDL.h>
#include <glm.hpp>

#include <vector>
#include <exception>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


int main(int arcc, char* argv[])
{
	struct Ray
	{
		glm::vec3 origin;
		glm::vec3 direction;
	};

	struct Triangle
	{
		glm::vec3 a;
		glm::vec3 b;
		glm::vec3 c;
		
		glm::vec3 color;
	};

	struct Camera
	{

	};

	struct RayTracer
	{

	};
	
	Ray r;
	RayTracer rt;

	Triangle tr;
	Triangle tr2;

	Camera c;

	/* SDL INITIALIZATION */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::exception();
	}

	SDL_Window *window = SDL_CreateWindow("Window",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

	bool quit = false;

	while (!quit)
	{
		SDL_Event event = { 0 };

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
#include <SDL.h>

#include "Assertion.h"
#include "SDLConfig.h"
#include "SDLManager.h"

SDLManager& SDLManager::Get()
{
	static SDLManager instance;
	return instance;
}

void SDLManager::Startup()
{
	CHECK(!bIsStartup_);

	SDL_FAILED(SDL_Init(SDL_INIT_EVERYTHING));

	SDL_FAILED(SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG));
	SDL_FAILED(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE));
	SDL_FAILED(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR_VERSION));
	SDL_FAILED(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MINOR_VERSION));
	SDL_FAILED(SDL_GL_SetAttribute(SDL_GL_RED_SIZE, GL_RED_SIZE));
	SDL_FAILED(SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, GL_GREEN_SIZE));
	SDL_FAILED(SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, GL_BLUE_SIZE));
	SDL_FAILED(SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, GL_ALPHA_SIZE));
	SDL_FAILED(SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, GL_DEPTH_SIZE));
	SDL_FAILED(SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, GL_STENCIL_SIZE));
	SDL_FAILED(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, GL_DOUBLEBUFFER));
	SDL_FAILED(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, GL_MULTISAMPLEBUFFERS));
	SDL_FAILED(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, GL_MULTISAMPLESAMPLES));

	int32_t x = 0;
	int32_t y = 0;

	if (WINDOW_POS_CENTERED)
	{
		x = SDL_WINDOWPOS_UNDEFINED;
		y = SDL_WINDOWPOS_UNDEFINED;
	}
	else if (WINDOW_POS_UNDEFINED)
	{
		x = SDL_WINDOWPOS_CENTERED;
		y = SDL_WINDOWPOS_CENTERED;
	}
	else
	{
		x = WINDOW_X;
		y = WINDOW_Y;
	}

	mainWindow_ = SDL_CreateWindow(WINDOW_TITLE, x, y, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	CHECK(mainWindow_ != nullptr);

	bIsStartup_ = true;
}

void SDLManager::Shutdown()
{
	CHECK(bIsStartup_);

	if (mainWindow_)
	{
		SDL_Window* window = reinterpret_cast<SDL_Window*>(mainWindow_);
		SDL_DestroyWindow(window);
		
		mainWindow_ = nullptr;
	}

	SDL_Quit();

	bIsStartup_ = false;
}

// OpenGL headers
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <SDL2/SDL_main.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "render.h"
extern int rotateX, rotateY, rotateZ;

int main(int argc, char *argv[])
{
    SDL_Window* window;
    SDL_GLContext glContext;
    
    //Use OpenGL 3.1 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // Initialize video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	// Display error message
	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	return -1;
    }

    // Create window
    window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			      800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
	// Display error message
	printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
	return -1;
    }

    
    // Create OpenGL context
    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
	printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
	return -1;
    }
    
    if (glewInit() != GLEW_OK) {
	printf( "Cannot init GLEW\n");
	return -1;
    }
    
    init();

    bool quit = false;
    SDL_Event event;
    while (!quit) {

        display();
	SDL_GL_SwapWindow(window);
	
	while (SDL_PollEvent(&event) != 0) {
	    switch (event.type) {
	    case SDL_QUIT:
		quit = true;
		break;
	    case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
		    rotateY -= 15;
		    printf("Left\n");
		    break;
		case SDLK_RIGHT:
		    rotateY += 15;
		    printf("Right\n");
		    break;
		case SDLK_UP:
		    rotateX -= 15;
		    printf("Up\n");
		    break;
		case SDLK_DOWN:
		    rotateX += 15;
		    printf("Down\n");
		    break;
		case SDLK_PAGEUP:
		    rotateZ += 15;
		    printf("PageUp\n");
		    break;
		case SDLK_PAGEDOWN:
		    rotateZ -= 15;
		    printf("PageDown\n");
		    break;
		case SDLK_HOME:
		    rotateX = rotateY = rotateZ = 0;
		    printf("Home\n");
		    break;
		case SDLK_ESCAPE:
		case SDLK_q:
		    printf("Escape\n");
		    quit = true;
		    break;
		default:
		    break;
		}
		break;
	    default:
		break;
	    }
	}
    }

    printf("Main loop exited normally.\n");
    
    // Destroy window
    SDL_DestroyWindow(window);
    window = NULL;
    
    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}

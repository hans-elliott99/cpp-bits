#include <iostream>
#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[])
{
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window *window = SDL_CreateWindow(
        "SDL Window",
         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
         WIDTH, HEIGHT, 
         SDL_WINDOW_ALLOW_HIGHDPI
        );
    // SDL_Surface* screenSurface = NULL;
    
    if (window == NULL)
    {
        std::cout << "Could not create window. Error: " << SDL_GetError() << std::endl;
        return 1;
    } 
    // else
    // {
    //     // Get window surface
    //     screenSurface = SDL_GetWindowSurface(window);
    //     // Fill with white
    //     SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    //     // Update surface
    //     SDL_UpdateWindowSurface(window);
    // }

    SDL_Event windowEvent;
    while (true)
    {
        if (SDL_PollEvent( &windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {break; }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;    
}
#include <iostream>

#include <SDL3/SDL.h>

#include "Core/Coordinator.hpp"
#include "Components.hpp"

bool gShowFPS = true;

Coordinator gCoordinator;

double hireTimeInSeconds()
{
    double t = SDL_GetTicks();
    t *= 0.001f;
    return t;
}

SDL_Texture* loadTextureFromFile(const char* pPath, SDL_Renderer* pR)
{
    SDL_Surface* surface = NULL;
    surface = SDL_LoadPNG(pPath);

    if (surface == NULL)
        SDL_LogError(SDL_LOG_PRIORITY_WARN, SDL_GetError());

    SDL_Texture* texture = SDL_CreateTextureFromSurface(pR, surface);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    SDL_DestroySurface(surface);

    return texture;
}

int main(int, char**) 
{
    gCoordinator.Init();

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_CreateWindowAndRenderer("2D Platformer", 1280, 720, SDL_WINDOW_RESIZABLE, &window, &renderer);

    bool isRunning = true;

    SDL_Event event;

    SDL_Texture* tex = loadTextureFromFile("spritesheets/axeman.png", renderer);

    // Time stepping
    const double dt = 0.01f;
    double accumulator = 0.0f;
    double currentTime = hireTimeInSeconds();

    double oneSecond = 0.f;
    int frameRenderedInOneSecond = 0;

    Sprite s;

    while (isRunning)
    {
        double newTime = hireTimeInSeconds();
        double frameTime = newTime - currentTime;

        // Avoid the spiral of death
        if (frameTime > 0.25f)
        {
            printf("Avoided the spiral of death.");
            frameTime = 0.25f;
        }

        currentTime = newTime;

        accumulator += frameTime;
        oneSecond += frameTime;

        // Physics, controls, etc
        while (accumulator >= dt)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT) isRunning = false;
            }

            // "Consume" the time the accumulator has "generated"
            accumulator -= dt;
        }

        // Calculate FPS
        if (gShowFPS && oneSecond >= 1)
        {
            std::string msg = "FPS: ";
            msg += std::to_string(frameRenderedInOneSecond);

            std::cout << msg << std::endl;

            oneSecond = 0;
            frameRenderedInOneSecond = 0;
        }

        frameRenderedInOneSecond++;

        // Where we are in between updates
        const double alpha = accumulator / dt;


        if (!SDL_RenderTextureRotated(renderer, tex, NULL, NULL, 30.f, NULL, SDL_FLIP_HORIZONTAL))
            SDL_LogError(SDL_LOG_PRIORITY_CRITICAL, SDL_GetError());
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}

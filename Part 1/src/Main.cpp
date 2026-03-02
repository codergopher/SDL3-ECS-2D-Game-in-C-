#include <iostream>

#include <SDL3/SDL.h>

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
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_CreateWindowAndRenderer("2D Platformer", 1280, 720, SDL_WINDOW_RESIZABLE, &window, &renderer);

    bool isRunning = true;

    SDL_Event event;

    SDL_Texture* tex = loadTextureFromFile("spritesheets/axeman.png", renderer);

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT) isRunning = false;
        }

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

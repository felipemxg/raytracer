#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL.h"
#include "raytracer.cpp"


int main(int argc, char * argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "error: failed to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    auto window = SDL_CreateWindow(
            "Raytracer",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            1280, 720,
            0);
    if (window == nullptr) {
        fprintf(stderr, "error: failed to create window: %s\n", SDL_GetError());
        return 1;
    }

    auto screen = SDL_GetWindowSurface(window);

    auto renderbuffer = SDL_CreateRGBSurfaceWithFormat(0,
            image_width,
            image_height,
            32,
            SDL_PIXELFORMAT_RGBA32);
    if (renderbuffer == nullptr) {
        fprintf(stderr, "error: failed to create surface: %s\n", SDL_GetError());
        return 1;
    }

    RaytracerRun(renderbuffer);

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
            else if (event.type == SDL_KEYDOWN
                    && event.key.keysym.sym == SDLK_ESCAPE)
                quit = true;
        }

        SDL_FillRect(screen, nullptr, 0);
        SDL_BlitSurface(renderbuffer, nullptr, screen, nullptr);
        SDL_UpdateWindowSurface(window);
    }

    return 0;
}

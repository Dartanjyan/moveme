#include "SDLApp.h"
#include <iostream>

SDLApp::SDLApp(const char *name, const int width, const int height)
    : name(name), width(width), height(height)
{
    
}

SDLApp::~SDLApp()
{

}

int SDLApp::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    window = SDL_CreateWindow(
        name,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        std::cerr << "Couldn't open a window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    std::cout << "Trying to run accelerated renderer..." << std::endl;
    if (renderer == NULL) {
        std::cout << "Couldn't use accelerated rendering (GPU): " << SDL_GetError() << "\n\nTrying to use software rendering (CPU)..." << std::endl;
        renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_SOFTWARE
        );
        if (renderer == NULL) {
            std::cerr << "Couldn't create software renderer: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        } else {
            std::cout << "Using software (CPU) rendering." << std::endl;
        }
    } else {
        std::cout << "Using accelerated (GPU) rendering." << std::endl;
    }

    return 0;
}

void SDLApp::shutdown()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;
    
    SDL_Quit();
}

void SDLApp::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                shutdown();
                break;
        }
    }
}

int SDLApp::update()
{
    if (!renderer || !window) return 0;
    
    handleEvents();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
    return 1;
}

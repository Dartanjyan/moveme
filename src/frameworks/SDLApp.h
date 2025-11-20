#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL2/SDL.h>
#include "IApplication.h"

class SDLApp : public IApplication {
public:
    SDLApp(const char *name, const int width, const int height);
    ~SDLApp();

    int initialize() override;
    void shutdown() override;
    int update() override;
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    const char *name;
    const int width, height;

    void handleEvents();
};

#endif
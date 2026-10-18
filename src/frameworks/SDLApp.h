#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL2/SDL.h>
#include <memory>
#include "IApplication.h"
#include "Vector2.h"

class SDLApp : public IApplication {
public:
    SDLApp(const char *name);
    ~SDLApp();

    int initialize(unsigned width, unsigned height) override;
    void shutdown() override;
    void render(const WorldSnapshot& s) override;
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    const char *name;
    unsigned _width, _height;
    
    Vector2 mousePos;
    bool mouseClicked;
    int frameCounter;

    void handleEvents();
};

#endif
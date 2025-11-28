#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL2/SDL.h>
#include <memory>
#include "IApplication.h"
#include "Vector2.h"
#include "GameState.h"

class SDLApp : public IApplication {
public:
    SDLApp(const char *name);
    ~SDLApp();

    int initialize(unsigned width, unsigned height, const GameState *gameState) override;
    void shutdown() override;
    int update() override;
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    const char *name;
    unsigned _width, _height;
    
    Vector2 mousePos;
    bool mouseClicked;
    int frameCounter;
    const GameState *gameState;

    void handleEvents();
    void render();
};

#endif
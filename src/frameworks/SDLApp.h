#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL2/SDL.h>
#include <memory>
#include "IApplication.h"
#include "Limb.h"

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
    
    std::unique_ptr<Limb> tentacle;
    Vector2 mousePos;
    bool mouseClicked;
    int frameCounter;

    void handleEvents();
    void render();
    void createTentacle();
};

#endif
#include "SDLApp.h"
#include <iostream>

SDLApp::SDLApp(const char *name, const int width, const int height)
    : name(name), width(width), height(height), mouseClicked(false)
{
    
}

SDLApp::~SDLApp()
{

}

void SDLApp::createTentacle() {
    const int segmentCount = 3;
    const float segmentLength = 40.0f;
    Vector2 basePosition(width / 2.0f, height / 2.0f);
    
    std::vector<BodyPart*> bodyParts;
    std::vector<Constraint*> constraints;
    
    for (int i = 0; i < segmentCount; i++) {
        Vector2 p1 = basePosition + Vector2(0, i * segmentLength);
        Vector2 p2 = basePosition + Vector2(0, (i + 1) * segmentLength);
        bodyParts.push_back(new BodyPart(nullptr, p1, p2));
        
        if (i > 0) {
            constraints.push_back(new Constraint(bodyParts[i-1], bodyParts[i]));
        }
    }
    
    tentacle = std::make_unique<Limb>(bodyParts, constraints);
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

    createTentacle();
    return 0;
}

void SDLApp::shutdown()
{
    tentacle.reset();
    
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
            case SDL_MOUSEMOTION:
                mousePos.x = event.motion.x;
                mousePos.y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseClicked = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseClicked = false;
                }
                break;
        }
    }
}

void SDLApp::render() {
    if (!tentacle) return;
    
    // Рисуем сегменты щупальца
    SDL_SetRenderDrawColor(renderer, 100, 200, 100, 255);
    
    for (auto* part : tentacle->getBodyParts()) {
        Vector2 p1 = part->getPoint1();
        Vector2 p2 = part->getPoint2();
        
        SDL_RenderDrawLine(renderer, 
            static_cast<int>(p1.x), static_cast<int>(p1.y),
            static_cast<int>(p2.x), static_cast<int>(p2.y));
        
        // Рисуем точки соединения
        SDL_Rect rect1 = {static_cast<int>(p1.x - 3), static_cast<int>(p1.y - 3), 6, 6};
        SDL_Rect rect2 = {static_cast<int>(p2.x - 3), static_cast<int>(p2.y - 3), 6, 6};
        SDL_RenderFillRect(renderer, &rect1);
        SDL_RenderFillRect(renderer, &rect2);
    }
    
    // Рисуем курсор
    if (mouseClicked) {
        SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
        SDL_Rect cursorRect = {
            static_cast<int>(mousePos.x - 5), 
            static_cast<int>(mousePos.y - 5), 
            10, 10
        };
        SDL_RenderFillRect(renderer, &cursorRect);
    }
}

int SDLApp::update()
{
    if (!renderer || !window) return 0;
    
    handleEvents();
    
    // Обновляем FABRIK если кнопка мыши нажата
    if (mouseClicked && tentacle) {
        tentacle->reachTowards(mousePos, 5);
    }

    SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
    SDL_RenderClear(renderer);

    render();

    SDL_RenderPresent(renderer);
    return 1;
}
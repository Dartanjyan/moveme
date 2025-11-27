#include "SDLApp.h"
#include <iostream>

// Интерполяция Catmull-Rom для плавной кривой
Vector2 catmullRomInterpolate(const Vector2& p0, const Vector2& p1, 
                               const Vector2& p2, const Vector2& p3, float t) {
    float t2 = t * t;
    float t3 = t2 * t;
    
    float x = 0.5f * ((2.0f * p1.x) +
                      (-p0.x + p2.x) * t +
                      (2.0f * p0.x - 5.0f * p1.x + 4.0f * p2.x - p3.x) * t2 +
                      (-p0.x + 3.0f * p1.x - 3.0f * p2.x + p3.x) * t3);
    
    float y = 0.5f * ((2.0f * p1.y) +
                      (-p0.y + p2.y) * t +
                      (2.0f * p0.y - 5.0f * p1.y + 4.0f * p2.y - p3.y) * t2 +
                      (-p0.y + 3.0f * p1.y - 3.0f * p2.y + p3.y) * t3);
    
    return Vector2(x, y);
}

// Основная функция для рисования плавной кривой
void drawSmoothCurve(SDL_Renderer* renderer, const std::vector<Vector2>& points, 
                     int segmentsPerPoint = 10) {
    if (points.size() < 2) return;
    
    // Если только 2 точки, рисуем прямую линию
    if (points.size() == 2) {
        SDL_RenderDrawLine(renderer,
            static_cast<int>(points[0].x), static_cast<int>(points[0].y),
            static_cast<int>(points[1].x), static_cast<int>(points[1].y));
        return;
    }
    
    // Для Catmull-Rom нужны контрольные точки до и после
    std::vector<Vector2> controlPoints;
    
    // Добавляем дублированную первую точку для начала
    controlPoints.push_back(points[0]);
    
    // Добавляем все точки
    for (const auto& p : points) {
        controlPoints.push_back(p);
    }
    
    // Добавляем дублированную последнюю точку для конца
    controlPoints.push_back(points.back());
    
    // Рисуем сегменты кривой
    for (size_t i = 0; i < controlPoints.size() - 3; i++) {
        Vector2 p0 = controlPoints[i];
        Vector2 p1 = controlPoints[i + 1];
        Vector2 p2 = controlPoints[i + 2];
        Vector2 p3 = controlPoints[i + 3];
        
        Vector2 prevPoint = p1;
        
        for (int seg = 1; seg <= segmentsPerPoint; seg++) {
            float t = static_cast<float>(seg) / segmentsPerPoint;
            Vector2 currentPoint = catmullRomInterpolate(p0, p1, p2, p3, t);
            
            SDL_RenderDrawLine(renderer,
                static_cast<int>(prevPoint.x), static_cast<int>(prevPoint.y),
                static_cast<int>(currentPoint.x), static_cast<int>(currentPoint.y));
            
            prevPoint = currentPoint;
        }
    }
}

// Альтернативная версия с толщиной линии (рисует несколько параллельных кривых)
void drawThickCurve(SDL_Renderer* renderer, const std::vector<Vector2>& points, 
                    int thickness = 3, int segmentsPerPoint = 10) {
    if (points.size() < 2) return;
    
    // Рисуем несколько кривых со смещением для создания эффекта толщины
    for (int offset = -thickness/2; offset <= thickness/2; offset++) {
        std::vector<Vector2> offsetPoints;
        
        for (size_t i = 0; i < points.size(); i++) {
            // Вычисляем перпендикулярное направление для смещения
            Vector2 perpendicular;
            
            if (i == 0 && points.size() > 1) {
                Vector2 dir = (points[1] - points[0]).normalized();
                perpendicular = Vector2(-dir.y, dir.x);
            } else if (i == points.size() - 1) {
                Vector2 dir = (points[i] - points[i-1]).normalized();
                perpendicular = Vector2(-dir.y, dir.x);
            } else {
                Vector2 dir = (points[i+1] - points[i-1]).normalized();
                perpendicular = Vector2(-dir.y, dir.x);
            }
            
            offsetPoints.push_back(points[i] + perpendicular * static_cast<float>(offset));
        }
        
        drawSmoothCurve(renderer, offsetPoints, segmentsPerPoint);
    }
}

// Простая версия с градиентом толщины (от толстого к тонкому)
void drawTaperedCurve(SDL_Renderer* renderer, const std::vector<Vector2>& points,
                      int startThickness = 5, int endThickness = 1, int segmentsPerPoint = 10) {
    if (points.size() < 2) return;
    
    std::vector<Vector2> controlPoints;
    controlPoints.push_back(points[0]);
    for (const auto& p : points) {
        controlPoints.push_back(p);
    }
    controlPoints.push_back(points.back());
    
    for (size_t i = 0; i < controlPoints.size() - 3; i++) {
        Vector2 p0 = controlPoints[i];
        Vector2 p1 = controlPoints[i + 1];
        Vector2 p2 = controlPoints[i + 2];
        Vector2 p3 = controlPoints[i + 3];
        
        for (int seg = 0; seg < segmentsPerPoint; seg++) {
            float t1 = static_cast<float>(seg) / segmentsPerPoint;
            float t2 = static_cast<float>(seg + 1) / segmentsPerPoint;
            
            Vector2 point1 = catmullRomInterpolate(p0, p1, p2, p3, t1);
            Vector2 point2 = catmullRomInterpolate(p0, p1, p2, p3, t2);
            
            // Вычисляем прогресс по всей кривой
            float progress = (i + t1) / (controlPoints.size() - 3);
            int thickness = startThickness + 
                          static_cast<int>((endThickness - startThickness) * progress);
            
            // Рисуем линию с текущей толщиной
            Vector2 dir = (point2 - point1).normalized();
            Vector2 perp = Vector2(-dir.y, dir.x);
            
            for (int offset = -thickness/2; offset <= thickness/2; offset++) {
                Vector2 offset1 = point1 + perp * static_cast<float>(offset);
                Vector2 offset2 = point2 + perp * static_cast<float>(offset);
                
                SDL_RenderDrawLine(renderer,
                    static_cast<int>(offset1.x), static_cast<int>(offset1.y),
                    static_cast<int>(offset2.x), static_cast<int>(offset2.y));
            }
        }
    }
}

SDLApp::SDLApp(const char *name, const int width, const int height)
    : name(name), width(width), height(height), mouseClicked(false), frameCounter(0)
{
    
}

SDLApp::~SDLApp()
{

}

void SDLApp::createTentacle() {
    const int segmentCount = 40;
    const float segmentLength = 5.0f;
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
    
    std::vector<Vector2> points;
    for (auto* part : tentacle->getBodyParts()) {
        points.push_back(part->getPoint1());
    }
    if (!tentacle->getBodyParts().empty()) {
        points.push_back(tentacle->getBodyParts().back()->getPoint2());
    }
    SDL_SetRenderDrawColor(renderer, 100, 200, 100, 255);
    drawTaperedCurve(renderer, points, 8, 2, 15);
}

int SDLApp::update()
{
    if (!renderer || !window) return 0;
    
    handleEvents();
    
    // // Обновляем FABRIK если кнопка мыши нажата
    // if (mouseClicked && tentacle) {
    //     tentacle->reachTowards(mousePos, 5);
    // }

    if (tentacle) {
        float x = std::cos((float)(frameCounter%120)/120*M_PI*2) * 100 + width/2;
        float y = std::sin((float)(frameCounter%120)/120*M_PI*6) * 50 + height/2;
        tentacle->reachTowards({x, y}, 5);
    }

    SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
    SDL_RenderClear(renderer);

    render();

    SDL_RenderPresent(renderer);

    frameCounter++;
    return 1;
}
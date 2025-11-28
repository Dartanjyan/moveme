#include "ApplicationManager.h"
#include <chrono>
#include <thread>

ApplicationManager::ApplicationManager(std::unique_ptr<IApplication> app)
    : app(std::move(app)), updateInterval(std::chrono::milliseconds(16)), tickCounter(0)
{
    this->app->initialize(width, height, &gameState);
    
    gameState = GameState();

    // Create tentacle
    // TODO: Move to another function later
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
    
    gameState.tentacle = new Limb(bodyParts, constraints);
}

ApplicationManager::~ApplicationManager()
{
    app->shutdown();

    delete gameState.tentacle;
    gameState.tentacle = nullptr;
}

int ApplicationManager::gameTick()
{
    Limb *tentacle = gameState.tentacle;
    if (tentacle) {
        float x = std::cos((float)(tickCounter%120)/120*M_PI*2) * 100 + width/2;
        float y = std::sin((float)(tickCounter%120)/120*M_PI*6) * 50 + height/2;
        tentacle->reachTowards({x, y}, 5);
    }

    return 1;
}

int ApplicationManager::run()
{
    using namespace std::chrono;
    auto previous_time = high_resolution_clock::now();
    system_clock::time_point current_time;
    nanoseconds elapsed_time;
    
    int running = 1;
    while (running == 1) {
        current_time = high_resolution_clock::now();
        elapsed_time = current_time - previous_time;
        previous_time = current_time;

        // Code
        running &= app->update() == 1;
        running &= this->gameTick() == 1;
        
        const auto processing_time = duration_cast<milliseconds>(
            high_resolution_clock::now() - current_time
        );
        const auto sleep_time = this->updateInterval - processing_time;
        // std::cout << sleep_time.count() << " ms" << std::endl;
        if (sleep_time > 0ms) {
            std::this_thread::sleep_for(sleep_time);
        }
        tickCounter++;
    }

    return 0;
}


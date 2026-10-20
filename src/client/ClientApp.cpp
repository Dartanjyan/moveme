#include "ClientApp.h"
#include "Creature.h"
#include <chrono>
#include <thread>
#include <variant>

ClientApp::ClientApp(std::unique_ptr<IApplication> app)
    : app(std::move(app)), updateInterval(std::chrono::milliseconds(16)), tickCounter(0)
{
    if (this->app->initialize(width, height) != 0) {
        std::cerr << "ClientApp: could not initialize Application, stopping" << std::endl;
        return;
    }

    // Create tentacle
    // TODO: Move to another function later
    const int segmentCount = 3;
    const float segmentLength = 5.0f*10;
    Vector2 basePosition(width / 2.0f, height / 2.0f);
    
    std::vector<std::shared_ptr<BodyPart>> bodyParts;
    std::vector<std::shared_ptr<Constraint>> constraints;
    
    for (int i = 0; i < segmentCount; i++) {
        Vector2 p1 = basePosition + Vector2(0, i * segmentLength);
        Vector2 p2 = basePosition + Vector2(0, (i + 1) * segmentLength);
        bodyParts.push_back(std::move(std::make_shared<BodyPart>(nullptr, p1, p2)));
        if (i > 0) {
            constraints.push_back(std::move(std::make_shared<Constraint>(bodyParts[i-1], bodyParts[i])));
        }
    }

    initialized = true;
}

ClientApp::~ClientApp()
{
    app->shutdown();
}

int ClientApp::run()
{
    if (!initialized)
        return 1;
    
    using namespace std::chrono;
    auto previous_time = steady_clock::now();
    system_clock::time_point current_time;
    nanoseconds elapsed_time;
    
    // int running = 1;
    // while (running == 1) {
    //     current_time = steady_clock::now();
    //     elapsed_time = current_time - previous_time;
    //     previous_time = current_time;

    //     // Code
    //     // Call render
    //     // TODO: move render to separate thread
    //     running &= app->update() == 1;
    //     // Call game tick
    //     running &= this->gameTick() == 1;
        
    //     const auto processing_time = duration_cast<milliseconds>(
    //         steady_clock::now() - current_time
    //     );
    //     const auto sleep_time = this->updateInterval - processing_time;
    //     // std::cout << sleep_time.count() << " ms" << std::endl;
    //     if (sleep_time > 0ms) {
    //         std::this_thread::sleep_for(sleep_time);
    //     }
    //     tickCounter++;
    // }

    // while (app->pollInput(input)) {
    //     conn->send(InputMsg{input.mousePos, input.mouseDown});
    //     while (auto m = conn->poll())
    //         if (auto* s = std::get_if<SnapshotMsg>(&*m)) latest = std::move(s->world);
    //     app->render(latest);
    //     // ~60 FPS
    // }


    return 0;
}


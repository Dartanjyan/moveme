#include "ApplicationManager.h"
#include <chrono>
#include <thread>

ApplicationManager::ApplicationManager(std::unique_ptr<IApplication> app)
    : app(std::move(app)), updateInterval(std::chrono::milliseconds(16))
{
    this->app->initialize();
}

ApplicationManager::~ApplicationManager()
{
    app->shutdown();
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
        running = app->update();

        const auto processing_time = duration_cast<milliseconds>(
            high_resolution_clock::now() - current_time
        );
        const auto sleep_time = this->updateInterval - processing_time;
        // std::cout << sleep_time.count() << " ms" << std::endl;
        if (sleep_time > 0ms) {
            std::this_thread::sleep_for(sleep_time);
        }
    }

    return 0;
}

cmake_minimum_required(VERSION 3.16)
project(moveme LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(Threads REQUIRED)

# Ядро: симуляция, протокол. SDL здесь нет
file(GLOB_RECURSE CORE_SRC CONFIGURE_DEPENDS
    src/entities/*.cpp src/dto/*.cpp src/use_cases/*.cpp src/interfaces/*.cpp)
add_library(moveme_core STATIC ${CORE_SRC})
target_include_directories(moveme_core PUBLIC
    src src/dto src/entities src/use_cases src/interfaces)
target_link_libraries(moveme_core PUBLIC Threads::Threads)

# Клиент
file(GLOB_RECURSE CLIENT_SRC CONFIGURE_DEPENDS src/client/*.cpp src/frameworks/*.cpp)
add_executable(moveme ${CLIENT_SRC})
target_include_directories(moveme PRIVATE src/client src/frameworks ${SDL2_INCLUDE_DIRS})
target_link_libraries(moveme PRIVATE moveme_core ${SDL2_LIBRARIES})

# Сервер: без SDL
file(GLOB_RECURSE SERVER_SRC CONFIGURE_DEPENDS src/server/*.cpp)
add_executable(moveme_server ${SERVER_SRC})
target_include_directories(moveme_server PRIVATE src/server)
target_link_libraries(moveme_server PRIVATE moveme_core)
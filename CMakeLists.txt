cmake_minimum_required(VERSION 3.16)
project(moveme LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)
# find_package(SDL2_ttf REQUIRED)

include_directories(
    "src"
    "src/dto"
    "src/entities"
    "src/use_cases"
    "src/interfaces"
    "src/frameworks"
    ${SDL2_INCLUDE_DIRS}
    # ${SDL2_IMAGE_INCLUDE_DIRS}
    # ${SDL2_TTF_INCLUDE_DIRS}
)

file(GLOB_RECURSE SRC src/*.cpp src/*.h)

add_executable(moveme ${SRC})

target_link_libraries(moveme
    ${SDL2_LIBRARIES}
    # ${SDL2_IMAGE_LIBRARIES}
    # ${SDL2_TTF_LIBRARIES}
)

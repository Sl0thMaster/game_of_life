include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

cmake_minimum_required(VERSION 3.26)
project(game_of_life)

set(CMAKE_CXX_STANDARD 17)

add_executable(game_of_life main.cpp)

FetchContent_Declare(
        sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML"
        GIT_TAG 2.6.0
)
set(SFML_BUILD_AUDIO FALSE)
set(SFML_BUILD_NETWORK FALSE)
FetchContent_MakeAvailable(sfml)

target_link_libraries(game_of_life PUBLIC sfml-graphics)
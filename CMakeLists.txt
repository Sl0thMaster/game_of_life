include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
enable_testing()

cmake_minimum_required(VERSION 3.26)
project(game_of_life)

set(CMAKE_CXX_STANDARD 17)

add_executable(game_of_life main.cpp
        field.h
        field.cpp)

add_library(field field.h field.cpp)

add_executable(field_test test.cpp)
target_link_libraries(field_test PRIVATE field)
add_test(NAME field_test COMMAND field_test)

FetchContent_Declare(
        sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML"
        GIT_TAG 2.6.0
)
set(SFML_BUILD_AUDIO FALSE)
set(SFML_BUILD_NETWORK FALSE)
FetchContent_MakeAvailable(sfml)

target_link_libraries(game_of_life PUBLIC sfml-graphics)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/saves DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/slkscr.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

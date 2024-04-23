include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
enable_testing()

cmake_minimum_required(VERSION 3.26)
project(game_of_life)

set(CMAKE_CXX_STANDARD 17)

add_library(field field.h field.cpp)
add_executable(game_of_life main.cpp)
target_link_libraries(game_of_life PRIVATE field)

add_executable(field_test test.cpp)
target_link_libraries(field_test PRIVATE field)
add_test(NAME field_test COMMAND field_test)

find_package(Doxygen)

set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_RTF YES)
set(DOXYGEN_USE_MATHJAX YES)
set(DOXYGEN_EXTRACT_PRIVATE YES)
set(DOXYGEN_OUTPUT_LANGUAGE Russian)

doxygen_add_docs(
        doc ALL
        ${PROJECT_SOURCE_DIR}/field.h
        COMMENT "Generate HTML documentation"
)

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

set(CMAKE_INSTALL_DOCDIR ${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME})
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html/
        DESTINATION ${CMAKE_INSTALL_DOCDIR})
install(TARGETS game_of_life
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
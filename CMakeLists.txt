cmake_minimum_required(VERSION 3.6)
project(simple-sfml-cmake-example)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(simple-sfml-cmake-example src/main.cpp src/main.cpp)

target_compile_features(simple-sfml-cmake-example
        PRIVATE
        cxx_std_17)

target_link_libraries(simple-sfml-cmake-example
        sfml-graphics
        sfml-window
        sfml-network
        sfml-system)
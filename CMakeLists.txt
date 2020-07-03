cmake_minimum_required(VERSION 3.16)
project(imgui_template)

set(CMAKE_CXX_STANDARD 14)
ADD_LIBRARY(LibsModule
        main.cpp
        lib/imgui_impl_sdl.cpp
        lib/imgui_impl_opengl2.cpp
        lib/imgui.cpp
        lib/imgui_draw.cpp
        lib/imgui_widgets.cpp
        lib/imgui_demo.cpp
)

target_link_libraries(LibsModule -lSDL2 -lGL -ldl)

add_executable(imgui_template main.cpp)

target_link_libraries(imgui_template LibsModule)
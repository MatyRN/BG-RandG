#ifndef LIBSANDVARIABLES_H
#define LIBSANDVARIABLES_H
#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
#endif
#define SDL_MAIN_HANDLED
#include <limits.h>
#include <windows.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL_syswm.h>
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl2.h"

// ========= FUCTIONS ========= //
void Init_WIN_and_GLEW();
void Loop_OpenGL();

    // ========= VARIABLE ======= //
    struct Colour {
        float r, g, b, a;
    };

    struct Vec3 {
        float x, y, z;
    };

    extern bool Reset;
    extern bool Running;
    extern const int WIDTH[];
    extern const int HEIGHT[];

#endif

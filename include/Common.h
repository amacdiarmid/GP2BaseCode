#ifndef _COMMON_H
#define _COMMON_H

#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>

#ifdef __APPLE__
#include <Opengl/glu.h>
#elif (_WIN64 || _WIN32)
#include <gl\GLU.h>
#endif

#endif

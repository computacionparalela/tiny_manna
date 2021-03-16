#pragma once

#include <ctime>

// number of sites
#ifndef N
#define N 32768
#endif

// number of sites
#ifndef DENSITY
#define DENSITY 0.8924
#endif

// number of temporal steps
#ifndef NSTEPS
#define NSTEPS 1000000
#endif

#ifndef SEED
#define SEED time(nullptr)
#endif

// graphics options
#ifdef GRAPHICS

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 256
#endif

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 256
#endif

#ifndef BAND_HEIGHT
#define BAND_HEIGHT 8
#endif

#ifndef TARGET_FPS
#define TARGET_FPS 30
#endif

#endif /* GRAPHICS */

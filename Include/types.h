#ifndef TYPES_H
#define TYPES_H

#include <SFML/Graphics.hpp>

// #define DisableGraphics

#define Niter 4
#define FORiter \
    for(int i = 0; i < Niter; i++)

typedef struct Settings{
    sf::Uint8* pixels;
    sf::RenderWindow* window;
    float x0;
    float y0;
    float scale;
    float dx;
    float dy;
    int Nmax;
    float Rmax;
    float* Rmax2;
    int mode;
} Settings;

const int width = 800, height = 600;

#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SFML/Graphics.hpp>
#include "types.h"
#include "draw_picture.h"

void CheckEvent (Settings* sets) {
    sf::Event event;

    while (sets->window->pollEvent(event)) {

        switch (event.type) {

            case sf::Event::Closed:
                sets->window->close();
                break;

            case sf::Event::KeyPressed:
                if(ChangeSets(sets, event.key))
                    sets->window->close();
                break;

            default:
                break;
            }
        
    }
}

int ChangeSets (Settings* sets, sf::Event::KeyEvent key) { 

    switch (key.code) {
        case sf::Keyboard::Escape :
            return 1;
            break;
        
        case sf::Keyboard::Left :
            sets->x0 -= 0.1f * sets->scale * ( (key.shift)? 10: 1 );
            break;
        
        case sf::Keyboard::Right :
            sets->x0 += 0.1f * sets->scale * ( (key.shift)? 10: 1 );
            break;
        
        case sf::Keyboard::Up :
            sets->y0 -= 0.1f * sets->scale * ( (key.shift)? 10: 1 );
            break;
        
        case sf::Keyboard::Down :
            sets->y0 += 0.1f * sets->scale * ( (key.shift)? 10: 1 );
            break;
        
        case sf::Keyboard::Equal :
        case sf::Keyboard::Add :
            sets->scale *= 0.9f * ( (key.shift)? 0.81: 1 );
            break;
        
        case sf::Keyboard::Subtract :
        case sf::Keyboard::Hyphen :
            sets->scale /= 0.9f * ( (key.shift)? 0.81: 1 );
            break;
        
        case sf::Keyboard::Num0 :
            sets->mode = 0;
            break;
        
        case sf::Keyboard::Num1 :
            sets->mode = 1;
            break;
        
        case sf::Keyboard::Num2 :
            sets->mode = 2;
            break;
        
        case sf::Keyboard::Num3 :
            sets->mode = 3;
            break;

        default:
            break;
    }

    return 0;
}

void ChangePixelColor (Settings* sets, int x, int y, char r, char g, char b) {
    sets->pixels[(y * width + x) * 4] = r;
    sets->pixels[(y * width + x) * 4 + 1] = g;
    sets->pixels[(y * width + x) * 4 + 2] = b;
    sets->pixels[(y * width + x) * 4 + 3] = 255;
}

void ChangePixel (Settings* sets, int n, int x, int y) {

    if(n == sets->Nmax)
        ChangePixelColor(sets, x, y, 0, 0, 0);
    else
        ChangePixelColor(sets, x, y, (char)(255 - (int)(sqrtf(1 - (float)n/sets->Nmax) * 10000.f)%200), \
            (char)(200 - (int)(sqrtf(sqrtf(1 - (float)n/sets->Nmax)) * 10000.f)%200), 200);
}






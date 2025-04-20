#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <x86intrin.h>
#include <SFML/Graphics.hpp>

#include "types.h"
#include "main_0.h"
#include "main_1.h"
#include "main_2.h"
#include "main_3.h"
#include "draw_picture.h"


int main() {
    
    // x = [-2, 1] y = [-1.25, 1.25]
    float x0 = -0.5f, y0 = 0.f;
    float scale = 1.f;
    float dx = 3 / 800.f, dy = 2.5f / 600.f;
    int Nmax = 256;
    float Rmax = 10, Rmax2[4] = {Rmax*Rmax, Rmax*Rmax, Rmax*Rmax, Rmax*Rmax};


    sf::Uint8* pixels = (sf::Uint8*)malloc(width * height * 4);
    sf::RenderWindow window (sf::VideoMode(width, height), "Mandelbrot");
    sf::Texture texture;
    texture.create(width, height);

    
    Settings sets = {pixels, &window, x0, y0, scale, dx, dy, Nmax, Rmax, Rmax2, 0};
    
    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    unsigned long long time0 = __rdtsc();
    int cnt_frame = 0;
    unsigned long long ticks = 0;
    unsigned long long ticks_average = 0;
    
    window.setKeyRepeatEnabled(false);

    while (window.isOpen()) {

        CheckEvent(&sets);

        switch (sets.mode) {
            case 0:
                mode_0(&sets);
                break;

            case 1:
                mode_1(&sets);
                break;
            
            case 2:
                mode_2(&sets);
                break;

            case 3:
                mode_3(&sets);
                break;
        }

        #ifndef DisableGraphics
            texture.update(sets.pixels);
            window.clear();
            sf::Sprite sprite(texture);
            window.draw(sprite);
            window.display();
        #endif

        sf::Time currentTime = clock.getElapsedTime();
        float fpsSFML = 1.f / (currentTime.asSeconds() - previousTime.asSeconds());

        unsigned long long time_now = __rdtsc();
        ticks += time_now - time0;
        time0 = time_now;

        cnt_frame++;
        if(cnt_frame == 256) {
            ticks_average = ticks >> 8;
            cnt_frame = 0;
            ticks = 0;
        }

        // float fpsRDTSC = (time0 - time_now);
        // if(cnt_frame % 256 == 0) {
            system("clear");
            printf("mode: %d\nfps_SFML: %.2lf\nticks_RDTSC: %Lu\n", sets.mode, fpsSFML, ticks_average);
        // }
        previousTime = currentTime;
    }

    return 0;
}









#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SFML/Graphics.hpp>
#include "types.h"
#include "main_0.h"
#include "draw_picture.h"

void mode_0 (Settings* sets) {

    for(int Ypt = 0; Ypt < 600; Ypt++) {

        float Y = sets->y0 + (float)(Ypt - 300) * sets->dy * sets->scale;

        for(int Xpt = 0; Xpt < 800; Xpt++) {

            float X = sets->x0 + (float)(Xpt - 400) * sets->dx * sets->scale;
            int n = 0;
            float x = X, y = Y;

            while(n < sets->Nmax) {

                float xy = x*y; 

                float R2 = x*x + y*y;

                if (R2 > sets->Rmax2[0]) break; 
                n++;

                x = x*x - y*y + X;
                y = 2*xy + Y;
            }

            #ifndef DisableGraphics
                ChangePixel(sets, n, Xpt, Ypt);
            #endif
            
        }
    }
}
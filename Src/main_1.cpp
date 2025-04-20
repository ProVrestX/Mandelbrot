#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SFML/Graphics.hpp>
#include "types.h"
#include "main_1.h"
#include "draw_picture.h"

void mode_1(Settings* sets) {

    for(int Ypt = 0; Ypt < 600; Ypt++) {

        float Y[Niter] = {}; FORiter Y[i] = sets->y0 + (float)(Ypt - 300) * sets->dy * sets->scale;

        for(int Xpt = 0; Xpt < 800; Xpt+=Niter) { 

            float DX = sets->dx * sets->scale;
            float X[Niter] = {}; FORiter X[i] = sets->x0 + (float)(Xpt - 400 + i) * DX; 
            float x[Niter] = {}; FORiter x[i] = X[i]; 
            float y[Niter] = {}; FORiter y[i] = Y[i];

            int Ncnt[4] = {};
            int Rcmp[Niter] = {1,1,1,1};

            for(int n = 0; n < sets->Nmax; n++) {

                float xy[Niter] = {}; FORiter xy[i] = x[i]*y[i]; 
                float x2[Niter] = {}; FORiter x2[i] = x[i]*x[i]; 
                float y2[Niter] = {}; FORiter y2[i] = y[i]*y[i]; 

                // float Dx[Niter] = {}; FORiter Dx[i] = x[i] - X[i];
                // float Dy[Niter] = {}; FORiter Dy[i] = y[i] - Y[i];
                // float R2[Niter] = {}; FORiter R2[i] = Dx[i]*Dx[i] + Dy[i]*Dy[i];
                float R2[Niter] = {}; FORiter R2[i] = (x2[i] + y2[i]);
                
                FORiter if(R2[i] > sets->Rmax2[i]) Rcmp[i] = 0; 

                int mask = 0; 
                FORiter mask |= (Rcmp[i] << i);
                if (!mask) break; 

                FORiter Ncnt[i] += Rcmp[i];

                FORiter x[i] = (x2[i] - y2[i] + X[i]); 
                FORiter y[i] = (2*xy[i] + Y[i]);

                FORiter if(!Rcmp[i]) {x[i] = sets->Rmax; y[i] = sets->Rmax;}

            }

            #ifndef DisableGraphics
                FORiter ChangePixel(sets, Ncnt[i], Xpt + i, Ypt);
            #endif
            
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SFML/Graphics.hpp>
#include "types.h"
#include "main_2.h"
#include "draw_picture.h"

inline void mm_set_ps (float mm[Niter], float val0, float val1, float val2, float val3) {
    mm[0] = val0; mm[1] = val1; mm[2] = val2; mm[3] = val3; }
inline void mm_set_ps1 (float mm[Niter], float val) {
    FORiter mm[i] = val; }
inline void mm_cpy_ps (float mm[Niter], const float mm1[Niter]) {
    FORiter mm[i] = mm1[i]; }

inline void mm_add_ps (float mm[Niter], const float mm1[Niter], const float mm2[Niter]) {
    FORiter mm[i] = mm1[i] + mm2[i]; }
inline void mm_add_epi32 (int mm[Niter], const int mm1[Niter], const float mm2[Niter]) {
    FORiter mm[i] = mm1[i] + (int)mm2[i]; }
inline void mm_sub_ps (float mm[Niter], const float mm1[Niter], const float mm2[Niter]) {
    FORiter mm[i] = mm1[i] - mm2[i]; }
inline void mm_mul_ps (float mm[Niter], const float mm1[Niter], const float mm2[Niter]) {
    FORiter mm[i] = mm1[i] * mm2[i]; }

inline void mm_cmplt_ps (float cmp[Niter], const float mm1[Niter], const float mm2[Niter]) {
    FORiter cmp[i] = (mm1[i] < mm2[i])? 1: 0; }
inline int mm_movemask_ps (const float cmp[Niter]) {
    int mask = 0;
    FORiter mask |= (!!(int)cmp[i] << i);
    return mask;
}

void mode_2(Settings* sets) {
    for(int Ypt = 0; Ypt < 600; Ypt++) {

        float Y[Niter] = {}; mm_set_ps1(Y, sets->y0 + (float)(Ypt - 300) * sets->dy * sets->scale);

        for(int Xpt = 0; Xpt < 800; Xpt+=Niter) { 
            
            float DX = sets->dx * sets->scale;
            float X[Niter] = {}; mm_set_ps(X, sets->x0 + (float)(Xpt - 400) * DX, \
                sets->x0 + (float)(Xpt - 400 + 1) * DX, \
                sets->x0 + (float)(Xpt - 400 + 2) * DX,\
                sets->x0 + (float)(Xpt - 400 + 3) * DX); 
            float x[Niter] = {}; mm_cpy_ps(x, X); 
            float y[Niter] = {}; mm_cpy_ps(y, Y);

            int Ncnt[4] = {};

            for(int n = 0; n < sets->Nmax; n++) {

                float xy[Niter] = {}; mm_mul_ps(xy, x, y); 
                float x2[Niter] = {}; mm_mul_ps(x2, x, x);  
                float y2[Niter] = {}; mm_mul_ps(y2, y, y); 

                float R2[Niter] = {}; mm_add_ps(R2, x2, y2);
                
                float Rcmp[Niter] = {};
                mm_cmplt_ps(Rcmp, R2, sets->Rmax2);

                int mask = mm_movemask_ps(Rcmp);
                if (!mask) break; 

                mm_add_epi32(Ncnt, Ncnt, Rcmp);

                mm_sub_ps(x, x2, y2); mm_add_ps(x, x, X);
                mm_add_ps(y, xy, xy); mm_add_ps(y, y, Y); 

                FORiter if(!(int)Rcmp[i]) {x[i] = sets->Rmax; y[i] = sets->Rmax;}
            }

            #ifndef DisableGraphics
                FORiter ChangePixel(sets, Ncnt[i], Xpt + i, Ypt);
            #endif
            
        }
    }
}
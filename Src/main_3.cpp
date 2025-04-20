#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <immintrin.h>
#include "types.h"
#include "main_3.h"
#include "draw_picture.h"

void mode_3(Settings* sets) {
    
    __m256d nul = _mm256_set1_pd((double) 0);
    __m256d Rmax2 = _mm256_set1_pd((double) sets->Rmax2[0]);

    for(int Ypt = 0; Ypt < 600; Ypt++) {

        __m256d Y = _mm256_set1_pd((double) sets->y0 + (float)(Ypt - 300) * sets->dy * sets->scale);

        for(int Xpt = 0; Xpt < 800; Xpt+=Niter) { 
            
            
            float DX = sets->dx * sets->scale;
            __m256d X = _mm256_set_pd((double) sets->x0 + (float)(Xpt - 400) * DX, \
                (double) sets->x0 + (float)(Xpt - 400 + 1) * DX, \
                (double) sets->x0 + (float)(Xpt - 400 + 2) * DX,\
                (double) sets->x0 + (float)(Xpt - 400 + 3) * DX); 
            __m256d x = _mm256_add_pd(X, nul); 
            __m256d y = _mm256_add_pd(Y, nul);

            __m256i Ncnt = {};

            for(int n = 0; n < sets->Nmax; n++) {

                __m256d xy = _mm256_mul_pd(x, y); 
                __m256d x2 = _mm256_mul_pd(x, x); 
                __m256d y2 = _mm256_mul_pd(y, y);

                __m256d R2 = _mm256_add_pd(x2, y2);
                
                __m256d Rcmp = _mm256_cmp_pd(R2, Rmax2, _CMP_LE_OS);

                int mask = _mm256_movemask_pd(Rcmp);
                if (!mask) break; 

                Ncnt = _mm256_sub_epi64(Ncnt, _mm256_castpd_si256(Rcmp));

                x = _mm256_sub_pd(x2, y2); x = _mm256_add_pd(x, X);
                y = _mm256_add_pd(xy, xy); y = _mm256_add_pd(y, Y); 

                // FORiter if(!((long long*)Rcmp)[i]) {x[i] = sets->Rmax; y[i] = sets->Rmax;}
            }
            
            #ifndef DisableGraphics
                ChangePixel(sets, _mm256_extract_epi64(Ncnt, 0), Xpt + 3, Ypt);
                ChangePixel(sets, _mm256_extract_epi64(Ncnt, 1), Xpt + 2, Ypt);
                ChangePixel(sets, _mm256_extract_epi64(Ncnt, 2), Xpt + 1, Ypt);
                ChangePixel(sets, _mm256_extract_epi64(Ncnt, 3), Xpt, Ypt);
            #endif
        }
    }
}
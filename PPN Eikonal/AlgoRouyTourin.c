//
//  AlgoRouyTourin.c
//  PPN Eikonal
//
//  Created by Yohan on 11/12/2014.
//  Copyright (c) 2014 Yohan. All rights reserved.
//

#include "AlgoRouyTourin.h"
#include "Matrix.h"

//Structure représentant les différent fronts sources
//les coordonnées sont rangés par abscisses puis ordonnées
//A(x,y) -> x = data[i] , y = data[i+1]
typedef struct{
    unsigned _nb_point;
    unsigned *_data_x;
    unsigned *_data_y;
}Front;

void RT(Matrice* m,Front* f){
    for (unsigned i = 0; i<m->nb_row; i++) {
        for (unsigned j = 0; j<m->nb_col; j++) {
            set(m, i, j, INF);
        }
    }
    for (unsigned i = 0; f->_nb_point; i+=2) {
        set(m, f->_data_x[i], f->_data_y[i], 0.0);
    }
    
}

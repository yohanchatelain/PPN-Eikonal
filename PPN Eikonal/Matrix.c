//
//  Matrix.c
//  PPN Eikonal
//
//  Created by Yohan on 11/12/2014.
//  Copyright (c) 2014 Yohan. All rights reserved.
//

#include "Matrix.h"

unsigned ind(unsigned nb_col, unsigned i,unsigned j){
    return i*nb_col+j;
}

void print_matrice(Pnum *m, unsigned nb_row, unsigned nb_col){
    int i,j;
    for (i = 0; i<nb_row; i++) {
        for (j = 0; j<nb_col; j++) {
            printf("%f\t",m[ind(nb_col, i, j)]);
        }
        printf("\n");
    }
}

void copie(Pnum *source, Pnum *dest, unsigned nb_row, unsigned nb_col){
    int i,j;
    for (i=0; i<nb_row; i++) {
        for (j=0; j<nb_col; j++) {
            dest[ind(nb_col, i, j)] = source[ind(nb_col, i, j)];
        }
    }
}
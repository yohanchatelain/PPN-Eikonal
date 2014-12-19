//
//  Matrix.h
//  PPN Eikonal
//
//  Created by Yohan on 11/12/2014.
//  Copyright (c) 2014 Yohan. All rights reserved.
//

#ifndef __PPN_Eikonal__Matrix__
#define __PPN_Eikonal__Matrix__

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "typePrecision.h"

typedef struct{
    unsigned nb_row;
    unsigned nb_col;
    Pnum *data;

}Matrice;

Matrice* init(unsigned n,unsigned m,char *name_file_matrix);
void freeMatrice(Matrice *m);
Pnum get(Matrice *m,unsigned i,unsigned j);
void set(Matrice *m, unsigned i,unsigned j,Pnum value);

#endif /* defined(__PPN_Eikonal__Matrix__) */

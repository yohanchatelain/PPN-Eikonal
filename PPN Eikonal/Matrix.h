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

unsigned ind(unsigned nb_col, unsigned i, unsigned j);
void print_matrice(Pnum *m, unsigned nb_row, unsigned nb_col);
void copie(Pnum *source, Pnum *dest, unsigned nb_row, unsigned nb_col);
#endif /* defined(__PPN_Eikonal__Matrix__) */

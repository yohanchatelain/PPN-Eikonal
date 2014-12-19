//
//  Matrix.c
//  PPN Eikonal
//
//  Created by Yohan on 11/12/2014.
//  Copyright (c) 2014 Yohan. All rights reserved.
//

#include "Matrix.h"

//Initialise une matrice (n,m)
//Stockage en Row Major
Matrice* init(unsigned n,unsigned m,char *name_file_matrix){
    Matrice *mm = (Matrice*) malloc(sizeof(Matrice));
    mm->nb_row = n;
    mm->nb_col = m;
    mm->data = (Pnum*) malloc(sizeof(n*m*sizeof(Pnum)));
    return mm;
}

//Libère la mémoire
void freeMatrice(Matrice *m){
    free(m->data);
    free(m);
}

// getter
//Stockage en RowMajor
Pnum get(Matrice *m,unsigned i,unsigned j){
    return m->data[i*m->nb_col+j];
}

//setter
void set(Matrice *m, unsigned i,unsigned j,Pnum value){
    assert(i>=0 && i<m->nb_row);
    assert(j>=0 && j<m->nb_col);
    m->data[i*m->nb_col+j] = value;
}

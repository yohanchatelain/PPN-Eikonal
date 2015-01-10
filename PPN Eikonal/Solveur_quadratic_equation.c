//
//  Solveur_quadratic_equation.c
//  PPN Eikonal
//
//  Created by Yohan on 11/12/2014.
//  Copyright (c) 2014 Yohan. All rights reserved.
//

#include <math.h>
#include "Solveur_quadratic_equation.h"


int signe(Pnum b) {
    if (b>=0)
        return 1;
    else
        return -1;
}

//alpha = h/c
Pnum solveEquation_2(Pnum Tx, Pnum Ty, Pnum h, Pnum f){
    if (fabs(Tx-Ty) >= (2.0/3.0)*sqrtf(2.0)*h/f)
        return fminf(Tx, Ty) + h/f;
    else
        return (Tx+Ty+sqrtf((8.0/9.0)*h*h/(f*f)-(Tx-Ty)*(Tx-Ty)))/2.0;
}

Pnum solveEquation_1(Pnum Tx, Pnum Ty, Pnum h, Pnum f){
    if (fabs(Tx-Ty) >= sqrtf(2.0)*h/f)
        return fminf(Tx, Ty) + h/f;
    else
        return (Tx+Ty+sqrtf(2*h*h/(f*f)-(Tx-Ty)*(Tx-Ty)))/2.0;
}

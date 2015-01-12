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

Pnum solveEquation_1(Pnum Tx, Pnum Ty, Pnum h, Pnum f){
    if (fabs(Tx-Ty) >= sqrtf(2.0)*h/f)
        return fminf(Tx, Ty) + h/f;
    else
        return (Tx+Ty+sqrtf(2*h*h/(f*f)-(Tx-Ty)*(Tx-Ty)))/2.0;
}

Pnum solveEquation_2(Pnum Txm, Pnum Txp, Pnum Tym, Pnum Typ, Pnum h, Pnum f){
    Pnum a = (Txm + Txp + Tym + Typ)*9.0/(4.0*h*h),
    b = -2*a,
    c = (Txm*Txm + Txp*Txp + Tym*Tym + Typ*Typ)*9.0/(4.0*h*h) - 1/(f*f);
    
    Pnum delta = b*b - 4*a*c;
    if (delta < 0) return INF;
    return (-b+sqrtf(delta))/(2*a);
}
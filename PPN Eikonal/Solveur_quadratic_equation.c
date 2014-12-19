//
//  Solveur_quadratic_equation.c
//  PPN Eikonal
//
//  Created by Yohan on 11/12/2014.
//  Copyright (c) 2014 Yohan. All rights reserved.
//

#include <math.h>
#include "Solveur_quadratic_equation.h"

#define SIGN(x) (x>0)

Pnum solveEquation(Pnum Tx, Pnum Ty, Pnum a, Pnum b, Pnum c){
    Pnum delta = b*b - 4*a*c;
    if (delta<0) return INF;
    Pnum q = -0.5*(b+SIGN(b)*sqrtf(delta));
    return fmaxf(q/a, c/q);
}

//alpha = h/c
Pnum solveEquation_2(Pnum Tx, Pnum Ty, Pnum a, Pnum b, Pnum c, Pnum alpha){
    Pnum delta = b*b - 4*a*c;
    if (delta<0) return INF;
    Pnum q = -0.5*(b+SIGN(b)*sqrtf(delta));
    Pnum x_sol = fmaxf(q/a, c/q);
    if (Ty > x_sol && x_sol > Tx) return Tx + alpha;
    if (Tx > x_sol && x_sol > Ty) return Ty + alpha;
    // if (x_sol > fmaxf(Tx, Ty))
    return x_sol;
}

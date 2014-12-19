//
//  Solveur_quadratic_equation.h
//  PPN Eikonal
//
//  Created by Yohan on 11/12/2014.
//  Copyright (c) 2014 Yohan. All rights reserved.
//

#ifndef __PPN_Eikonal__Solveur_quadratic_equation__
#define __PPN_Eikonal__Solveur_quadratic_equation__

#include <stdio.h>
#include "typePrecision.h"

Pnum solveEquation(Pnum Tx, Pnum Ty,Pnum a, Pnum b, Pnum c);
Pnum solveEquation_2(Pnum Tx, Pnum Ty, Pnum a, Pnum b, Pnum c, Pnum alpha);

#endif /* defined(__PPN_Eikonal__Solveur_quadratic_equation__) */

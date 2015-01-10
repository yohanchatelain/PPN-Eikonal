//
//  AlgoRouyTourin.h
//  PPN Eikonal
//
//  Created by Yohan on 11/12/2014.
//  Copyright (c) 2014 Yohan. All rights reserved.
//

#ifndef __PPN_Eikonal__AlgoRouyTourin__
#define __PPN_Eikonal__AlgoRouyTourin__

#include <stdio.h>
#include "Matrix.h"
#include "Solveur_quadratic_equation.h"

typedef enum{
    Gaussienne, Cercle
}Fonction;

unsigned nb_point_cercle(int rayon);
unsigned nb_point_carre(int cote, int centre_x, int centre_y);
unsigned nb_point_rectangle(int largeur, int longueur, int centre_x, int centre_y);
unsigned nb_point_segment(int a_x, int a_y, int b_x, int b_y);

void init_front_carre(unsigned *front,unsigned *nb_points_front, int nb_row, int nb_col, int cote, int centre_x, int centre_y);
void init_front_rectangle(unsigned *front,unsigned *nb_points_front, int nb_row, int nb_col, int largeur, int longueur, int centre_x, int centre_y);
void init_front_cercle(unsigned *front,unsigned *nb_points_front, int nb_row, int nb_col, int rayon, int centre_x, int centre_y);
void init_front_segment(unsigned *front,unsigned *nb_points_front, int nb_row, int nb_col, int x_a, int y_a, int x_b, int y_b);

void RT_firstOrder(Pnum *m, Pnum *velocity, unsigned nb_row, unsigned nb_col, unsigned *front, unsigned nb_points_front);
void RT_secondOrder(Pnum* m,Pnum* velocity,unsigned nb_row, unsigned nb_col, unsigned* f, unsigned nb_points_front);
void init_velocity_const(Pnum *velocity,Pnum v, unsigned nb_row, unsigned nb_col);
void init_velocity(Pnum *velocity, unsigned nb_row, unsigned nb_col);

#endif /* defined(__PPN_Eikonal__AlgoRouyTourin__) */

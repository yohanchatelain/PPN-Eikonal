//
//  main.c
//  PPN Eikonal
//
//  Created by Yohan on 11/12/2014.
//  Copyright (c) 2014 Yohan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AlgoRouyTourin.h"
#include "VTK_ios.h"

int main(int argc, const char * argv[]) {
    unsigned nb_col = 11;
    unsigned nb_row = 11;
//    unsigned nb_points_fronts = nb_point_segment(50, 0, 50, 101);
    unsigned nb_points_fronts = 1;
    Pnum *grid, *velocity;
    unsigned *front;
    grid = (Pnum*) malloc(nb_col*nb_row*sizeof(Pnum));
    velocity = (Pnum*) malloc(nb_col*nb_row*sizeof(Pnum));
//    front = (unsigned*) malloc(8*3*sizeof(unsigned));
    front = (unsigned *) malloc(2*nb_points_fronts*sizeof(unsigned int));
//    init_velocity_const(velocity,1.0,nb_row,nb_col);
    init_velocity(velocity, nb_row, nb_col);
    //  init_front_segment(front, &nb_points_fronts, nb_row, nb_col, 50, 0, 50, 100);
    front[0] = nb_row/2;    front[1] = nb_col/2;
    //    front[0] = 0;   front[1] = nb_col-1;
//    front[2] = nb_row-1;   front[3] = 0;
//    front[4] = nb_row/2;    front[5] = nb_col/2;

    RT_firstOrder(grid, velocity, nb_row, nb_col, front, nb_points_fronts);
    writeVTK(grid, nb_row, nb_col, "firstOrd.vtk");
    RT_secondOrder(grid, velocity, nb_row, nb_col, front, nb_points_fronts);
    writeVTK(grid, nb_row, nb_col, "firstSnd.vtk");
    free(grid);
    free(velocity);
    free(front);
    return 0;
}

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
#include <math.h>
#include "AlgoRouyTourin.h"
#include "VTK_ios.h"

int main(int argc, const char * argv[]) {
    unsigned nb_col = 100;
    unsigned nb_row = 100;
//    unsigned nb_points_fronts = nb_point_segment(0, 0, 0, 100);
    unsigned nb_points_fronts = 1;
    
    Pnum *grid, *velocity;
    unsigned *front;
    int i,j;
    grid = (Pnum*) malloc(nb_col*nb_row*sizeof(Pnum));
    velocity = (Pnum*) malloc(nb_col*nb_row*sizeof(Pnum));
    front = (unsigned *) malloc(2*nb_points_fronts*sizeof(unsigned int));
//    front[0] = nb_row/2;    front[1] = 0;
    
//  init_velocity_gaussienne(velocity, nb_row, nb_col, nb_col/2, nb_row/2, nb_col/4, nb_row);
    init_velocity_const(velocity,1.0,nb_row,nb_col);
//    init_velocity_disque(velocity, 0.6788, 30, 50, 50, nb_row, nb_col);
//    init_velocity_rectangle(velocity, -1, nb_row, nb_col, 20, 10, 50, 10);
//    init_velocity_rectangle(velocity, -1, nb_row, nb_col, 20, 10, 50, 30);
//    init_velocity_rectangle(velocity, -1, nb_row, nb_col, 20, 10, 50, 50);
//    init_velocity_rectangle(velocity, -1, nb_row, nb_col, 20, 10, 50, 70);
//    init_velocity_rectangle(velocity, -1, nb_row, nb_col, 20, 10, 50, 90);
//        init_front_segment(front, &nb_points_fronts, nb_row, nb_col, 0, 0, 0, 100);
    //    init_front_cercle(front, &nb_points_fronts, nb_row, nb_col, 10, 50, 50);
//        init_velocity_disque(velocity, -1, 10, 50, 50, nb_row, nb_col);
//    front[0] = nb_row/2;    front[1] = nb_col/2;
        front[0] = 0;   front[1] = nb_col-1;
//        front[2] = nb_row-1;   front[3] = 0;
    //    front[4] = nb_row/2;    front[5] = nb_col/2;
    

//    for (i=10; i<100; i+=10) {
//        unsigned nb_col = i;
//        unsigned nb_row = i;
//        unsigned nb_points_fronts = 1;
//        
//        Pnum *grid, *velocity;
//        unsigned *front;
//        
//        grid = (Pnum*) malloc(nb_col*nb_row*sizeof(Pnum));
//        velocity = (Pnum*) malloc(nb_col*nb_row*sizeof(Pnum));
//        front = (unsigned *) malloc(2*nb_points_fronts*sizeof(unsigned int));
//        front[0] = nb_row/2;    front[1] = nb_col/2;
//        init_velocity_const(velocity,1.0,nb_row,nb_col);
//        
//        RT_firstOrder(grid, velocity, nb_row, nb_col, front, nb_points_fronts);
//        RT_secondOrder(grid, velocity, nb_row, nb_col, front, nb_points_fronts);
//        
//        free(grid);
//        free(velocity);
//        free(front);
//    }
//    for (i=100; i<1000; i+=100) {
//        unsigned nb_col = i;
//        unsigned nb_row = i;
//        unsigned nb_points_fronts = 1;
//        
//        Pnum *grid, *velocity;
//        unsigned *front;
//        
//        grid = (Pnum*) malloc(nb_col*nb_row*sizeof(Pnum));
//        velocity = (Pnum*) malloc(nb_col*nb_row*sizeof(Pnum));
//        front = (unsigned *) malloc(2*nb_points_fronts*sizeof(unsigned int));
//        front[0] = nb_row/2;    front[1] = nb_col/2;
//        init_velocity_const(velocity,1.0,nb_row,nb_col);
//        
//        RT_firstOrder(grid, velocity, nb_row, nb_col, front, nb_points_fronts);
//        RT_secondOrder(grid, velocity, nb_row, nb_col, front, nb_points_fronts);
//        
//        free(grid);
//        free(velocity);
//        free(front);
//    }
//    for (i=1000; i<2000; i+=1000) {
//        unsigned nb_col = i;
//        unsigned nb_row = i;
//        unsigned nb_points_fronts = 1;
//        
//        Pnum *grid, *velocity;
//        unsigned *front;
//        
//        grid = (Pnum*) malloc(nb_col*nb_row*sizeof(Pnum));
//        velocity = (Pnum*) malloc(nb_col*nb_row*sizeof(Pnum));
//        front = (unsigned *) malloc(2*nb_points_fronts*sizeof(unsigned int));
//        front[0] = nb_row/2;    front[1] = nb_col/2;
//        init_velocity_const(velocity,1.0,nb_row,nb_col);
//        
//        RT_firstOrder(grid, velocity, nb_row, nb_col, front, nb_points_fronts);
//        RT_secondOrder(grid, velocity, nb_row, nb_col, front, nb_points_fronts);
//        
//        free(grid);
//        free(velocity);
//        free(front);
//    }
//    
//    Pnum *l2 = (Pnum*) malloc(nb_row*nb_col*sizeof(Pnum));
//    for (i=0; i<nb_col; i++) {
//        for (j=0; j<nb_row; j++) {
//            l2[ind(nb_col, i, j)] = sqrtf((i-nb_col/2)*(i-nb_col/2)+(j-nb_row/2)*(j-nb_row/2));
//        }
//    }
//    
    RT_firstOrder(grid, velocity, nb_row, nb_col, front, nb_points_fronts);
    writeVTK(grid, nb_row, nb_col, "fstOrd.vtk");
    RT_secondOrder(grid, velocity, nb_row, nb_col, front, nb_points_fronts);
    writeVTK(grid, nb_row, nb_col, "sndOrd.vtk");
//    writeVTK(l2, nb_row, nb_col, "l2.vtk");
    free(grid);
    free(velocity);
    free(front);
    return 0;
}

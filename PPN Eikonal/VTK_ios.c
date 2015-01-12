//
//  VTK_ios.c
//  PPN Eikonal
//
//  Created by Yohan on 12/12/2014.
//  Copyright (c) 2014 Yohan. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "VTK_ios.h"

FILE* gnudata_open(char *filename){
    FILE *file;
    char name[30];
    sprintf(name, "%s.dat",filename);
    
    file = fopen(name, "a+");
    if (file == NULL) {
        fprintf(stderr, "File couldn't be open\n");
        exit(1);
    }
    printf("%s has been written\n",name);
    return file;
}

void dput_xy(FILE *file,Pnum x, Pnum y){
    fprintf(file, "%e %e\n",x,y);
}

void vtk_read_error(char * string_error,const char * string_expected){
    fprintf(stderr, "Error while reading :\n");
    fprintf(stderr, "Invalid format %s\n",string_error);
    fprintf(stderr, "Format expected %s\n",string_expected);
}

void writeVTK(Pnum *m,unsigned nb_row, unsigned nb_col, char *file_name_matrix){
    
    int i,j;
    FILE* fp;
    
    char* vtk ="# vtk DataFile Version 3.0";
    char* type="Propagation de front";
    char* format = "ASCII";
    char* dataset="DATASET RECTILINEAR_GRID";
    fp = fopen(file_name_matrix,"w+");

    //Header
    printf("\n Writting data ....\n ");
    fprintf(fp,"%s\n%s\n%s\n%s\n",vtk,type,format,dataset);
    fprintf(fp,"DIMENSIONS %d %d %d\n",nb_row,nb_col,1);
    
    //Coordonnées
    fprintf(fp,"X_COORDINATES %d float\n",nb_col);
    for(i=0;i<nb_col;i++)
        fprintf(fp,"%f ",i/1.0);
    
    fprintf(fp,"\nY_COORDINATES %d float\n",nb_row);
    for(j=0;j<nb_row;j++)
        fprintf(fp,"%f ",j/1.0);
    
    fprintf(fp,"\nZ_COORDINATES 1 float\n");
    fprintf(fp,"0.0");
    
    //Valeurs
    fprintf(fp,"\nPOINT_DATA %d\n",nb_row*nb_col);
    fprintf(fp,"SCALARS u float 1\n");
    fprintf(fp,"LOOKUP_TABLE default\n");
    
    for(i=0;i<nb_row;i++)
        for(j=0;j<nb_col;j++){
            Pnum f = m[ind(nb_col,i,j)];
            f = f==INF ? -1 : f;
            fprintf(fp,"%f ",f);
        }
        printf("%s has been written\n",file_name_matrix);
    
    fclose(fp);
    
}

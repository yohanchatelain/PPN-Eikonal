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

static char *vtk_ext = "vtk";
static char *vtk_part_one = "# vtk Datafile Version %d.%d";

void vtk_read_error(char * string_error,const char * string_expected){
    fprintf(stderr, "Error while reading :\n");
    fprintf(stderr, "Invalid format %s\n",string_error);
    fprintf(stderr, "Format expected %s\n",string_expected);
}

void readVTK(Pnum *velocity, char *file_name_matrix){
    char * ext = strrchr(file_name_matrix, '.');
    if (strcmp(vtk_ext, ext)){
        vtk_read_error(ext,vtk_ext);
    }else{
        FILE* file_stream = fopen(file_name_matrix, "r");
        if (file_stream != NULL){
            char *buff;
            gets(buff);
            if(strcmp(buff, vtk_part_one)) vtk_read_error(buff,vtk_part_one);
            
        }
    }
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
    fprintf(fp,"X_COORDINATES %d float\n",nb_row);
    for(i=0;i<nb_col;i++)
        fprintf(fp,"%f ",i/1.0);
    
    fprintf(fp,"\nY_COORDINATES %d float\n",nb_col);
    for(j=0;j<nb_row;j++)
        fprintf(fp,"%f ",j/1.0);
    
    fprintf(fp,"\nZ_COORDINATES 1 float\n");
    fprintf(fp,"0.0");
    
    fprintf(fp,"\nPOINT_DATA %d\n",nb_row*nb_col);
    fprintf(fp,"SCALARS u float 1\n");
    fprintf(fp,"LOOKUP_TABLE default\n");
    
    for(i=0;i<nb_row;i++)
        for(j=0;j<nb_col;j++)
            fprintf(fp,"%f ",m[ind(nb_col,i,j)]);
    
    printf("\ndone ... exit \n ");
    
    fclose(fp);
    
}

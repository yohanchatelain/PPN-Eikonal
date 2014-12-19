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

void readVTK(Matrice *m,char *file_name_matrix){
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

void writeVTK(Matrice *m,char *file_name_matrix){

}

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

int main(int argc, const char * argv[]) {
    static char *vtk_part_one = "# vtk Datafile Version %d.%d";
    char *vtk = "# vtk Datafile Version 3.0";
    printf("%d\n",strcmp(vtk_part_one,vtk));
    
    return 0;
}

//
//  VTK_ios.h
//  PPN Eikonal
//
//  Created by Yohan on 12/12/2014.
//  Copyright (c) 2014 Yohan. All rights reserved.
//

#ifndef __PPN_Eikonal__VTK_ios__
#define __PPN_Eikonal__VTK_ios__

#include <stdio.h>
#include "Matrix.h"

void readVTK(Matrice *m,char *file_name_matrix);
void writeVTK(Matrice *m,char *file_name_matrix);

#endif /* defined(__PPN_Eikonal__VTKReader__) */

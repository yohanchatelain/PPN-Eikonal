//
//  AlgoRouyTourin.c
//  PPN Eikonal
//
//  Created by Yohan on 11/12/2014.
//  Copyright (c) 2014 Yohan. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "AlgoRouyTourin.h"

const static int PRINT = 0;
const static Pnum epiflon = 10E-3;
const static Pnum h = 1.0;

int max(int a , int b){
    return (a<b) ? b : a;
}

unsigned nb_point_carre(int cote, int centre_x, int centre_y){
    cote = (cote % 2 == 0) ? cote+1 : cote;
    return 4*(cote-1);
}

unsigned nb_point_rectangle(int largeur, int longueur, int centre_x, int centre_y){
    largeur = (largeur % 2 == 0) ? largeur+1 : largeur;
    longueur = (longueur % 2 == 0) ? longueur+1 : longueur;
    return 2*longueur+2*(largeur-2);
}

unsigned nb_point_cercle(int rayon){
    return 8*rayon;
}

unsigned nb_point_segment(int x1, int y1, int x2, int y2){
    return max(abs(x1-x2)+1,abs(y1-y2)+1);
}

void init_front_carre(unsigned *front,unsigned *nb_points_front, int nb_row, int nb_col, int cote, int centre_x, int centre_y){
    int i,c = 0;
    int coin_sup_x = cote/2+centre_x;
    coin_sup_x = (coin_sup_x >= nb_col) ? nb_col-1 : coin_sup_x;
    
    int coin_inf_x = centre_x-cote/2;
    coin_inf_x = (coin_inf_x < 0) ? 0 : coin_inf_x;
    
    int coin_sup_y = cote/2+centre_y;
    coin_sup_y = (coin_sup_y >= nb_row) ? nb_row-1 : coin_sup_y;
    
    int coin_inf_y = centre_y-cote/2;
    coin_inf_y = (coin_inf_y < 0) ? 0 : coin_inf_y;
    
    for (i = coin_inf_x; i<coin_sup_x; i++, c+=2) {
        front[c] = i;   front[c+1] = coin_sup_y;
    }
    
    for (i = coin_inf_x; i<coin_sup_x; i++, c+=2) {
        front[c] = i; front[c+1] = coin_inf_y;
    }
    
    for (i = coin_inf_y+1; i<coin_sup_y; i++, c+=2) {
        front[c] = coin_inf_x; front[c+1] = i;
    }
    
    for (i = coin_inf_y; i<=coin_sup_y; i++, c+=2) {
        front[c] = coin_sup_x; front[c+1] = i;
    }
}

void init_front_cercle(unsigned *front,unsigned *nb_points_front, int nb_row, int nb_col, int rayon, int centre_x, int centre_y){
    int x, y, m, c = 0;
    x = 0 ;
    y = rayon ;
    m = 5 - 4*rayon ;
    while (x <= y) {
        front[c] = x+centre_x; front[c+1] = y+centre_y;
        front[c+2] = y+centre_x; front[c+3] = x+centre_y;
        front[c+4] = -x+centre_x; front[c+5] = y+centre_y;
        front[c+6] = -y+centre_x; front[c+7] = x+centre_y;
        front[c+8] = x+centre_x; front[c+9] = -y+centre_y;
        front[c+10] = y+centre_x; front[c+11] = -x+centre_y;
        front[c+12] = -x+centre_x; front[c+13] = -y+centre_y;
        front[c+14] = -y+centre_x; front[c+15] = -x+centre_y;
        c+=16;
        if (m > 0) {
            y = y - 1 ;
            m = m-8*y ;
        }
        x = x+1 ;
        m = m + 8*x+4 ;
    }
    *nb_points_front = c/2;
}

void init_front_segment(unsigned *front,unsigned *nb_points_front, int nb_row, int nb_col, int x1, int y1, int x2, int y2){
    
    int dx, dy, c = 0;
    
    if ((dx = x2 - x1) != 0) {
        if (dx > 0) {
            if ((dy = y2 - y1) != 0) {
                if (dy > 0) {
                    if (dx >= dy) {
                        int e ;
                        dx = (e = dx) * 2 ; dy *= 2;
                        while(1){
                            front[c] = x1; front[c+1] = y1; c+=2;
                            if (x1++ == x2) break ;
                            if ((e -= dy) < 0) {
                                y1++;
                                e += dx ;
                            }
                        }
                    }else{
                        int e ;
                        dy = (e = dy) * 2 ; dx *= 2;
                        while(1){
                            front[c] = x1; front[c+1] = y1; c+=2;
                            if (y1++ == y2) break ;
                            if ((e -= dx) < 0){
                                x1++;
                                e += dy ;
                            }
                        }
                    }
                }else{
                    if (dx >= -dy) {
                        int e ;
                        dx = (e = dx) * 2 ; dy *= 2;
                        while(1) {
                            front[c] = x1; front[c+1] = y1; c+=2;
                            if (x1++ == x2) break ;
                            if ((e += dy) < 0) {
                                y1--;
                                e += dx ;
                            }
                        }
                    }else{
                        int e ;
                        dy = (e = dy) * 2 ; dx *= 2;
                        while(1) {
                            front[c] = x1; front[c+1] = y1; c+=2;
                            if (y1-- == y2) break ;
                            if ((e += dx) > 0) {
                                x1++;
                                e += dy ;
                            }
                        }
                    }
                    
                }
            }else{
                do{
                    front[c] = x1; front[c+1] = y1; c+=2;
                }while((x1++) != x2) ;
                
            }
        }else{
            if ((dy = y2 - y1) != 0) {
                if (dy > 0) {
                    if (-dx >= dy) {
                        int e ;
                        dx = (e = dx) * 2 ; dy *= 2;
                        while(1) {
                            front[c] = x1; front[c+1] = y1; c+=2;
                            if (x1-- == x2) break ;
                            if ((e += dy) >= 0) {
                                y1++;
                                e += dx ;
                            }
                        }
                    }else{
                        int e ;
                        dy = (e = dy) * 2 ; dx *= 2;
                        while(1) {
                            front[c] = x1; front[c+1] = y1; c+=2;
                            if (y1++ == y2) break;
                            if ((e += dx) <= 0) {
                                x1--;
                                e += dy ;
                            }
                        }
                    }
                    
                } else {
                    if (dx <= dy) {
                        int e ;
                        dx = (e = dx) * 2 ; dy *= 2;
                        while(1) {
                            front[c] = x1; front[c+1] = y1; c+=2;
                            if (x1-- == x2) break ;
                            if ((e -= dy) >= 0) {
                                y1--;
                                e += dx ;
                            }
                        }
                    } else {
                        int e ;
                        dy = (e = dy) * 2 ; dx *= 2;
                        while(1) {
                            front[c] = x1; front[c+1] = y1; c+=2;
                            if (y1-- == y2) break ;
                            if ((e -= dx) >= 0) {
                                x1--;
                                e += dy ;
                            }
                        }
                    }
                    
                }
            } else {
                do{
                    front[c] = x1; front[c+1] = y1; c+=2;
                }while((x1--) != x2);
                
            }
        }
    } else {
        if ((dy = y2 - y1) != 0) {
            if (dy > 0) {
                do{
                    front[c] = x1; front[c+1] = y1; c+=2;
                }while((y1 = y1 + 1) != y2);
            } else {
                do{
                    front[c] = x1; front[c+1] = y1; c+=2;
                }while((y1--) != y2);
                
            }
        }
    }
    *nb_points_front = c/2;
}

void init_front_rectangle(unsigned *front,unsigned *nb_points_front, int nb_row, int nb_col, int largeur, int longueur, int centre_x, int centre_y){
    int i,c = 0;
    int coin_sup_x = largeur/2+centre_x;
    coin_sup_x = (coin_sup_x >= nb_col) ? nb_col-1 : coin_sup_x;
    int coin_inf_x = centre_x-largeur/2;
    coin_inf_x = (coin_inf_x < 0) ? 0 : coin_inf_x;
    int coin_sup_y = longueur/2+centre_y;
    coin_sup_y = (coin_sup_y >= nb_row) ? nb_row-1 : coin_sup_y;
    int coin_inf_y = centre_y-(longueur/2);
    coin_inf_y = (coin_inf_y < 0) ? 0 : coin_inf_y;
    
    for (i = coin_inf_x; i<coin_sup_x; i++, c+=2) {
        front[c] = i;   front[c+1] = coin_sup_y;
    }
    for (i = coin_inf_x; i<coin_sup_x; i++, c+=2) {
        front[c] = i; front[c+1] = coin_inf_y;
    }
    for (i = coin_inf_y+1; i<coin_sup_y; i++, c+=2) {
        front[c] = coin_inf_x; front[c+1] = i;
    }
    for (i = coin_inf_y; i<=coin_sup_y; i++, c+=2) {
        front[c] = coin_sup_x; front[c+1] = i;
    }
}

void init_velocity_const(Pnum *velocity,Pnum v, unsigned nb_row, unsigned nb_col){
    int i,j;
    for (i=0; i<nb_row; i++) {
        for (j=0; j<nb_col; j++) {
            velocity[ind(nb_col, i, j)] =  v;
        }
    }
}

Pnum gaussienne(Pnum x, Pnum y, Pnum x_0, Pnum y_0, Pnum sigma_x, Pnum sigma_y){
    return expf(-( (x-x_0)*(x-x_0)/(2*sigma_x*sigma_x) + (y-y_0)*(y-y_0)/(2*sigma_y*sigma_y) ));
}

void init_velocity(Pnum *velocity, unsigned nb_row, unsigned nb_col){
    int i,j;
    Pnum x_0 = nb_col/2, y_0 = nb_row/2;
    for (i=0; i<nb_row; i++) {
        for (j=0; j<nb_col; j++) {
            velocity[ind(nb_col, i, j)] =  gaussienne(i,j,x_0,y_0,nb_row/4,nb_col);
        }
    }
    print_matrice(velocity, nb_row, nb_col);
}

void disque(Pnum x, Pnum y, Pnum x_0, Pnum y_0){
    
}

void init_velocity_disque(Pnum *velocity, unsigned nb_row, unsigned nb_col){
    int i,j;
    Pnum x_0 = nb_col/2, y_0 = nb_row/2;
    for (i=0; i<nb_row; i++) {
        for (j=0; j<nb_col; j++) {
            velocity[ind(nb_col, i, j)] =  disque(i,j,x_0,y_0,nb_row/4,nb_col);
        }
    }
    print_matrice(velocity, nb_row, nb_col);
}

int convergence(Pnum *m,Pnum *m_0, unsigned nb_row, unsigned nb_col){
    int i,j;
    for (i = 0; i<nb_row; i++) {
        for (j = 0; j<nb_col; j++) {
            if ( epiflon <= fabsf( m[ind(nb_col,i, j)] - m_0[ind(nb_col, i, j)] ) )
                return 0;
        }
    }
    return 1;
}

void set_front_source_ordre1(Pnum *m,unsigned nb_row, unsigned nb_col, int x, int y){
    if (x+1 < nb_col) m[ind(nb_col, x+1, y)] = 1.0;
    if (x-1 >= 0) m[ind(nb_col, x-1, y)] = 1.0;
    if (y+1 < nb_row) m[ind(nb_col, x, y+1)] = 1.0;
    if (y-1 >= 0) m[ind(nb_col, x, y-1)] = 1.0;
}

void RT_firstOrder(Pnum* m,Pnum* velocity,unsigned nb_row, unsigned nb_col, unsigned* f, unsigned nb_points_front){
    
    Pnum* m_0 = (Pnum*) malloc(nb_col*nb_row*sizeof(Pnum));
    //Initialisation des noeuds
    int i,j;
    for (i = 0; i<nb_row; i++) {
        for (j = 0; j<nb_col; j++) {
            m_0[ind(nb_col,i,j)] = INF;
        }
    }
    
    //Initialisation des noeuds sources
    for (i = 0; i<2*nb_points_front; i+=2) {
        m_0[ind(nb_col,f[i], f[i+1])] = 0.0;
    }
    
    int c = 0;
    do{
        copie(m_0, m, nb_row, nb_col);
        for (i = 0; i<nb_row; i++) {
            for (j = 0; j<nb_col; j++) {
                Pnum x_m1 = (i-1 >= 0)       ? m[ind(nb_col, i-1, j)] : INF;
                Pnum x_p1 = (i+1 < nb_col)  ? m[ind(nb_col, i+1, j)] : INF;
                Pnum y_m1 = (j-1 >= 0)       ? m[ind(nb_col, i, j-1)] : INF;
                Pnum y_p1 = (j+1 < nb_row)  ? m[ind(nb_col, i, j+1)] : INF;
                Pnum Tx = fminf(x_m1, x_p1);
                Pnum Ty = fminf(y_m1, y_p1);
                Pnum f = velocity[ind(nb_col, i, j)];
                Pnum sol = solveEquation_1(Tx,Ty,h,f);
                Pnum sol_min = fminf(m[ind(nb_col, i, j)],sol);
                m_0[ind(nb_col, i, j)] = sol_min;
            }
        }
        if (PRINT) {
            printf("\n----\n");
            print_matrice(m, nb_row, nb_col);
        }
        c++;
    } while (!convergence(m_0,m,nb_row,nb_col));
    free(m_0);
    printf("%d itérations\n",c);
}

void RT_secondOrder(Pnum* m,Pnum* velocity,unsigned nb_row, unsigned nb_col, unsigned* f, unsigned nb_points_front){
    
    Pnum* m_0 = (Pnum*) malloc(nb_col*nb_row*sizeof(Pnum));
    
    //Initialisation des noeuds
    int i,j;
    for (i = 0; i<nb_row; i++) {
        for (j = 0; j<nb_col; j++) {
            m_0[ind(nb_col,i,j)] = INF;
            
        }
    }
    //Initialisation des noeuds sources
    for (i = 0; i<2*nb_points_front; i+=2) {
        m_0[ind(nb_col,f[i], f[i+1])] = 0.0;
    }
    
    int s = 0, fi = 0, c = 0;
    do{
        copie(m_0, m, nb_row, nb_col);
        for (i = 0; i<nb_row; i++) {
            for (j = 0; j<nb_col; j++) {
                Pnum x_m1 = (i-1 >= 0)       ? m[ind(nb_col, i-1, j)] : INF;
                Pnum x_m2 = (i-2 >= 0)       ? m[ind(nb_col, i-2, j)] : INF;
                Pnum x_p1 = (i+1 < nb_col)  ? m[ind(nb_col, i+1, j)] : INF;
                Pnum x_p2 = (i+2 < nb_col)  ? m[ind(nb_col, i+2, j)] : INF;
                Pnum y_m1 = (j-1 >= 0)       ? m[ind(nb_col, i, j-1)] : INF;
                Pnum y_m2 = (j-2 >= 0)       ? m[ind(nb_col, i, j-2)] : INF;
                Pnum y_p1 = (j+1 < nb_row)  ? m[ind(nb_col, i, j+1)] : INF;
                Pnum y_p2 = (j+2 < nb_row)  ? m[ind(nb_col, i, j+2)] : INF;
                Pnum sol, Tx, Ty, f;
                f = velocity[ind(nb_col, i, j)];
                if (x_p2 < INF && x_m2 < INF && y_m2 < INF && y_p2 < INF ){
                    s++;
                    Tx = fminf((4*x_m1-x_m2)/3.0, (4*x_p1-x_p2)/3.0);
                    Ty = fminf((4*y_m1-y_m2)/3.0,(4*y_p1-y_p2)/3.0);
                    sol = solveEquation_2(Tx,Ty,h,f);
                }else{
                    fi++;
                    Tx = fminf(x_m1, x_p1);
                    Ty = fminf(y_m1, y_p1);
                    sol = solveEquation_1(Tx,Ty,h,f);
                }
                Pnum sol_min = fminf(m[ind(nb_col, i, j)],sol);
                m_0[ind(nb_col, i, j)] = sol_min;
            }
        }
        c++;
    } while (!convergence(m_0,m,nb_row,nb_col));
    free(m_0);
    printf("%d itérations\n",c);
}


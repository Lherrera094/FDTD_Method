#ifndef _FDTD1_H
#define _FDTD1_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Grid {
    /* data */
    double *ez;
    double *hy;
    int sizeX;
    int time, maxTime;
    double cdtds;
} Grid;

/*memory allocation macro*/
#define ALLOC_1D(PNTR, NUM, TYPE)                 \
    PNTR = (TYPE *)calloc(NUM, sizeof(TYPE) );    \
    if(!PNTR){                                    \
        perror("ALLOC_1D");                       \
        fprintf( stderr,                         \
            "Allocation failed for" #PNTR ". \n");\
        exit(-1);                                 \
    }

/*macros for accesing arrays and such*/
/* NOTE!!!! The structure is g.*/
#define Hy(MM)      g->hy[MM]
#define Ez(MM)      g->ez[MM]
#define SizeX       g->sizeX
#define Time        g->time
#define MaxTime     g->maxTime
#define Cdtds       g->cdtds


#endif 



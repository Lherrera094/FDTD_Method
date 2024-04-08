#ifndef _FDTD_GRID1_H
#define _FDTD_GRID1_H

#include <stdio.h>
#include <stdlib.h>

enum GRIDTYPE {oneDGrid, teZGrid, tmZGrid, threeDGrid};

typedef struct Grid {
    /* data */
    double *hx, *chxh, *chxe;
    double *hy, *chyh, *chye;
    double *hz, *chzh, *chze;
    double *ex, *cexe, *cexh;
    double *ey, *ceye, *ceyh;
    double *ez, *ceze, *cezh;
    int sizeX, sizeY, sizeZ;
    int time, maxTime;
    int type;
    double cdtds;
} Grid;

/*memory allocation macro*/
#define ALLOC_2D(PNTR, NUMX, NUMY, TYPE)                        \
    PNTR = (TYPE *)calloc( (NUMX) * (NUMY), sizeof(TYPE) );     \
    if(!PNTR){                                                  \
        perror("ALLOC_1D");                                     \
        fprintf( stderr,                                        \
            "Allocation failed for" #PNTR ". \n");              \
        exit(-1);                                               \
    }

/*macros for accesing arrays and such*/
/* NOTE!!!! The structure is g.*/
#define Hy(MM)      g->hy[MM]
#define Chyh(MM)    g->chyh[MM]
#define Chye(MM)    g->chye[MM]

#define Ez(MM)      g->ez[MM]
#define Ceze(MM)    g->ceze[MM]
#define Cezh(MM)    g->cezh[MM]

#define SizeX       g->sizeX
#define Time        g->time
#define MaxTime     g->maxTime
#define Cdtds       g->cdtds

/*Function Prototypes*/
void abcInit(Grid *g);
void abc(Grid *g);

void gridInit(Grid *g);

void saveFile(Grid *g);

void tfsfInit(Grid *g);
void tfsfUpdate(Grid *g);

void updateE(Grid *g);
void updateH(Grid *g);

#endif 
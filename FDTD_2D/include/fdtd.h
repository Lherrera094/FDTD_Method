#ifndef _FDTD_GRID1_H
#define _FDTD_GRID1_H

#include <stdio.h>
#include <stdlib.h>

enum GRIDTYPE {oneDGrid, teZGrid, tmZGrid, threeDGrid};

typedef struct Grid {
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

#endif 
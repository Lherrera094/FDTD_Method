/*Function Initialize Grid structure*/

#include "fdtd-macros-tmz.h"
#include "fdtd-alloc1.h"
#include <math.h>

void gridInit(Grid *g){
    double imp0 = 377.0;
    int mm, nn;

    Type = tmZGrid;
    SizeX = 101;
    SizeY = 81;
    MaxTime = 300;
    Cdtds = 1.0 / sqrt(2.0);

    ALLOC_2D(g->hx,     SizeX,    SizeY - 1, double);
    ALLOC_2D(g->chxh,   SizeX,    SizeY - 1, double);
    ALLOC_2D(g->chxe,   SizeX,    SizeY - 1, double);
    ALLOC_2D(g->hy,     SizeX - 1,SizeY,     double);
    ALLOC_2D(g->chyh,   SizeX - 1,SizeY,     double);
    ALLOC_2D(g->chye,   SizeX - 1,SizeY,     double);
    ALLOC_2D(g->ez,     SizeX,    SizeY,     double);
    ALLOC_2D(g->ceze,   SizeX,    SizeY,     double);
    ALLOC_2D(g->cezh,   SizeX,    SizeY,     double);

    /*set eletric field update coefficients*/
    for(mm = 0; mm < SizeX; mm++){
        for(nn = 0; nn < SizeY; nn++){
            Ceze(mm, nn) = 1.0;
            Cezh(mm, nn) = Cdtds * imp0;
        }
    }//end for electric field 

    /*set magnetic field update coefficients*/
    for(mm = 0; mm < SizeX; mm++){
        for(nn = 0; nn < SizeY - 1; nn++){
            Chxh(mm, nn) = 1.0;
            Chxe(mm, nn) = Cdtds / imp0;
        }
    }

    for(mm = 0; mm < SizeX - 1; mm++){
        for(nn = 0; nn < SizeY; nn++){
            Chyh(mm, nn) = 1.0;
            Chye(mm, nn) = 1.0 / imp0; 
        }
    }//end for electric field

    return;
}

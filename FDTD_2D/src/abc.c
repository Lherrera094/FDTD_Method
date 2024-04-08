/*Implements first-order Absrobing boundary condition*/

#include "fdtd.h"
#include <math.h>

static int initDone = 0;
static double ezOldLeft = 0.0, ezOldRight = 0.0;
static double abcCoefLeft, abcCoefRight;

//Initialize the first order ABC
void abcInit(Grid *g){
    double temp;
    initDone = 1;

    /*calculate coefficient on the left of the grid*/
    temp = sqrt( Cezh(0) * Chye(0) );
    abcCoefLeft = (temp - 1.0) / (temp + 1.0);

    /*calculate coefficient on the right end of the grid*/
    temp = sqrt(SizeX - 1) * Chye(SizeX - 2);
    abcCoefRight = (temp - 1.0) / (temp + 1.0);

    return;
}

/*Apply ABC on the grid*/
void abc(Grid *g){
    /*Check if abcInit() has been called*/
    if (!initDone){
        fprintf(stderr,
            "abc: Init must be called before abc. \n");
        exit(-1);
    }
    
    /*ABC for the left side of the grid*/
    Ez(0) = ezOldLeft + abcCoefLeft*(Ez(1) - Ez(0));
    ezOldLeft = Ez(1);

    /*ABC for right side of the grid*/
    Ez(SizeX - 1) = ezOldRight + abcCoefRight * ( Ez(SizeX - 2) - Ez(SizeX - 1) );
    ezOldRight = Ez(SizeX - 2);
}
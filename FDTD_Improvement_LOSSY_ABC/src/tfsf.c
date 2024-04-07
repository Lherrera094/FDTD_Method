/*Function to implement a 1D DTD boundary*/

#include <math.h>
#include "fdtd.h"
#include "ezinc.h"

static int tfsfBoundary = 0;

void tfsfInit(Grid *g){

    printf("Enter location of TFSF boundary: ");
    scanf(" %d", &tfsfBoundary);

    ezIncInit(g);
}

void tfsfUpdate(Grid *g){
    /*Check if tfsfInit() has been called*/
    if(tfsfBoundary <= 0){
        fprintf(stderr, 
            "tfsfUpdate: tfsfInit must be called before tfsfUpdate. \n"
            "            Boundary location must be set to positive value. \n");
        exit(-1);
    }

    /*Correct Hy adjcent to TFSF boundary*/
    Hy(tfsfBoundary) -= ezInc(Time, 0.0) * Chye(tfsfBoundary);

    /*correct Ez adjacent to TFSF boundary*/
    Ez(tfsfBoundary + 1) += ezInc(Time + 0.5, -0.5);
}
/*Functions to update the Electric and Magnetic field*/

#include "fdtd.h"

/*Update magnetic field*/
void updateH(Grid *g){
    int mm;

    for ( mm = 0; mm < SizeX - 1; mm++){
        Hy(mm) = Chyh(mm) * Hy(mm) + 
                 Chye(mm) * (Ez(mm + 1) - Ez(mm) );
    }
    return;
}

/*Update electric field*/
void updateE(Grid *g){
    int mm;
    
    for ( mm = 1; mm < SizeX - 1; mm++){
        Ez(mm) = Ceze(mm) * Ez(mm) + 
                 Cezh(mm) * (Hy(mm) - Hy(mm - 1) );
    }
    return;
}


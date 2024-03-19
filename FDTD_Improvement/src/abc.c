/*Functions for the Absrobing boundary condition*/

#include "fdtd.h"

//Initialize the ABC
void abcInit(Grid *g){

}

/*Apply ABC on the grid*/
void abc(Grid *g){

    /*Simple ABC for the left side of the grid*/
    Ez(0) = Ez(1);
}
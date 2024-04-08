/*Functions to calculate the source function*/

#include "ezinc.h"

/*Global variables -- private to this file*/
static double ppw = 0, cdtds;

/*prompt user for source-function width and delay*/
void ezIncInit(Grid *g){

    cdtds = Cdtds;
    
    printf("Enter poins per wavelenght: ");
    scanf(" %lf", &ppw);

    return;
}

/*Calculate source function at given time and location*/
double ezInc(double time, double location){
    if(ppw <= 0){
        fprintf(stderr, 
            "ezInc: must call ezIncInit before ezInc. \n"
            "       Width must be positive. \n");
    exit(-1);
    }

    return sin(2.0 * M_PI / ppw * (cdtds * time - location));
}
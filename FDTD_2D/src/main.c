/*TMz simulation with Ricker source at center of Grid*/

#include "fdtd-alloc1.h"
#include "fdtd-macros-tmz.h"
#include "fdtd-proto1.h"
#include "ezinc.h"
#include <time.h>

void writeFile(Grid *g){
    char filename[100];
    sprintf(filename, "data/time=%d.csv", g->time);

    FILE *fptr = fopen(filename, "w");

    if(fptr == NULL){
        printf("Error opening the file. \n");
    }

    fprintf(fptr, "pos,Hx,Hy,Ez\n");
    for(int i = 0; i < g->sizeX; i++){
        fprintf(fptr, "%d,%.5f,%.5f, %.5f\n", i, g->hx[i], g->hy[i], g->ez[i]);
    }
    
    fclose(fptr);
}

int main(){

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    
    Grid *g;                //Declares a pointer to the struct g               

    ALLOC_1D(g, 1, Grid);   //Allocates in memmory the space for pointer to structure g

    gridInit(g);
    ezIncInit(g);

    /*do time stepping*/
    for(Time = 0; Time < MaxTime; Time++){
        updateH2d(g);     //Update mgnetic field
        updateE2d(g);     //update electric field

        Ez(SizeX / 2, SizeY / 2) = ezInc(Time, 0.0);
        
        writeFile(g);   //save file
    }//end of time stepping

    end = clock();
    cpu_time_used = ( (double)(end-start) )/CLOCKS_PER_SEC;
	printf("Program Running Time = %.2e s.\n", cpu_time_used);

    return 0;
}
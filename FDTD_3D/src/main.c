/*TMz simulation with Ricker source at center of Grid*/

#include "fdtd-alloc.h"
#include "fdtd-macro.h"
#include "fdtd-proto.h"
#include "ezinc.h"
#include <time.h>


void writeFile(Grid *g){
    char filename[100];
    sprintf(filename, "data/time=%d.csv", Time);

    FILE *fptr = fopen(filename, "w");

    if(fptr == NULL){
        printf("Error opening the file. \n");
    }

    for(int i = 0; i < SizeX; i++){
        fprintf(fptr, "%d,",i);
    }
    fprintf(fptr, "\n");

    //pragma omp for
    int pp = 15;
    for(int nn = 0; nn < SizeY; nn++){
        for(int mm = 0; mm < SizeX; mm++){
            fprintf(fptr, "%.5f,", 150*Ez(mm,nn,pp));
        }
        fprintf(fptr, "\n"); 
    }
    
    fclose(fptr);
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    Grid *g;

    ALLOC_1D(g, 1, Grid);   // allocate memory for grid structure
    gridInit(g);            // initialize 3D grid

    abcInit(g);             // initialize ABC
    ezIncInit(g);
    snapshot3dInit(g);      // initialize snapshots

    /* do time stepping */
    for (Time = 0; Time < MaxTime; Time++) {

        if(Time == 150){
            start = clock();
        }    
        
        updateH(g);             // update magnetic fields
        updateE(g);             // update electric fields

        if(Time == 150){
            end = clock();
            cpu_time_used = ( (double)(end-start) )/CLOCKS_PER_SEC;
	        printf("Program Running Time = %.2e s.\n", cpu_time_used);
        }

        Ex((SizeX - 1) / 2, SizeY / 2, SizeZ / 2) += ezInc(Time, 0.0);
        abc(g);                 // apply ABC
        //snapshot3d(g);          // take a snapshot (if appropriate)
    
        writeFile(g);
    } // end of time-stepping

    return 0;
}
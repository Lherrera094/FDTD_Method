/*TMz simulation with Ricker source at center of Grid*/

#include "fdtd-alloc1.h"
#include "fdtd-macros-tmz.h"
#include "fdtd-proto1.h"
#include "ezinc.h"
#include <time.h>
#include <omp.h>

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
    for(int mm = 0; mm < SizeY; mm++){
        for(int nn = 0; nn < SizeX; nn++){
            fprintf(fptr, "%.5f,", Ez(mm,nn));
        }
        fprintf(fptr, "\n"); 
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
    snapshotInit2d(g);

    /*do time stepping*/
    for(Time = 0; Time < MaxTime; Time++){
        updateH2d(g);     //Update mgnetic field
        updateE2d(g);     //update electric field

        Ez(SizeX / 2, SizeY / 2) = ezInc(Time, 0.0);
        
        writeFile(g);
        //snapshot2d(g);
    }//end of time stepping

    end = clock();
    cpu_time_used = ( (double)(end-start) )/CLOCKS_PER_SEC;
	printf("Program Running Time = %.2e s.\n", cpu_time_used);

    return 0;
}
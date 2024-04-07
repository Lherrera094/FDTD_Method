/*TFSF Boundary: FDTD method for 1D code
TFSF boundary between hy[49] and ez[50] and 
dielectric material starting at ez[100]*/

#include "fdtd.h"
#include <time.h>

void writeFile(Grid *grid){
    char filename[100];
    sprintf(filename, "data/time=%d.csv", grid->time);

    FILE *fptr = fopen(filename, "w");

    if(fptr == NULL){
        printf("Error opening the file. \n");
    }

    fprintf(fptr, "pos,Magnetic_Field,Electric_Field\n");
    for(int i = 0; i < grid->sizeX; i++){
        fprintf(fptr, "%d,%.5f,%.5f\n", i, grid->hy[i], grid->ez[i]);
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
    abcInit(g);
    tfsfInit(g);

    /*do time stepping*/
    for(Time = 0; Time < MaxTime; Time++){
        updateH(g);     //Update mgnetic field
        tfsfUpdate(g);  //correct on TFSF boundary
        abc(g);         //Apply ABC
        updateE(g);     //update electric field
        
        writeFile(g);   //save file
    }

    end = clock();
    cpu_time_used = ( (double)(end-start) )/CLOCKS_PER_SEC;
	printf("Program Running Time = %.2e s.\n", cpu_time_used);

    return 0;
}
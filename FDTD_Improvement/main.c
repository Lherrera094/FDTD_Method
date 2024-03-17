/*TFSF Boundary: FDTD method for 1D code
TFSF boundary between hy[49] and ez[50] and 
dielectric material starting at ez[100]*/

#include "fdtd1.h"
#include <math.h>
#include <time.h>

void writeFile(Grid *grid, int filenumber){
    char filename[100];
    sprintf(filename, "data/time=%d.csv", filenumber);

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
    double imp0 = 367.73;   //Impedance in vacuum
    int mm, count;                 

    ALLOC_1D(g, 1, Grid);   //Allocates in memmory the space for pointer to structure g

    SizeX = 200;            //Size of the spatial grid
    MaxTime = 250;          //Simulation time
    Cdtds = 1.0;            //Courant number

    ALLOC_1D(g->ez, SizeX, double);
    ALLOC_1D(g->hy, SizeX, double);

    //Do time stepping
    for(Time = 0; Time < MaxTime; Time++){

        // Update the magnetic field
        for(mm = 0; mm < SizeX - 1; mm++){
            Hy(mm) = Hy(mm) + ( (Ez(mm+1) - Ez(mm))/imp0 );
        }//end for magnetic field

        //Update electric field
        for(mm = 1; mm < SizeX; mm++){
            Ez(mm) = Ez(mm) + ( imp0*(Hy(mm) - Hy(mm-1)) );
        }//End for electric field 

        //correction for Ez adjacent to TFSF boundary
        Ez(0) = exp( - (Time - 30.) * (Time - 30.)/100.);

        //printf("%g \n", ez[50]);
        writeFile(g, count);

        count += 1;

    }//end for

    end = clock();
    cpu_time_used = ( (double)(end-start) )/CLOCKS_PER_SEC;
	printf("Program Running Time = %.2e s.\n", cpu_time_used);

    return 0;
}
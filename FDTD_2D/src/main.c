/*TMz simulation with Ricker source at center of Grid*/

#include "fdtd-alloc1.h"
#include "fdtd-macros-tmz.h"
#include "fdtd-proto1.h"
#include "ezinc.h"
#include <time.h>
#include <hdf5.h>

int main(){

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    hid_t file_id, group_id, dataset_id, dataspace_id;
    herr_t status;

    /*Initialize the HDF5 library*/
    status = H5open();
    if( status < 0){
        fprintf(stderr, "Error: Unable to initialize the HDF5 library.");
        return EXIT_FAILURE;
    }else{
        fprintf("HDF5 library initialized. \n");
    }

    /*Create new HDF5*/
    file_id = H5Fcreate(FILENAME, HF5_ACC_TRUNC, H5P_DEFAULT, H5P_DEFALT);
    if( file_id < 0){
        fprintf(stderr, "Error: Unable to create HDF5 file.");
        return EXIT_FAILURE;
    }else{
        fprintf("HDF5 file created. \n");
    }
    
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
        
        snapshot2d(g);
    }//end of time stepping

    end = clock();
    cpu_time_used = ( (double)(end-start) )/CLOCKS_PER_SEC;
	printf("Program Running Time = %.2e s.\n", cpu_time_used);

    return 0;
}

#include "hdf5_savedata.h"

void createDataspace(){

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

}

void saveGroup(Grid *g){

    

}

void savegrid(Grid *g){



}


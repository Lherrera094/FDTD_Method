#include <stdio.h>
#include <stdlib.h>
#include "fdtd-macros-tmz.h"

static int temporalStride = -2, frame = 0, startTime,
    startNodeX, endNodeX, spatialStrideX,
    startNodeY, endNodeY, spatialStrideY; 
static char basename[80];

void snapshotInit2d(Grid *g){
    int choice;
    printf("Do you want 2D snapshots? (1=yes, 0-no)");
    scanf("%d", &choice);
    
    if(choice == 0){
        temporalStride = -1;
        return;
    }

    printf("Duration of Simulation is %d steps. \n", MaxTime);
    
    printf("Enter start time and temporal stride: ");
    scanf(" %d %d", &startTime, &temporalStride);

    printf("In x direction grid has %d total nodes "
            "(ranging from 0 to %d).\n", SizeX, SizeX-1);

    printf("Enter first node, last node, spatial stride: ");
}
#include <stdio.h>
#include <stdlib.h>
#include "fdtd-macros-tmz.h"

static int temporalStride = -2, frame = 0, startTime,
    startNodeX, endNodeX, spatialStrideX,
    startNodeY, endNodeY, spatialStrideY; 
static char basename[80];

void snapshotInit2d(Grid *g){
    int choice;
    printf("Do you want 2D snapshots? (1=yes, 0=no)");
    scanf("%d", &choice);
    
    if(choice == 0){
        temporalStride = -1;
        return;
    }

    printf("Duration of Simulation is %d steps. \n", MaxTime);
    
    printf("Enter start time and temporal stride: ");
    scanf(" %d %d", &startTime, &temporalStride);

    printf("In X direction grid has %d total nodes "
            "(ranging from 0 to %d).\n", SizeX, SizeX-1);

    printf("Enter first node, last node, spatial stride: ");
    scanf(" %d %d %d", &startNodeX, &endNodeX, &spatialStrideX);

    printf("In Y direction grid has %d total nodes "
            "(ranging from 0 to %d).\n", SizeY, SizeY-1);

    printf("Enter first node, last node, spatial stride: ");
    scanf(" %d %d %d", &startNodeY, &endNodeY, &spatialStrideY);

    printf("Enter the base name: ");
    scanf(" %s", basename);

    return;
}

void snapshot2d(Grid *g) {
    int mm, nn;
    float dim1, dim2, temp;
    char filename[100];
    FILE *out;

    /*
    sprintf(filename, "data/time=%d.csv", Time);

    FILE *fptr = fopen(filename, "w");

    if(fptr == NULL){
        printf("Error opening the file. \n");
    }

    fprintf(fptr, "pos, ");
    for(int i = 0; i < SizeY; i++)
        fprintf(fptr, "%d, ", i);

    fprintf(fptr, "\n");

    for(mm = 0; mm < SizeX; mm++){
        fprintf(fptr, "%d, ", mm);
        for(nn = 0; nn < SizeY; nn++){
            fprintf(fptr, "%.5f, ", Ez(mm,nn));
        }
        fprintf(fptr, "\n");
    }
    
    fclose(fptr);
    */

    
    /*ensure temporal stride set to a reasonable value*/
    if(temporalStride == -1){
        return;
    } if(temporalStride < -1){
        fprintf(stderr,
            "snapshot2d: snapshotInit2d must be called befor snapshot. \n"
            "            Temporal stride must be set to positive value. \n");
        exit(-1);
    }

    /*get snapshot if temporal conditions met*/
    if(Time >= startTime && (Time - startTime) % temporalStride){
        sprintf(filename, "data/%s.%d", basename, frame++);
        out = fopen(filename, "wb");

        /*write dimensions to output file --
          express dimensions as floats   */
        dim1 = (endNodeX - startNodeX) / spatialStrideX + 1;
        dim2 = (endNodeY - startNodeY) / spatialStrideY + 1;

        fwrite(&dim1, sizeof(float), 1, out);
        fwrite(&dim2, sizeof(float), 1, out);

        /*Write remaining data*/
        for(nn = endNodeY; nn >= startNodeY; nn -= spatialStrideX)
            for(mm = startNodeX; mm<=endNodeX; mm += spatialStrideX){
                temp = (float)Ez(mm, nn);
                fwrite(&temp, sizeof(float), 1, out);
            }
        
        fclose(out);
    }
    return;
}
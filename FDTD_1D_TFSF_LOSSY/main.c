/*TFSF Boundary: FDTD method for 1D code
TFSF boundary between hy[49] and ez[50] and 
dielectric material starting at ez[100]*/

#include <stdio.h>
#include <math.h>
#include <time.h>

#define SIZE 200
#define LOSS 0.01

void writeFile(double mag[], double elec[], int filenumber){
    char filename[100];
    sprintf(filename, "data/time=%d.csv", filenumber);

    FILE *fptr = fopen(filename, "w");

    if(fptr == NULL){
        printf("Error opening the file. \n");
    }

    fprintf(fptr, "pos,Magnetic_Field,Electric_Field\n");

    for(int i = 0; i < SIZE-1; i++){
        fprintf(fptr, "%d,%.5f,%.5f\n",i, mag[i], elec[i]);
    }
    fclose(fptr);
}

double source_current(int time){
    return exp(-(time - 30.) * (time-30.) / 100. );
}//end source_current function

int main(){

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    
    double ez[SIZE] = {0.}, hy[SIZE-1] = {0.},  
           ceze[SIZE], cezh[SIZE], imp0 = 376.73;
    int qTime, maxTime = 450, mm;

    /*set electric field update coefficients*/
        for(mm = 0; mm < SIZE; mm++){ /*Free space*/
            if(mm < 100){
                ceze[mm] = 1.0;
                cezh[mm] = imp0;
            } else {                /*Lossy dielectric*/
                ceze[mm] = (1.0 - LOSS) / (1.0 + LOSS);
                cezh[mm] = imp0 / 9.0 / (1.0 + LOSS);
            } 
        }

    //Do time stepping
    for(qTime = 0; qTime < maxTime; qTime++){
        //Now the grid is finished at E node.

        // Update the magnetic field
        for(mm = 0; mm < SIZE - 1; mm++){
            hy[mm] = hy[mm] + ( (ez[mm+1] - ez[mm])/imp0 );
        }//end for magnetic field

        //correction for the Hy adyacent
        hy[49] += -exp(- (qTime - 30.)*(qTime - 30.)/100. )/imp0;

        //Simple an Absorbing Boundary Condition for ez[0] and ez[SIZE-1]
        ez[0] = ez[1];

        //Update electric field
        for(mm = 1; mm < SIZE; mm++){
            ez[mm] = ceze[mm]*ez[mm] + ( cezh[mm]*(hy[mm] - hy[mm-1]) );
        }//End for electric field 

        //correction for Ez adjacent to TFSF boundary
        ez[50] += exp( - (qTime +0.5 - (-0.5) - 30.) * 
                         (qTime +0.5 - (-0.5) - 30.)/100.);

        //printf("%g \n", ez[50]);
        writeFile(hy, ez, qTime);

    }//end for

    end = clock();
    cpu_time_used = ( (double)(end-start) )/CLOCKS_PER_SEC;
	printf("Program Running Time = %.2e s.\n", cpu_time_used);

    return 0;
}
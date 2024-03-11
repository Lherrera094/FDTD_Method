/*Bare-Bones Simulation: FDTD method for 1D code*/

#include <stdio.h>
#include <math.h>

#define SIZE 200

void writeFile(double mag[], double elec[], int filenumber){
    char filename[40];
    sprintf(filename, "ABC_data/time=%d.csv", filenumber);

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
    
    int activate_current = 1;
    double ez[SIZE] = {0.}, hy[SIZE] = {0.}, jz[SIZE] = {0.} ,imp0 = 377.0;
    int qTime, maxTime = 250, mm;

    //Do time stepping
    for(qTime = 0; qTime < maxTime; qTime++){
        
        //Applying Absorbing Boundary Condition for hy[Size-1]
        hy[SIZE-1] = hy[SIZE-2];
        // Update the magnetic field
        for(mm = 0; mm < SIZE - 1; mm++){
            hy[mm] = hy[mm] + ( (ez[mm+1] - ez[mm])/imp0 );
        }//end for magnetic field


        //Applying an Absorbing Boundary Condition for ez[0]
        ez[0] = ez[1];
        //Update electric field
        for(mm = 1; mm < SIZE; mm++){
            ez[mm] = ez[mm] + ( imp0*(hy[mm] - hy[mm-1]) );
        }//End for electric field 

        //Habilitates current term in Ampere's Law
        if( activate_current == 1){
            double j = source_current(qTime);
            ez[100] += j;
        }else{
            //Hardwire a source node
            ez[0] += exp(-(qTime - 30.) * (qTime-30.) / 100. );
        }

        //printf("%g \n", ez[50]);
        writeFile(hy, ez, qTime);

    }//end for

    return 0;

}
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#include "omp.h"


void procedureOne(int *Array, int arraySize) {
    omp_set_num_threads(4);
#pragma omp parallel for
    for (int i = 0; i < arraySize; ++i) {
        Array[i] = 0;
    }
}


int generateRandomNumber(int Range) {

    int r = rand() % Range;
    return r;
}

void procedureTwo(int *Array, int arraySize) {

    int temp = (arraySize * 0.1);
    int increment = arraySize / temp;
    omp_set_num_threads(4);

    //Way to do it with the compiler making choices
#pragma omp parallel for
    for (int i = 0; i < arraySize; i += increment) {
        Array[i] = 1;
    }


    //This method was slower, even though we allocated specific segments to each thread
    /*
     int sectionAmount = arraySize / 4;



     //Since we are forcing only 4 threads, we will have four sections this is one way to do it

 #pragma omp parallel
     {
 #pragma omp sections
         {
 #pragma omp section
             {
                 for (int i = 0; i <sectionAmount ; i += increment) {
                     Array[i] = 1;
                 }
             }
 #pragma omp section
             {
                 for (int i = sectionAmount; i <2*sectionAmount ;  i += increment) {
                     Array[i] = 1;
                 }
             }
 #pragma omp section
             {
                 for (int i = 2*sectionAmount; i <3*sectionAmount ;  i += increment) {
                     Array[i] = 1;
                 }
             }
 #pragma omp section
             {
                 for (int i = 3*sectionAmount; i <4*sectionAmount ;  i += increment) {
                     Array[i] = 1;
                 }
             }
         }

     }
     */


}


int *getCoord(int dimension, const int *dimensionArray, int offset) {

    int *coord;
    int temp = offset;
    coord = malloc(dimension * sizeof(int));

    for (int i = dimension - 1; i >= 0; i--) {
        coord[i] = temp % dimensionArray[i];
        temp = temp / dimensionArray[i];
    }

    return coord;

}

void procedureThree(int *Array, int ArraySize, const int *dimensionArray, int Dimension) {

    int noOfSamples = ArraySize * 0.05;

    omp_set_num_threads(4);


    int *tempArray;


    for (int i = 0; i < noOfSamples; ++i) {
        int k = generateRandomNumber(ArraySize);
        printf("\nValue %d in array is: %d at co-ordinates: ", k, Array[k]);
        tempArray = getCoord(Dimension, dimensionArray, k);

        for (int j = 0; j < Dimension; j++) {
            printf("\t%d", tempArray[j]);
        }
    }


    /*
#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            {
                int *tempArray;
                for (int i = 0; i < sectionAmount; ++i) {
                    int k = generateRandomNumber(ArraySize);
                    printf("\nValue %d in array: %d at co-ordinates: ", k, Array[k]);
                    tempArray = getCoord(Dimension, dimensionArray, k);

                    for (int j = 0; j < Dimension; j++) {
                        printf("\t%d", tempArray[j]);
                    }
                }
            }
#pragma omp section
            {
                int *tempArray;
                for (int i = sectionAmount; i < sectionAmount*2; ++i) {
                    int k = generateRandomNumber(ArraySize);
                    printf("\nValue %d in array: %d at co-ordinates: ", k, Array[k]);
                    tempArray = getCoord(Dimension, dimensionArray, k);

                    for (int j = 0; j < Dimension; j++) {
                        printf("\t%d", tempArray[j]);
                    }
                }
            }
#pragma omp section
            {
                int *tempArray;
                for (int i = 2*sectionAmount; i < 3*sectionAmount; ++i) {
                    int k = generateRandomNumber(ArraySize);
                    printf("\nValue %d in array: %d at co-ordinates: ", k, Array[k]);
                    tempArray = getCoord(Dimension, dimensionArray, k);

                    for (int j = 0; j < Dimension; j++) {
                        printf("\t%d", tempArray[j]);
                    }
                }
            }
#pragma omp section
            {
                int *tempArray;
                for (int i = 3*sectionAmount; i < 4*sectionAmount; ++i) {
                    int k = generateRandomNumber(ArraySize);
                    printf("\nValue %d in array: %d at co-ordinates: ", k, Array[k]);
                    tempArray = getCoord(Dimension, dimensionArray, k);

                    for (int j = 0; j < Dimension; j++) {
                        printf("\t%d", tempArray[j]);
                    }
                }
            }
        }

    }
*/



}


int main(void) {

    srand(time(NULL));

    int numberOfDimensions;
    printf("Please enter the number of Dimensions: ");
    scanf("%d", &numberOfDimensions);


    printf("Please enter number of elements in array: ");

    int *dimensionElementArray;

    dimensionElementArray = malloc(numberOfDimensions * sizeof(int));


    for (int i = 0; i < numberOfDimensions; i++) {
        scanf("%d", &dimensionElementArray[i]);
    }

    int totalSize = 1;

    for (int i = 0; i < numberOfDimensions; i++) {
        printf("%d\t", dimensionElementArray[i]);
        totalSize = totalSize * dimensionElementArray[i];
    }

    printf("\n%d\n", totalSize);

    int *mainArray;

    mainArray = (int *) malloc(totalSize * sizeof(int));


    double starttime = omp_get_wtime();

    procedureOne(mainArray, totalSize);
    procedureTwo(mainArray, totalSize);
    procedureThree(mainArray, totalSize, dimensionElementArray, numberOfDimensions);


    double endtime = omp_get_wtime();
    double finalTime = endtime - starttime;


    printf("\n");


    int count = 0;
    for (int i = 0; i < totalSize; ++i) {
        if (mainArray[i] == 1) {
            count++;
        }
    }


    printf("\nTime taken for all three procedures to complete tasks: %lf\n", finalTime);
    printf("\nTotal elements made equal to 1: %d\n", count);


}
















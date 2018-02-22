#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void procedureOne(int *Array, int oneDimArraySize) {
    for (int i = 0; i < oneDimArraySize; ++i) {
        Array[i] = 0;
    }
}


int generateRandomNumber(int Range) {

    int randomNumber = rand() % Range;
    return randomNumber;
}


void procedureTwo(int *Array, int oneDimArraySize) {

    int temp = (oneDimArraySize / 10);
    int increment = 0;
    if (temp > 0) {
        increment = oneDimArraySize / temp;
    } else {

        increment = 1;
    }


    for (int i = 0; i < oneDimArraySize; i += increment) {
        Array[i] = 1;
    }
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

void procedureThree(int *Array, int oneDimArraySize, const int *dimensionArray, int Dimension) {

    int noOfSamples = oneDimArraySize * 0.05;

    int *tempArray;
    int *holderArray;
    holderArray = malloc(noOfSamples * sizeof(int));


    for (int i = 0; i < noOfSamples; ++i) {


        int k = generateRandomNumber(oneDimArraySize);


        for (int l = 0; l < noOfSamples; ++l) {
            if (holderArray[l] == k) {
                k = generateRandomNumber(oneDimArraySize);
            }

        }
        holderArray[i] = k;

        printf("\nValue %d in array is: %d at co-ordinates: ", k, Array[k]);
        tempArray = getCoord(Dimension, dimensionArray, k);

        for (int j = 0; j < Dimension; j++) {
            printf("\t%d", tempArray[j]);
        }
    }
}


int main(void) {


    int numberOfDimensions;
    printf("Please enter the number of Dimensions or '-1' to quit: ");
    scanf("%d", &numberOfDimensions);


    while (numberOfDimensions != -1) {

        int *dimensionElementArray;

        dimensionElementArray = (int *) malloc(numberOfDimensions * sizeof(int));

        printf("Please enter the bounds in each dimension of the mapped 1D array:\n");
        for (int i = 0; i < numberOfDimensions; i++) {
            scanf("%d", &dimensionElementArray[i]);
        }

        int totalSize = 1;

        for (int i = 0; i < numberOfDimensions; i++) {
            printf("%d\t", dimensionElementArray[i]);
            totalSize = totalSize * dimensionElementArray[i];
        }

        printf("\nThe total number of elements the 1D array is: %d\n", totalSize);

        int *mainArray;

        mainArray = (int *) malloc(totalSize * sizeof(int));

        srand(time(NULL));


        procedureOne(mainArray, totalSize);
        procedureTwo(mainArray, totalSize);
        procedureThree(mainArray, totalSize, dimensionElementArray, numberOfDimensions);


        printf("\n");


        int count = 0;
        for (int i = 0; i < totalSize; ++i) {
            if (mainArray[i] == 1) {
                count++;
            }
        }

        printf("\nTotal elements made equal to 1: %d\n", count);
        printf("\n");


        free(dimensionElementArray);
        free(mainArray);

        printf("Please enter the number of Dimensions or '-1' to quit: ");
        scanf("%d", &numberOfDimensions);


    }


    return 0;


}




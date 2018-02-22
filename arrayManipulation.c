#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>


void populateArrayWithZeroes(int *Array, int oneDimArraySize) {
    for (int i = 0; i < oneDimArraySize; ++i) {
        Array[i] = 0;
    }
}


int generateRandomNumber(int oneDimArraySize) {

    int randomNumber = rand() % oneDimArraySize;
    return randomNumber;
}


void uniformPopulationOfOnes(int *Array, int oneDimArraySize) {

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


int *getCoordinate(int kDimension, const int *arrayOfBoundDimensions, int offset) {

    int *coordinate;
    int temp = offset;
    coordinate = malloc(kDimension * sizeof(int));

    for (int i = kDimension - 1; i >= 0; i--) {
        coordinate[i] = temp % arrayOfBoundDimensions[i];
        temp = temp / arrayOfBoundDimensions[i];
    }

    return coordinate;

}


void printUniformRandomCoordinates(int *Array, int oneDimArraySize, const int *arrayOfBoundDimensions, int kDimension) {

    int noOfCoordinates = oneDimArraySize * 0.05;

    int *tempArray;
    int *holderArray;
    holderArray = malloc(noOfCoordinates * sizeof(int));

    for (int i = 0; i < noOfCoordinates; ++i) {
        int randomNumber = generateRandomNumber(oneDimArraySize);

        for (int l = 0; l < noOfCoordinates; ++l) {

            if (holderArray[l] == randomNumber) {
                randomNumber = generateRandomNumber(oneDimArraySize);
            }
        }
        holderArray[i] = randomNumber;
        printf("\nValue %d in array is: %d at co-ordinates: ", randomNumber, Array[randomNumber]);
        tempArray = getCoordinate(kDimension, arrayOfBoundDimensions, randomNumber);

        for (int j = 0; j < kDimension; j++) {
            printf("\t%d", tempArray[j]);
        }
    }
}


int main(void) {


    int numberOfDimensions;
    printf("Please enter the number of Dimensions or '-1' to quit: ");
    scanf("%d", &numberOfDimensions);


    while (numberOfDimensions != -1) {

        int *arrayOfBoundDimensions;

        arrayOfBoundDimensions = (int *) malloc(numberOfDimensions * sizeof(int));

        printf("Please enter the bounds in each dimension of the mapped 1D array:\n");
        for (int i = 0; i < numberOfDimensions; i++) {
            scanf("%d", &arrayOfBoundDimensions[i]);
        }

        int totalSizeOf1Darray = 1;

        for (int i = 0; i < numberOfDimensions; i++) {
            printf("%d\t", arrayOfBoundDimensions[i]);
            totalSizeOf1Darray = totalSizeOf1Darray * arrayOfBoundDimensions[i];
        }

        printf("\nThe total number of elements the 1D array is: %d\n", totalSizeOf1Darray);

        int *mapped1DArray;

        mapped1DArray = (int *) malloc(totalSizeOf1Darray * sizeof(int));

        srand(time(NULL));


        populateArrayWithZeroes(mapped1DArray, totalSizeOf1Darray);
        uniformPopulationOfOnes(mapped1DArray, totalSizeOf1Darray);
        printUniformRandomCoordinates(mapped1DArray, totalSizeOf1Darray, arrayOfBoundDimensions,
                                      numberOfDimensions);


        printf("\n");


        int count = 0;
        for (int i = 0; i < totalSizeOf1Darray; ++i) {
            if (mapped1DArray[i] == 1) {
                count++;
            }
        }

        printf("\nTotal elements made equal to 1: %d\n", count);
        printf("\n");


        free(arrayOfBoundDimensions);

        free(mapped1DArray);

        printf("Please enter the number of Dimensions or '-1' to quit: ");
        scanf("%d", &numberOfDimensions);


    }


    return 0;


}




//
// Created by sailen on 2018/02/19.
//

#include <stdlib.h>
#include <stdio.h>


int *getCoord(int dimension, const int * dimensionArray, int offset) {

    int *coord;
    int temp =offset;
    coord = malloc(dimension * sizeof(int));

    for (int i = dimension-1; i >= 0 ; i--){
        coord[i] = temp%dimensionArray[i];

        temp =  temp/dimensionArray[i];
    }


    for (int i = 0; i<dimension; i++){
        printf("\t%d",coord[i]);
    }

    return coord;

}


int main() {

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

    int * mainArray;

    mainArray =(int*)malloc(totalSize * sizeof(int));

    printf("%d\n", mainArray[20]);

    int offset = 20;

    int* coord = malloc(numberOfDimensions* sizeof(int));

     coord = getCoord(numberOfDimensions, dimensionElementArray, offset);


    free(mainArray);
    free(dimensionElementArray);
    free(coord);


}
































































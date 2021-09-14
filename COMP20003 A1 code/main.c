#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "dataset.h"
#include "polygon.h"
#include "split.h"
#include "region.h"

int main(int argc, char **argv){
    //variables
    watchtower_t **datasetArray;
    halfedge_t **edgeArray, **facesArray;
    int datasetArraySize, edgeArraySize, biggestEdgeIndex, edgeArrayMemSize, faceIndexes;

    readFile1(argv[1], &datasetArray, &datasetArraySize);
    readFile2(argv[2], &edgeArray, &edgeArraySize, &edgeArrayMemSize);
    split(&edgeArray, &edgeArraySize, &biggestEdgeIndex, &edgeArrayMemSize, &faceIndexes, &facesArray);
    watchTowerRegion(argv[3], &datasetArray, &datasetArraySize, &facesArray, &faceIndexes);

    //free all allocated memory
    free(facesArray);
    freeDatasetArray(&datasetArray, &datasetArraySize);
    freeEdgeArray(&edgeArray, &edgeArraySize); 
    return 0;
}


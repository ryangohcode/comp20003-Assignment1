#ifndef REGION_H
#define REGION_H

#include "dataset.h"
#include "polygon.h"

//This function prints out the watchertowers belonging in each face into the file
void watchTowerRegion(char* file3, watchtower_t*** datasetArray, int* datasetArraySize, halfedge_t*** facesArray, int* faceIndexes);

//This function checks if the point is within the edge. It returns 1 if it is and 0 if it is not.
int checkInside(coordinates_t point, halfedge_t edge);

#endif

#ifndef SPLIT_H
#define SPLIT_H

#include "polygon.h"

//This function checks if the point is within the edge. It returns 1 if it is and 0 if it is not.
int checkInside(coordinates_t point, halfedge_t edge);

//This function splits the faces
void split(halfedge_t*** edgeArray, int* edgeArraySize, int* biggestEdgeIndex, int* edgeArrayMemSize, int* faceIndexes, halfedge_t*** faceArray);

//This function loops around the new face and updates all the faceIndexes
void updateFace(halfedge_t* edge);

//This function prints the order of the polygons by looking at the next pointer
void printFace(halfedge_t* edge);

//These function prints the order of the polygons by looking at the previous pointer
void printFaceBackwards(halfedge_t* edge);

//This function prints the faceIndex of the halfedges in faceArray
void printFaceArray(halfedge_t*** faceArray ,int* faceIndexes);

#endif

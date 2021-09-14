#ifndef POLY_H
#define POLY_H

#include "dataset.h"

#define INITIALSIZE 5

//This struct stores details for each halfedge
typedef struct halfedge halfedge_t;
struct halfedge {
    coordinates_t start;
    coordinates_t end;
    halfedge_t *nextHalfEdge;
    halfedge_t *prevHalfEdge;
    halfedge_t *oppHalfEdge;
    int faceIndex;
    int edgeIndex;
};

//this function reads in the second argument file and constructs the initial polygon
void readFile2(char* file2Name, halfedge_t*** edgeArray, int* edgeArraySize, int* edgeArrayMemSize);

//This function prints out the initial polygon edges. This is purely for testing purposes and not called.
void printEdgeArray(halfedge_t*** edgeArray ,int* edgeArraySize);

//this function frees the array of pointers to structs
void freeEdgeArray(halfedge_t*** edgeArray ,int* edgeArraySize);

//this function is for testing purposes
void printVisual(halfedge_t*** edgeArray ,int* edgeArraySize);
#endif

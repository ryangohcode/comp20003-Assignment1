#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "polygon.h"

//this function reads in the second argument file and constructs the initial polygon
void readFile2(char* file2Name, halfedge_t*** edgeArray, int* edgeArraySize, int* edgeArrayMemSize){
    //variables
    double x, y, prevX, prevY;
    int numRow = 0;
    int arraySize = INITIALSIZE;

    //open polygon.txt, allocate memory for polygon
    FILE *file = fopen(file2Name, "r");
    assert(file);
    (*edgeArray) = (halfedge_t**)malloc(sizeof(halfedge_t*)*arraySize);
    assert(*edgeArray);
    while(1){
        if(numRow<arraySize){
            if(fscanf(file, "%lf %lf" , &x, &y)==EOF){
                break;
            }
            if(numRow>0){
                //create edges
                (*edgeArray)[numRow-1] = (halfedge_t*)malloc(sizeof(halfedge_t));
                assert((*edgeArray)[numRow-1]);
                (*edgeArray)[numRow-1]->start.x = prevX;
                (*edgeArray)[numRow-1]->start.y = prevY;
                (*edgeArray)[numRow-1]->end.x = x;
                (*edgeArray)[numRow-1]->end.y = y;
                (*edgeArray)[numRow-1]->oppHalfEdge = NULL;
                (*edgeArray)[numRow-1]->faceIndex = 0;
                (*edgeArray)[numRow-1]->edgeIndex = numRow-1;

                if(numRow>1){
                    (*edgeArray)[numRow-1]->prevHalfEdge = (*edgeArray)[numRow-2];
                    (*edgeArray)[numRow-2]->nextHalfEdge = (*edgeArray)[numRow-1];
                }
            }
            prevX = x;
            prevY = y;
            numRow++;
        }
        else{
            //realloc
            arraySize = arraySize*2;
            (*edgeArray) = (halfedge_t**)realloc((*edgeArray),arraySize*sizeof(halfedge_t*));
            assert(*edgeArray);
        }
    }
    //link to first edge
    (*edgeArray)[numRow-1] = (halfedge_t*)malloc(sizeof(halfedge_t));
    assert((*edgeArray)[numRow-1]);
    (*edgeArray)[numRow-1]->start.x = prevX;
    (*edgeArray)[numRow-1]->start.y = prevY;
    (*edgeArray)[numRow-1]->end.x = (*edgeArray)[0]->start.x;
    (*edgeArray)[numRow-1]->end.y = (*edgeArray)[0]->start.y;
    (*edgeArray)[numRow-1]->oppHalfEdge = NULL;
    (*edgeArray)[numRow-1]->faceIndex = 0;
    (*edgeArray)[numRow-1]->edgeIndex = numRow-1;
    (*edgeArray)[numRow-1]->prevHalfEdge = (*edgeArray)[numRow-2];
    (*edgeArray)[numRow-2]->nextHalfEdge = (*edgeArray)[numRow-1];

    //link pointers for first and last points edges
    (*edgeArray)[0]->prevHalfEdge = (*edgeArray)[numRow-1];
    (*edgeArray)[numRow-1]->nextHalfEdge = (*edgeArray)[0];
    *edgeArraySize = numRow;
    *edgeArrayMemSize = arraySize;
    fclose(file);
}

//This function prints out the initial polygon edges. This is purely for testing purposes and not called.
void printEdgeArray(halfedge_t*** edgeArray ,int* edgeArraySize){
    for(int i=0; i<*edgeArraySize; i++){
        printf("edge %d: start %lf %lf\n", i, (*edgeArray)[i]->start.x, (*edgeArray)[i]->start.y);
        printf("edge %d: end %lf %lf\n", i, (*edgeArray)[i]->end.x, (*edgeArray)[i]->end.y);
        printf("edge %d: Index of face-%d, Index of edge %d\n", i, (*edgeArray)[i]->faceIndex, (*edgeArray)[i]->edgeIndex);
        printf("edge %d: previous halfEdge index: %d\n", i, (*edgeArray)[i]->prevHalfEdge->edgeIndex);
        printf("edge %d: next halfEdge index: %d\n", i, (*edgeArray)[i]->nextHalfEdge->edgeIndex);
        if((*edgeArray)[i]->oppHalfEdge){
            printf("edge %d: opp halfEdge index: %d\n", i, (*edgeArray)[i]->oppHalfEdge->edgeIndex);
        }
        printf("\n");
    }
}

//this function frees the array of pointers to structs
void freeEdgeArray(halfedge_t*** edgeArray ,int* edgeArraySize){
    for(int i=0; i<*edgeArraySize; i++){
        free((*edgeArray)[i]);
    }
    free(*edgeArray);
}

void printVisual(halfedge_t*** edgeArray ,int* edgeArraySize){
    for(int i=0; i<*edgeArraySize; i++){
        printf("@E%d %lf %lf %lf %lf\n", (*edgeArray)[i]->faceIndex, (*edgeArray)[i]->start.x, (*edgeArray)[i]->start.y, (*edgeArray)[i]->end.x, (*edgeArray)[i]->end.y);
    }
}


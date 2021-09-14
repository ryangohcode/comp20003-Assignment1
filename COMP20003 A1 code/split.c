#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "split.h"

void split(halfedge_t*** edgeArray, int* edgeArraySize, int* biggestEdgeIndex, int* edgeArrayMemSize, int* faceIndexes, halfedge_t*** faceArray){
    //variables
    int startSplitIndex, endSplitIndex, faceArrayMemSize;
    coordinates_t midStartEdgeCoords, midEndEdgeCoords, gPoint, endStartEdge, startEndEdge;
    halfedge_t *startSplitEdge, *endSplitEdge, *startSplitEdgeNext, *endSplitEdgePrev, *newSplitEdge, *createEdge1, *createEdge2;

    //initialise
    faceArrayMemSize = INITIALSIZE;
    *faceIndexes = 0;
    *biggestEdgeIndex = *edgeArraySize-1;

    //malloc faceArray
    (*faceArray)=(halfedge_t**)malloc(sizeof(halfedge_t*)*faceArrayMemSize);
    assert(*faceArray);
    while(scanf("%d %d", &startSplitIndex, &endSplitIndex)==2){

        //Make sure there is still 6 spaces left in malloced array otherwise realloc
        if(edgeArrayMemSize-edgeArraySize<=6){
            //malloc
            *edgeArrayMemSize = (*edgeArrayMemSize)*2;
            (*edgeArray) = (halfedge_t**)realloc((*edgeArray),(*edgeArrayMemSize)*sizeof(halfedge_t*));
            assert(*edgeArray);
        }

        //find startSplitEdge and endSplitEdge
        for(int i=0; i<*edgeArraySize; i++){
            if((*edgeArray)[i]->edgeIndex==startSplitIndex){
                startSplitEdge=(*edgeArray)[i];
                break;
            }
        }
        for(int i=0; i<*edgeArraySize; i++){
            if((*edgeArray)[i]->edgeIndex==endSplitIndex){
                endSplitEdge=(*edgeArray)[i];
                break;
            }
        }        

        //check if point g is inside the edge. if not, swap to opposite side. 
        midStartEdgeCoords.x = (startSplitEdge->start.x + startSplitEdge->end.x)/2;
        midStartEdgeCoords.y = (startSplitEdge->start.y + startSplitEdge->end.y)/2;
        midEndEdgeCoords.x = (endSplitEdge->start.x + endSplitEdge->end.x)/2;
        midEndEdgeCoords.y = (endSplitEdge->start.y + endSplitEdge->end.y)/2;
        gPoint.x = (midStartEdgeCoords.x+midEndEdgeCoords.x)/2;
        gPoint.y = (midStartEdgeCoords.y+midEndEdgeCoords.y)/2;

        if(!checkInside(gPoint, *startSplitEdge)){
            if(startSplitEdge->oppHalfEdge==NULL){
                printf("Error swapping\n");
            }
            else{
                startSplitEdge=startSplitEdge->oppHalfEdge;
            }
            
        }
        if(!checkInside(gPoint, *endSplitEdge)){
            if(endSplitEdge->oppHalfEdge==NULL){
                printf("Error swapping\n");
            }
            else{
                endSplitEdge=endSplitEdge->oppHalfEdge;
            }
        }
        
        //store end point of startSplitEdge and start point of endSplitEdge
        endStartEdge = startSplitEdge->end;
        startEndEdge = endSplitEdge->start;

        //update end point of startSplitEdge and start point of endSplitEdge
        startSplitEdge->end = midStartEdgeCoords;
        endSplitEdge->start = midEndEdgeCoords;

        //update their opp half if they exist as well   
        if(startSplitEdge->oppHalfEdge!=NULL){
            startSplitEdge->oppHalfEdge->start = midStartEdgeCoords;
        }
        if(endSplitEdge->oppHalfEdge!=NULL){
            endSplitEdge->oppHalfEdge->end = midEndEdgeCoords;
        }

        //add new edge from split
        *edgeArraySize = *edgeArraySize+1;
        (*edgeArray)[*edgeArraySize-1] = (halfedge_t*)malloc(sizeof(halfedge_t));
        assert((*edgeArray)[*edgeArraySize-1]);
        (*edgeArray)[*edgeArraySize-1]->start = midStartEdgeCoords;
        (*edgeArray)[*edgeArraySize-1]->end = midEndEdgeCoords;
        (*edgeArray)[*edgeArraySize-1]->edgeIndex = *biggestEdgeIndex+1;
        *biggestEdgeIndex = *biggestEdgeIndex + 1;

        //store pointers
        startSplitEdgeNext = startSplitEdge->nextHalfEdge;
        endSplitEdgePrev = endSplitEdge->prevHalfEdge;

        //set face
        (*edgeArray)[*edgeArraySize-1]->faceIndex = startSplitEdge->faceIndex;

        //connect pointers
        (*edgeArray)[*edgeArraySize-1]->nextHalfEdge = endSplitEdge;  
        (*edgeArray)[*edgeArraySize-1]->prevHalfEdge = startSplitEdge;  
        endSplitEdge->prevHalfEdge = (*edgeArray)[*edgeArraySize-1];
        startSplitEdge ->nextHalfEdge = (*edgeArray)[*edgeArraySize-1];

        //Adjacent edges anticlockwise case
        if(startSplitEdge->prevHalfEdge==endSplitEdge){
            endSplitEdge->nextHalfEdge = startSplitEdge;
            startSplitEdge->prevHalfEdge = endSplitEdge;
        }
        
        //create opposite of splitedge
        *edgeArraySize = *edgeArraySize+1;
        (*edgeArray)[*edgeArraySize-1] = (halfedge_t*)malloc(sizeof(halfedge_t));
        assert((*edgeArray)[*edgeArraySize-1]);
        newSplitEdge = (*edgeArray)[*edgeArraySize-1];
        (*edgeArray)[*edgeArraySize-1]->start = midEndEdgeCoords;
        (*edgeArray)[*edgeArraySize-1]->end = midStartEdgeCoords;
        (*edgeArray)[*edgeArraySize-1]->edgeIndex = *biggestEdgeIndex;
        (*edgeArray)[*edgeArraySize-1]->oppHalfEdge = (*edgeArray)[*edgeArraySize-2]; 
        (*edgeArray)[*edgeArraySize-2]->oppHalfEdge = (*edgeArray)[*edgeArraySize-1];
        (*edgeArray)[*edgeArraySize-1]->faceIndex = *faceIndexes+1; 

        //create createEdge1
        *edgeArraySize = *edgeArraySize+1;
        (*edgeArray)[*edgeArraySize-1] = (halfedge_t*)malloc(sizeof(halfedge_t)); 
        assert((*edgeArray)[*edgeArraySize-1]);
        createEdge1=(*edgeArray)[*edgeArraySize-1];
        (*edgeArray)[*edgeArraySize-1]->start = midStartEdgeCoords;
        (*edgeArray)[*edgeArraySize-1]->end = endStartEdge;
        (*edgeArray)[*edgeArraySize-1]->edgeIndex = *biggestEdgeIndex+1;
        *biggestEdgeIndex = *biggestEdgeIndex + 1;
        
        //connect pointers for edge1
        createEdge1->prevHalfEdge = newSplitEdge;
        newSplitEdge->nextHalfEdge = createEdge1;
        (*edgeArray)[*edgeArraySize-1]->faceIndex = (*edgeArray)[*edgeArraySize-1]->prevHalfEdge->faceIndex;
        
        //Update startEdge's opposite halfedge if it exists
        if(startSplitEdge->oppHalfEdge!=NULL){
            //create new halfedge
            *edgeArraySize = *edgeArraySize+1;
            (*edgeArray)[*edgeArraySize-1] = (halfedge_t*)malloc(sizeof(halfedge_t)); 
            assert((*edgeArray)[*edgeArraySize-1]);
            (*edgeArray)[*edgeArraySize-1]->oppHalfEdge = createEdge1;
            createEdge1->oppHalfEdge = (*edgeArray)[*edgeArraySize-1];
            (*edgeArray)[*edgeArraySize-1]->start = createEdge1->end;
            (*edgeArray)[*edgeArraySize-1]->end = createEdge1->start;
            (*edgeArray)[*edgeArraySize-1]->edgeIndex = createEdge1->edgeIndex;

            //handle pointers
            (*edgeArray)[*edgeArraySize-1]->nextHalfEdge = startSplitEdge->oppHalfEdge;
            (*edgeArray)[*edgeArraySize-1]->faceIndex = startSplitEdge->oppHalfEdge->faceIndex;
            (*edgeArray)[*edgeArraySize-1]->prevHalfEdge = startSplitEdge->oppHalfEdge->prevHalfEdge;
            (*edgeArray)[*edgeArraySize-1]->nextHalfEdge->prevHalfEdge = (*edgeArray)[*edgeArraySize-1];
            (*edgeArray)[*edgeArraySize-1]->prevHalfEdge->nextHalfEdge = (*edgeArray)[*edgeArraySize-1];
        }
        
        //create other new edge
        *edgeArraySize = *edgeArraySize+1;
        (*edgeArray)[*edgeArraySize-1] = (halfedge_t*)malloc(sizeof(halfedge_t)); 
        assert((*edgeArray)[*edgeArraySize-1]);
        createEdge2 = (*edgeArray)[*edgeArraySize-1];
        (*edgeArray)[*edgeArraySize-1]->start = startEndEdge;
        (*edgeArray)[*edgeArraySize-1]->end = midEndEdgeCoords;
        (*edgeArray)[*edgeArraySize-1]->edgeIndex = *biggestEdgeIndex+1;
        *biggestEdgeIndex = *biggestEdgeIndex + 1;
        
        //connect pointers to createEdge2
        createEdge2->nextHalfEdge = newSplitEdge;
        newSplitEdge->prevHalfEdge = createEdge2;
        (*edgeArray)[*edgeArraySize-1]->faceIndex = newSplitEdge->faceIndex;
        
        //Adjacent edges clockwise case
        if(startSplitEdgeNext==endSplitEdge){ 
            createEdge1->nextHalfEdge = createEdge2;
            createEdge2->prevHalfEdge = createEdge1;
        }
        else{
            createEdge1->nextHalfEdge = startSplitEdgeNext;
            startSplitEdgeNext->prevHalfEdge = createEdge1;
            createEdge2->prevHalfEdge = endSplitEdgePrev;
            endSplitEdgePrev->nextHalfEdge = createEdge2;
        }
        
        //Update endEdge's opposite halfedge if it exists
        if(endSplitEdge->oppHalfEdge!=NULL){
            //create new halfedge
            *edgeArraySize = *edgeArraySize+1;
            (*edgeArray)[*edgeArraySize-1] = (halfedge_t*)malloc(sizeof(halfedge_t)); 
            assert((*edgeArray)[*edgeArraySize-1]);
            (*edgeArray)[*edgeArraySize-1]->oppHalfEdge = createEdge2;
            createEdge2->oppHalfEdge = (*edgeArray)[*edgeArraySize-1];
            (*edgeArray)[*edgeArraySize-1]->start = createEdge2->end;
            (*edgeArray)[*edgeArraySize-1]->end = createEdge2->start;
            (*edgeArray)[*edgeArraySize-1]->edgeIndex = createEdge2->edgeIndex;

            //handle pointers
            (*edgeArray)[*edgeArraySize-1]->nextHalfEdge = endSplitEdge->oppHalfEdge->nextHalfEdge;
            (*edgeArray)[*edgeArraySize-1]->faceIndex = endSplitEdge->oppHalfEdge->faceIndex;
            (*edgeArray)[*edgeArraySize-1]->prevHalfEdge = endSplitEdge->oppHalfEdge;
            (*edgeArray)[*edgeArraySize-1]->nextHalfEdge->prevHalfEdge = (*edgeArray)[*edgeArraySize-1];
            (*edgeArray)[*edgeArraySize-1]->prevHalfEdge->nextHalfEdge = (*edgeArray)[*edgeArraySize-1];
        }
        //update face
        updateFace(newSplitEdge);

        //realloc if faceArray is too small
        if(faceArrayMemSize-*faceIndexes<=1){
            faceArrayMemSize = faceArrayMemSize*2;
            (*faceArray) = (halfedge_t**)realloc((*faceArray),faceArrayMemSize*sizeof(halfedge_t*));
            assert(*edgeArray);
        }
        (*faceArray)[startSplitEdge->faceIndex] = newSplitEdge->oppHalfEdge;
        (*faceArray)[*faceIndexes+1] = newSplitEdge;
        *faceIndexes = *faceIndexes+1;
    }

    //if no split done
    if(!*faceIndexes){
        (*faceArray)[0] = (*edgeArray)[0];
    }
}

//This function checks if the point is within the edge. It returns 1 if it is and 0 if it is not.
int checkInside(coordinates_t point, halfedge_t edge){
    double gradient, intercept, yPredicted, yR;

    //vertical cases
    if((edge.start.x==edge.end.x)&&(edge.start.y>=edge.end.y)){
        if(point.x<=edge.start.x){
            return 1;
        }
    }
    if((edge.start.x==edge.end.x)&&(edge.start.y<=edge.end.y)){
        if(point.x>=edge.start.x){
            return 1;
        }
    }
    if(edge.start.x!=edge.end.x){
        //find gradient then try both test cases
        gradient = (edge.end.y-edge.start.y)/(edge.end.x-edge.start.x);
        intercept = edge.end.y-(gradient*edge.end.x);
        yPredicted = gradient*point.x+intercept;
        yR = point.y-yPredicted;

        //slanted cases
        if((edge.end.x>edge.start.x)&&(yR<=0)){
            return 1;
        }
        if((edge.end.x<edge.start.x)&&(yR>=0)){
            return 1;
        }

        //horizontal cases
        if((edge.end.x==edge.start.x)&&(edge.end.y>=edge.start.y)){
            if(yR<=0){
                return 1;
            }
        }
        if((edge.end.x==edge.start.x)&&(edge.end.y<=edge.start.y)){
            if(yR>=0){
                return 1;
            }
        }
    }
    return 0;
}

//This function loops around the new face and updates all the faceIndexes
void updateFace(halfedge_t* edge){
    int startIndex;

    startIndex = edge->edgeIndex;
    while(edge->nextHalfEdge->edgeIndex!=startIndex){
        edge->nextHalfEdge->faceIndex = edge->faceIndex;
        edge=edge->nextHalfEdge; 
    }
    edge->nextHalfEdge->faceIndex = edge->faceIndex;
}

//This function prints the order of the polygons by looking at the next pointer
void printFace(halfedge_t* edge){
    int startIndex;

    startIndex = edge->edgeIndex;
    while(edge->nextHalfEdge->edgeIndex!=startIndex){
        printf("%d -> ",edge->edgeIndex);
        edge = edge->nextHalfEdge; 
    }
    printf("%d -> %d\n",edge->edgeIndex, startIndex);
}

//These function prints the order of the polygons by looking at the previous pointer
void printFaceBackwards(halfedge_t* edge){
    int startIndex;

    startIndex = edge->edgeIndex;
    while(edge->prevHalfEdge->edgeIndex!=startIndex){
        printf("%d -> ",edge->edgeIndex);
        edge = edge->prevHalfEdge; 
    }
    printf("%d -> %d\n",edge->edgeIndex, startIndex);
}

//This function prints the faceIndex of the halfedges in faceArray
void printFaceArray(halfedge_t*** faceArray ,int* faceIndexes){
    for(int i=0; i<=*faceIndexes; i++){
        printf("%d",(*faceArray)[i]->faceIndex);
    }
}

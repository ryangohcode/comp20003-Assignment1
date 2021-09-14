#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "region.h"

void watchTowerRegion(char* file3, watchtower_t*** datasetArray, int* datasetArraySize, halfedge_t*** facesArray, int* faceIndexes){
    int maxPopulation[*faceIndexes];
    int startIndex;
    halfedge_t* edge;
    int check = 0;

    //Open outfile.txt
    FILE *file = fopen(file3, "w");
    assert(file);

    //Initiallise initial values to 0
    for(int i=0; i<=*faceIndexes;i++){
        maxPopulation[i] = 0;
    }

    //Loop through every watchtower in face[j]
    for(int j=0; j<=*faceIndexes; j++){
        fprintf(file, "%d\n", j);
        for(int i=0; i<*datasetArraySize; i++){
            check = 1;
            edge = (*facesArray)[j];
            startIndex = edge->edgeIndex;
            while(edge->nextHalfEdge->edgeIndex!=startIndex){
                if(checkInside((*datasetArray)[i]->location, *edge)){
                    edge=edge->nextHalfEdge; 
                }
                else{
                    check = 0;
                    break;
                }
            }
            
            //Watchtower is inside face. Add to maxPopulation and print details
            if(checkInside((*datasetArray)[i]->location, *edge)&&check==1){
                maxPopulation[j]=maxPopulation[j]+(*datasetArray)[i]->population;
                fprintf(file, "Watchtower ID: W%s, ",(*datasetArray)[i]->ID);
                fprintf(file, "Postcode: %s, ",(*datasetArray)[i]->postcode);
                fprintf(file, "Population Served: %d, ",(*datasetArray)[i]->population);
                fprintf(file, "Watchtower Point of Contact Name: %s, ",(*datasetArray)[i]->pointOfContact);
                fprintf(file, "x: %lf, ",(*datasetArray)[i]->location.x);
                fprintf(file, "y: %lf\n",(*datasetArray)[i]->location.y);
            }
        }
    }
    for(int j=0; j<=*faceIndexes; j++){
        fprintf(file, "Face %d population served: %d\n", j, maxPopulation[j]);
    }
    fclose(file);
}

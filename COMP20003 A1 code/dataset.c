#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "dataset.h"

//This function reads in the csv file. Assumption: WatchtowerID starts with W
void readFile1(char* file1Name, watchtower_t*** datasetArray, int* datasetArraySize){
    int datasetRows = 0;
    int arraySize = INITIALSIZE;
    char c;

    //Open dataset.csv
    FILE *file = fopen(file1Name, "r");
    assert(file);
    fscanf(file, "Watchtower ID,Postcode,Population Served,Watchtower Point of Contact Name,x,y\n");

    //malloc number of rows
    (*datasetArray)=(watchtower_t**)malloc(sizeof(watchtower_t*)*arraySize);
    assert(*datasetArray);
    while(fscanf(file, "%c" , &c)!=EOF){
        if(arraySize-datasetRows<=1){
            arraySize = arraySize*2;
            (*datasetArray) = (watchtower_t**)realloc((*datasetArray),arraySize*sizeof(watchtower_t*));
            assert(*datasetArray);
        }
        (*datasetArray)[datasetRows] = (watchtower_t*)malloc(sizeof(watchtower_t));
        assert((*datasetArray)[datasetRows]);
        //scan ID
        scanString(&(*datasetArray)[datasetRows]->ID,file);

        //scan postcode
        scanString(&(*datasetArray)[datasetRows]->postcode,file);
        
        //scan population
        fscanf(file, "%d" , &(*datasetArray)[datasetRows]->population);
        fscanf(file, "%c" , &c);
        
        //scan PointOfContact
        scanString(&(*datasetArray)[datasetRows]->pointOfContact,file);

        //scan coorinatesOfWatertower
        fscanf(file, "%lf" , &(*datasetArray)[datasetRows]->location.x);
        fscanf(file, "%c" , &c);
        fscanf(file, "%lf " , &(*datasetArray)[datasetRows]->location.y);

        datasetRows++;
    }
    *datasetArraySize=datasetRows; 
    fclose(file);
}

//This function prints out the list of dataset. This is purely for testing purposes and not called.
void printDatasetArray(watchtower_t*** datasetArray, int* datasetArraySize){
    for(int i=0; i<*datasetArraySize; i++){
        printf("Dataset row %d\n",i);
        printf("ID: %s\n",(*datasetArray)[i]->ID);
        printf("Postcode: %s\n",(*datasetArray)[i]->postcode);
        printf("Population: %d\n",(*datasetArray)[i]->population);
        printf("Point of contact: %s\n",(*datasetArray)[i]->pointOfContact);
        printf("X coordinates: %lf\n",(*datasetArray)[i]->location.x);
        printf("Y coordinates: %lf\n",(*datasetArray)[i]->location.y);
    }
}

//this function frees the array of pointers to structs
void freeDatasetArray(watchtower_t*** datasetArray, int* datasetArraySize){
    for(int i=0; i<*datasetArraySize; i++){
        free((*datasetArray)[i]->ID);
        free((*datasetArray)[i]->postcode);
        free((*datasetArray)[i]->pointOfContact);
        free((*datasetArray)[i]);
    }
    free(*datasetArray);
}

//this function scans in a string from the cvs file and stores it in the first argument
void scanString(char **location, FILE *file){
    char tempArray[MAXIMUMFIELDLENGTH], c;
    for(int i=0; fscanf(file, "%c" , &c)==1; i++){
        if(c==','){
            tempArray[i] = '\0';
            *location=(char*)malloc((i+1)*sizeof(char));
            assert(*location);
            strcpy(*location,tempArray);
            break;
        }
        tempArray[i]=c;
    }
}

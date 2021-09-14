#ifndef DATA_H
#define DATA_H

#define MAXIMUMFIELDLENGTH 129 //128+1 for null byte
#define INITIALSIZE 5

//This struct stores x and y coordinates
typedef struct{
    double x;
    double y;
}coordinates_t;

//This struct stores the details for each watchtower
typedef struct {
    char *ID; 
    char *postcode;
    int population;
    char *pointOfContact;
    coordinates_t location;
}watchtower_t;

//this function reads in the first argument as a file and creates a dynamic array of pointers to watchtower structs.
void readFile1(char* file1Name, watchtower_t*** datasetArray, int* datasetArraySize);

//This function prints out the list of dataset. This is purely for testing purposes and not called.
void printDatasetArray(watchtower_t*** datasetArray, int* datasetArraySize);

//this function frees the array of pointers to structs
void freeDatasetArray(watchtower_t*** datasetArray, int* datasetArraySize);

//this function scans in a string from the cvs file and stores it in the first argument
void scanString(char **location, FILE *file);

#endif

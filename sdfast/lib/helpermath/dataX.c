//
//  dataX.c
//  DarwinSD
//
//  Created by Robert Brothers on 5/23/16.
//  Copyright © 2016 Robert Brothers. All rights reserved.
//

#include "dataX.h"
void extract(char * fname, char * data[NU]) {
    // extract each line from the file and store it in the data array
//    data = (char **)malloc(sizeof(char *)*NU);
    size_t size = 0;
    char * buffer;
    buffer = (char *)malloc(sizeof(char)*size);
    FILE *fid;
    fid = fopen(fname, "r");
    if(fid) {
        for (int i=0; i<NU; i++) {
            getline(&buffer, &size, fid);
            data[i] = (char*)malloc(sizeof(char)*size);
            strcpy(data[i], buffer);
        }
    } else {
        printf("file did not open\n");
    }
    fclose(fid);
    free(buffer);
}

void extractjoints(FILE * fid, body data[NU]) {
    int id;
    double btj[3],itj[3];
    if (fid) {
        printf("working");
    } else {
        printf("broken");
    }
    
    while (!feof(fid)) {
        fscanf(fid,"%d %lf %lf %lf %lf %lf %lf", &id,
               &btj[0], &btj[1], &btj[2],
               &itj[0], &itj[1], &itj[2]);
        data[id].btj[0] = btj[0]; data[id].btj[1] = btj[1]; data[id].btj[2] = btj[2];
        data[id].itj[0] = itj[0]; data[id].itj[1] = itj[1]; data[id].itj[2] = itj[2];
        printf("%i %lf %lf %lf %lf %lf %lf\n", id,
               data[id].btj[0],data[id].btj[1],data[id].btj[2],
               data[id].itj[0],data[id].itj[1],data[id].itj[2]);
    }
}
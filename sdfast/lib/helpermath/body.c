//
//  body.c
//  DarwinSD
//
//  Created by Robert Brothers on 5/19/16.
//  Copyright © 2016 Robert Brothers. All rights reserved.
//

#include "body.h"

void getPoint(char * str, double p[3]){
    char * pch;
    pch = strtok(str, ",");
    printf("%s\n",str);
    p[0] = atof(pch);
    pch = strtok(NULL, ",");
    p[1] = atof(pch);
    pch = strtok(NULL, ",");
    p[2] = atof(pch);
//    if(pch)
//        free(pch);
}

void extract_line_info( char * data[NU], body b[NU]){
    char * p1, * p2, * pch;
    int id;
    double pp1[3], pp2[3];
    size_t i;
    for (i=0; i<NU; i++) {
        pch = strtok(data[i], " ");
        p1 = strtok(NULL, " ");
        p2 = strtok(NULL, " ");
        id = atoi(pch);
        getPoint(p1, pp1);
        getPoint(p2, pp2);
        b[id].ID = id;
        b[id].p_geocom[0] = pp1[0]+(pp2[0]-pp1[0])/2;
        b[id].p_geocom[1] = pp1[1]+(pp2[1]-pp1[1])/2;
        b[id].p_geocom[2] = pp1[2]+(pp2[2]-pp1[2])/2;
        b[id].j2body[0] = (pp2[0]-pp1[0])/2;
        b[id].j2body[1] = (pp2[1]-pp1[1])/2;
        b[id].j2body[2] = (pp2[2]-pp1[2])/2;
        b[id].length[0] = pp2[0]-pp1[0];
        b[id].length[1] = pp2[1]-pp1[1];
        b[id].length[2] = pp2[2]-pp1[2];
    }
}

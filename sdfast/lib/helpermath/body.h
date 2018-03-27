//
//  body.h
//  DarwinSD
//
//  Created by Robert Brothers on 5/19/16.
//  Copyright © 2016 Robert Brothers. All rights reserved.
//

#ifndef body_h
#define body_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parameters.h"


// data structures
struct body_t {
    char * name;
    int ID, j_ID;
    double p_com[3], p_geocom[3], jnt0[3], jnt1[3];
    double j2body[3], length[3],btj[3],itj[3];
};
typedef struct body_t body;

void getPoint(char *, double[3]);

void extract_line_info( char * data[NU], body[NU]);


#endif /* body_h */

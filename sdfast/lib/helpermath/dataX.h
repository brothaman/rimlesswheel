//
//  dataX.h
//  DarwinSD
//
//  Created by Robert Brothers on 5/23/16.
//  Copyright © 2016 Robert Brothers. All rights reserved.
//

#ifndef dataX_h
#define dataX_h

#include <stdio.h>
#include <stdlib.h>
#include "body.h"
#include "parameters.h"
#include <string.h>


void extract(char * fname, char * data[]);
//void extractjoints(body[NU]);
void extractjoints(FILE *, body [NU]);

#endif /* dataX_h */

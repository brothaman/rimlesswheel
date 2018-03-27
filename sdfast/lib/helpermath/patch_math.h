//
//  patch_math.h
//  PlanarWheel
//
//  Created by Robert B on 5/23/17.
//  Copyright © 2017 Robert Brothers. All rights reserved.
//

#ifndef patch_math_h
#define patch_math_h

#include <stdio.h>
#include <math.h>
#include "globals.h"

double patch_cos(double theta, unsigned maxiter, double errmin);
double patch_sin(double theta, unsigned maxiter, double errmin);
double quad(double phi);
void getSpokeLocations(double spoke[NSPOKE][3]);
unsigned long long factorial(unsigned a);
#endif /* patch_math_h */

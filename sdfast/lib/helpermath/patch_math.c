//
//  patch_math.c
//  PlanarWheel
//
//  Created by Robert B on 5/23/17.
//  Copyright © 2017 Robert Brothers. All rights reserved.
//

#include "patch_math.h"

unsigned long long factorial(unsigned a) {
    unsigned long long solution = 1;
    unsigned i;
    for (i=a; i>0; i--) {
        solution *=i;
    }
    return solution;
}

double patch_cos(double theta, unsigned maxiter, double errmin) {
    int i;
    long double solution = 1, last_solution = 0, err, least_err = 1, close;
    for (i=1; i < maxiter; i++) {
        solution += pow(-1,i)*pow(theta,2*i)/factorial(2*i);
        err = (solution==last_solution) ? 0 : fabsl((solution - last_solution));
        if (err < errmin) {
            break;
        }
        if (err < least_err) {
            close = solution;
            least_err = err;
        }
        if ( solution != solution) {
            // ERROR_MESSAGE - could not reach desired resolution
            return close;
        }
        last_solution = solution;
    }
    return (double) solution;
}

double patch_sin(double theta, unsigned maxiter, double errmin) {
    int i;
    long double solution = 0, last_solution = 0, err=1, least_err = 1, close = 0.0;
    for (i=0; i < maxiter; i++) {
        double val = pow(-1,i)*pow(theta,2*i+1)/factorial(2*i+1);
        solution += pow(-1,i)*pow(theta,2*i+1)/factorial(2*i+1);
        err = (solution==last_solution) ? 0 : fabsl((solution - last_solution));
        if (err < errmin) {
            break;
        }
        if (err < least_err) {
            close = solution;
            least_err = err;
        }
        if ( solution != solution) {
            // ERROR_MESSAGE - could not reach desired resolution
            return (double) close;
        }
        last_solution = solution;
    }
    return (double) solution;
}

double quad(double phi) {
    int quadrant;
    phi = phi/(2*PI);
    return quadrant;
}

void getSpokeLocations(double spoke[NSPOKE][3]) {
    int i;
    for (i=0; i<NSPOKE; i++) {
        double val  = 2*PI/NSPOKE*i;
        val = patch_sin(2*PI/NSPOKE*i, 500, 1e-17);
        spoke[i][0] = 0;
        spoke[i][1] = RADIUS*patch_cos(2*PI/NSPOKE*i, 500, 1e-17);
        spoke[i][2] = RADIUS*patch_sin(2*PI/NSPOKE*i, 500, 1e-17);
    }
}

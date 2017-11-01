#include <stdio.h>
#include "Globals.h"


/* functions to initialize the system */
void getSpokeLocations(int body, double offset);

void initialize( double t, int lock[NU], int * err);

void initialize_characteristic_location();
/* this file will need multiple function variables to store */
/* various desired states of the system */

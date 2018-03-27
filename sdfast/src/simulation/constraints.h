#ifndef constraints_h
#define constraints_h

#include <stdio.h>
#include "Globals.h"

/* Constraints for the system and foot transition */
void sduperr (double t, double q[NQ], double errs[NUSERC]);
void sduverr (double t, double q[NQ], double u[NU], double errs[NUSERC]);
void sduaerr (double t, double q[NQ], double u[NU],
		double udot[NU], double errs[NUSERC]);
void sduconsfrc(double t, double q[NQ], double u[NU], double mults[NUSERC]);
void update_position();
void update_velocity();
void update_acceleration();
void update_state_variables( double state[NSTATE], double q[NQ], double u[NU]);
void foot_select();
void lowest_foot();
void update_direction(int direction[2], int opposite[2][FEET]);
void update_leading_foot(int direction[2]);

#endif

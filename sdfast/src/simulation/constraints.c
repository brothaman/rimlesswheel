#include "constraints.h"

/* active foot */
int active_foot[2], leading_foot[2];

/*
 y_left_lagging, y_left_leading,
 z_left_lagging, z_left_leading,
 y_right_lagging, y_right_leading,
 z_right_lagging, z_right_leading,
 z_body_lagging
 */
void sduperr( double t, double q[NQ], double errs[NUSERC]) {
	int i;

	/* initialize the errs array */
	for (i=0; i<NUSERC; i++)
		errs[i]=0;

	/* update the positions */
	update_position();
	
	/* set the errors when components below 0 */
	/* load the errors */
	if (lwf_position[active_foot[0]][ZZ] < GROUND_LEVEL) {
		errs[0] = 0;
		errs[1] = lwf_position[active_foot[0]][ZZ];
	}
	if (rwf_position[active_foot[1]][ZZ] < GROUND_LEVEL) {
		errs[2] = 0;
		errs[3] = rwf_position[active_foot[1]][ZZ];
	}
	if (body_position[1][ZZ] <= GROUND_LEVEL)
		errs[4] = body_position[1][ZZ];
}

void sduverr (double t, double q[NQ], double u[NU], double errs[NUSERC]) {
	int i;
	
	/* initialize the errs array */
	for (i=0; i<NUSERC; i++)
		errs[i]=0;
	
	/* update the velocities */
	update_velocity();
	
	/* set the errors when components below 0 */
	if (lwf_position[active_foot[0]][ZZ] < GROUND_LEVEL) {
		errs[0] = lwf_velocity[active_foot[0]][YY];
		errs[1] = lwf_velocity[active_foot[0]][ZZ];
	}
	if (rwf_position[active_foot[1]][ZZ] < GROUND_LEVEL) {
		errs[2] = rwf_velocity[active_foot[1]][YY];
		errs[3] = rwf_velocity[active_foot[1]][ZZ];
	}
	if (body_position[1][ZZ] <= GROUND_LEVEL)
		errs[4] = body_velocity[1][ZZ];
}

void sduaerr (double t, double q[NQ], double u[NU], double udot[NU], double errs[NUSERC]) {
	int i;
	
	/* initialize the errs array */
	for (i=0; i<NUSERC; i++)
		errs[i]=0;
	
	/* update the accelerations */
	update_acceleration();
	
	/* set the errors when components below 0 */
	if (lwf_position[active_foot[0]][ZZ] < GROUND_LEVEL) {
		errs[0] = lwf_acceleration[active_foot[0]][YY];
		errs[1] = lwf_acceleration[active_foot[0]][ZZ];
	}
	if (rwf_position[active_foot[1]][ZZ] < GROUND_LEVEL) {
		errs[2] = rwf_acceleration[active_foot[1]][YY];
		errs[3] = rwf_acceleration[active_foot[1]][ZZ];
	}
	if (body_position[1][ZZ] <= GROUND_LEVEL)
		errs[4] = body_acceleration[1][ZZ];
}

void sduconsfrc(double t, double q[NQ], double u[NU], double mults[NUSERC]) {
	double frc[3]={0,0,0};
	/* set the errors when components below 0 */
	if (lwf_position[active_foot[0]][ZZ] < GROUND_LEVEL){
		frc[0] = 0;
		frc[1] = mults[0];
		frc[2] = mults[1];
		sdtrans(GND,frc,LEFT_WHEEL,frc);
		sdpointf(LEFT_WHEEL, local_lwf_position[active_foot[0]], frc);
	}
	if (rwf_position[active_foot[1]][ZZ] < GROUND_LEVEL){
		frc[0] = 0;
		frc[1] = mults[2];
		frc[2] = mults[3];
		sdtrans(GND,frc,RIGHT_WHEEL,frc);
		sdpointf(RIGHT_WHEEL, local_rwf_position[active_foot[1]], frc);
	}
	if (body_position[1][ZZ] <= GROUND_LEVEL)
	{
		printf("Time at Ground Collision is %1.4e",t);
		frc[0] = 0;
		frc[1] = 0;
		frc[2] = mults[4];
		sdtrans(GND,frc,BODY,frc);
		sdpointf(BODY, local_body_position, frc);
	}
	
}

void update_position() {
	int i;
	/* update left wheel */
	for (i=0; i<FEET; i++) {
		sdpos(LEFT_WHEEL, local_lwf_position[i], lwf_position[i]);
	}
    /* update right wheel */
	for (i=0; i<FEET; i++) {
		sdpos(RIGHT_WHEEL, local_rwf_position[i], rwf_position[i]);
	}
    /* update body */
	sdpos(BODY, local_center, body_position[0]);
	sdpos(BODY, local_body_position, body_position[1]);
	for (i=0; i<2; i++) {
		
	}
}

void update_velocity() {
	int i;
	/* update left wheel */
	for (i=0; i<FEET; i++) {
		sdvel(LEFT_WHEEL, local_lwf_position[i], lwf_velocity[i]);
	}
	/* update right wheel */
	for (i=0; i<FEET; i++) {
		sdvel(RIGHT_WHEEL, local_rwf_position[i], rwf_velocity[i]);
	}
	/* update body */
	sdvel(BODY, local_center, body_velocity[0]);
	sdvel(BODY, local_body_position, body_velocity[1]);
}

void update_acceleration() {
	int i;
	/* update left wheel */
	for (i=0; i<FEET; i++) {
		sdacc(LEFT_WHEEL, local_lwf_position[i], lwf_acceleration[i]);
	}
	/* update right wheel */
	for (i=0; i<FEET; i++) {
		sdacc(RIGHT_WHEEL, local_rwf_position[i], rwf_acceleration[i]);
	}
	/* update body */
	sdacc(BODY, local_center, body_acceleration[0]);
	sdacc(BODY, local_body_position, body_acceleration[1]);
}

void update_state_variables( double state[NSTATE], double q[NQ], double u[NU]) {
    int i;
    for (i=0; i<NSTATE; i++) {
        if (i<NQ) {
            q[i] = state[i];
        } else {
            u[i-NQ] = state[i];
        }
    }
}

/* function to select the the active foot */
void foot_select() {
	/* initially set the lagging foot as the 0th foot */
	/* the leading foot should always have a negative  velocity in the z-direction */
	/* and be the closest to the ground. Once the velocity of the lagging foot */
	/* becomes positive and is greater that the ground level the lagging foot shifts */
	/* When the leading foot engages the lagging foot should disengage. After the */
	/* lagging foot disengages the leading foot should become the lagging foot */
	static int steps[2] = {0,0}, direction[2];
	int i, current_direction[2];
	double lowest = RADIUS;
	static int opposite[2][FEET];

	/* update positions in the global feet and body variables */
	update_position();
	update_velocity();
	update_acceleration();

	if (steps[0] == 0 && steps[1] == 0) {
		// the lagging foot should be foot closest to the ground and furtherst behind
		lowest_foot();
		direction[0] = direction[1] = 1;
		for (i=0; i<FEET; i++) {
			opposite[0][i] = i < FEET/2 ? i+FEET/2:i-FEET/2;
			opposite[1][i] = i < FEET/2 ? i+FEET/2:i-FEET/2;
		}
		steps[0]++; steps[1]++;
	} else {
		// determine the direction of velocity using the foot directly above
		update_direction(current_direction, opposite);
		
		// if direction is of the system is negative active foot needs to change
		if (current_direction[0] != direction[0] || current_direction[1] != direction[1]) {
			// change the leading foot
			update_leading_foot(current_direction);
			cpy_ivec(direction, current_direction, 2);
		}
		
		// select the lagging foot
		if ( lwf_position[leading_foot[0]][ZZ] < GROUND_LEVEL) {
			steps[0]++;
			active_foot[0] = leading_foot[0];
			update_leading_foot(direction);
		}
		// select the lagging foot
		if ( rwf_position[leading_foot[1]][ZZ] < GROUND_LEVEL) {
			steps[1]++;
			active_foot[1] = leading_foot[1];
			update_leading_foot(direction);
		}
		for (i=0; i<FEET; i++) {
			if (lwf_position[i][ZZ] <= GROUND_LEVEL && i != active_foot[0]) {
				update_leading_foot(current_direction);
			}
			if (rwf_position[i][ZZ] <= GROUND_LEVEL && i != active_foot[0]) {
				update_leading_foot(current_direction);
			}
		}
	}
}

void lowest_foot() {
	int i;
	double lowest[2] = {RADIUS,RADIUS};
	for (i=0; i<FEET; i++) {
		if (lwf_position[i][ZZ] < lowest[0]) {
			active_foot[0] = i;
			lowest[0] = lwf_position[i][ZZ];
		}
		if (rwf_position[i][ZZ] < lowest[1]) {
			active_foot[1] = i;
			lowest[1] = rwf_position[i][ZZ];
		}
	}
	
	/* set leading foot for the left wheel */
	if (active_foot[0]==FEET) {
		leading_foot[0]=0;
	} else {
		leading_foot[0]=active_foot[0]+1;
	}
	
	/* set leading foot for the right wheel */
	if (active_foot[1]==FEET) {
		leading_foot[1]=0;
	} else {
		leading_foot[1]=active_foot[1]+1;
	}
}

void update_direction(int direction[2], int opposite[2][FEET]) {
	direction[0] = (lwf_velocity[opposite[0][active_foot[0]]][YY] > 0) ? 1:-1;
	direction[1] = (rwf_velocity[opposite[1][active_foot[1]]][YY] > 0) ? 1:-1;
}

void update_leading_foot(int direction[2]) {
	if(active_foot[0] == 0) {
		leading_foot[0] = (direction[0] > 0) ? active_foot[0]+1:FEET-1;
	} else if (active_foot[0] == FEET-1) {
		leading_foot[0] = (direction[0] > 0) ? 0:active_foot[0]-1;
	} else {
		leading_foot[0] = (direction[0] > 0) ? active_foot[0]+1:active_foot[0]-1;
	}
	
	if(active_foot[1] == 0) {
		leading_foot[1] = (direction[1] > 0) ? active_foot[1]+1:FEET-1;
	} else if (active_foot[1] == FEET-1) {
		leading_foot[1] = (direction[1] > 0) ? 0:active_foot[1]-1;
	} else {
		leading_foot[1] = (direction[1] > 0) ? active_foot[1]+1:active_foot[1]-1;
	}
}

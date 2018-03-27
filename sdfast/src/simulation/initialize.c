#include "initialize.h"
/* initialize the btj, itj and initial states */
void initialize ( double t, int lock[NU], int * err) {
	
	/* variables necessary */
	int fcnt=0;
	/* variables for initialization */
	double btj[NBOD][3], itj[NBOD][3];
	double inertia[3][3];
	double baumgartes;
	
	/* BODY - initialize the btj and itj variables */
	btj[BODY][0] = 0;
	btj[BODY][1] = 0;
	btj[BODY][2] = BODY_LENGTH;
	itj[BODY][0] = 0;
	itj[BODY][1] = 0;
	itj[BODY][2] = RADIUS;
	sdbtj(BODY, btj[BODY]);
	sditj(BODY, itj[BODY]);
	
	
	/* LEFT - initialize the btj and itj variables */
	btj[LEFT_WHEEL][0] = 0;
	btj[LEFT_WHEEL][1] = 0;
	btj[LEFT_WHEEL][2] = 0;
	itj[LEFT_WHEEL][0] = -BODY_WIDTH;
	itj[LEFT_WHEEL][1] = 0;
	itj[LEFT_WHEEL][2] = BODY_LENGTH;
	sdbtj(LEFT_WHEEL, btj[LEFT_WHEEL]);
	sditj(LEFT_WHEEL, itj[LEFT_WHEEL]);
	
	/* RIGHT - initialize the btj and itj variables */
	btj[RIGHT_WHEEL][0] = 0;
	btj[RIGHT_WHEEL][1] = 0;
	btj[RIGHT_WHEEL][2] = 0;
	itj[RIGHT_WHEEL][0] = BODY_WIDTH;
	itj[RIGHT_WHEEL][1] = 0;
	itj[RIGHT_WHEEL][2] = BODY_LENGTH;
	sdbtj(RIGHT_WHEEL, btj[RIGHT_WHEEL]);
	sditj(RIGHT_WHEEL, itj[RIGHT_WHEEL]);
	
	/* set up and initialize the inertia for each body */
	inertia[0][0] = BODY_MASS*BODY_LENGTH*BODY_LENGTH/3;   inertia[0][1] = inertia[0][2] = 0;
	inertia[1][0] = 0; inertia[1][1] = BODY_MASS*BODY_LENGTH*BODY_LENGTH/3; inertia[1][2] = 0;
	inertia[2][0] = inertia[2][1] = 0; inertia[2][2] = 0;
	sdiner(BODY,inertia);
	
	/* set up and initialize the inertia for each body */
	inertia[0][0] = WHEEL_MASS*RADIUS*RADIUS/2;   inertia[0][1] = inertia[0][2] = 0;
	inertia[1][0] = 0; inertia[1][1] = WHEEL_MASS*RADIUS*RADIUS/4; inertia[1][2] = 0;
	inertia[2][0] =    inertia[2][1] = 0; inertia[2][2] = WHEEL_MASS*RADIUS*RADIUS/4;
	sdiner(LEFT_WHEEL,inertia);
	sdiner(RIGHT_WHEEL,inertia);
	
	/* load the mass characteristics */
	sdmass(BODY,BODY_MASS);
	sdmass(LEFT_WHEEL,WHEEL_MASS);
	sdmass(RIGHT_WHEEL,WHEEL_MASS);
	
	/* initialize sdfast */
	sdinit();
	    
	/* load state and initial values */
	sdstate( t, &state[0], &state[NQ]);

	/* assemble the given state */
	sdassemble(t, state, lock, TOL, MAXITER, &fcnt, &err[0]);
	if (*err) {
		mexPrintf("Assembly Error: %i\n",*err);
		fcnt = 0;
	}

	/* set the given initial velocities */
	sdinitvel( t, state, lock, TOL, MAXITER, &fcnt, &err[0]);
	if (*err) {
		mexPrintf("Initial Velocity Error: %i\n",*err);
		fcnt = 0;
	}

	/* set up the baumgarte stabilization constant */
	baumgartes = 50;
	sdstab(2*baumgartes, baumgartes*baumgartes);
	
	/* initialize necessary measurements */
	initialize_characteristic_location();
}


/* change so that the function edits the local_lwf_variable */
void getSpokeLocations(int body, double offset) {
	int i;
	double origin[3]={0,0,0}, center[3], theta;
	
	/* there is an issue with center 9/14/17 */
	sdpos(body,origin,center);
	switch (body) {
		case LEFT_WHEEL:
			for (i=0; i<FEET; i++) {
				theta = 2*PI/FEET*i - PI/2.0 + offset;
				local_lwf_position[i][0] = 0;
				local_lwf_position[i][1] = RADIUS*cos(theta);
				local_lwf_position[i][2] = RADIUS*sin(theta);
			}
		case RIGHT_WHEEL:
			for (i=0; i<FEET; i++) {
				theta = 2*PI/FEET*i - PI/2.0 + offset;
				local_rwf_position[i][0] = 0;
				local_rwf_position[i][1] = RADIUS*cos(theta);
				local_rwf_position[i][2] = RADIUS*sin(theta);
			}
		default:
			break;
	}
}

void initialize_characteristic_location() {
	double btj[3];
	/* find out information about the system */
	sdgetitj(2,btj);
	local_center[0] = 0;
	local_center[1] = 0;
	local_center[2] = btj[2];
	
	/* update the center position */
	sdpos(0, local_center, body_position[0]);
	getSpokeLocations(1,0);
	getSpokeLocations(2,0);
}

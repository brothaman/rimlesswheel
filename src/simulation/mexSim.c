// necessary for matlab
#include "mex.h"


// standard lib
#include <stdlib.h>
#include <stdio.h>

// local developed libraries
#include "helper.h"
#include "Globals.h"
#include "initialize.h"
#include "constraints.h"


void getBodyAngle( double * angle) {
	double directional_cosine[3][3];

	/* determine the body angle between the ground */
	sdorient( BODY, directional_cosine);
	sddc2ang(directional_cosine, &angle[0], &angle[1], &angle[2]);
}

void cpy_vecd(int n, double * invec, double * outvec) {
	for (int i = 0; i<n; i++) {
		outvec[i] = invec[i];
	}
}
double *Torques;
/* state variable containing system information */
double t, state[NSTATE], dstate[NSTATE];

/* positional information relative to each local frame */
double local_center[3];            
double local_body_position[2][3];  
double local_lwf_position[FEET][3];
double local_rwf_position[FEET][3];

/* dynamic information relative to points on the body in the global frame */
double body_position[2][3], body_velocity[2][3], body_acceleration[2][3];
double lwf_position[FEET][3], lwf_velocity[FEET][3], lwf_acceleration[FEET][3];
double rwf_position[FEET][3], rwf_velocity[FEET][3], rwf_acceleration[FEET][3];

void mexFunction(
		int n_output_parameters,      mxArray * output_arguments[],
		int n_input_parameters, const mxArray * input_arguments[]) 
{
	/* so as not to redefine iterators */
	int i, j;
	/* matlabs input and output variables */
	double *tin, *state_in, *dstate_in;
	double *tout, *state_out, *dstate_out;
 	double *rxn_torques, *value;

  double errest;
	double directional_cosine[3][3], angles[3], * bodyAngles;
	double bodydim[3][3];

	// set the body dimensions
	bodydim[0][0] = BODY_WIDTH;
	bodydim[0][1] = BODY_LENGTH;
	bodydim[0][2] = BODY_DEPTH;
	bodydim[1][0] = SPOKE_RADIUS;
	bodydim[1][1] = RADIUS;
	bodydim[1][2] = 0;
	bodydim[2][0] = SPOKE_RADIUS;
	bodydim[2][1] = RADIUS;
	bodydim[2][2] = 0;

	/* add the ncessar values for the animation values 
	 *
	 * anistates with be composed of:
	 * [0-2]		-> body center position
	 * [3-5]		-> body euler angles
	 * [6-8]		-> left wheel center position
	 * [9-11]		-> left wheel euler angles
	 * [12-14]	-> right wheel center position
	 * [15-17]	-> right wheel euler angles
	 *
	 */
	double * aniStates, * tempdarr;
	mxArray * tempcell, * Cellin;

	int lock[NU], fcnt, err, flag, cellsize;

	// get pointers to the inputs from matlab
	tin       = mxGetPr(input_arguments[0]);
	state_in  = mxGetPr(input_arguments[1]);
	dstate_in = mxGetPr(input_arguments[2]);
	Torques   = mxGetPr(input_arguments[3]);
	Cellin		= input_arguments[4];

	// get details about the information coming in
	cellsize = mxGetNumberOfElements(Cellin);

	// reserve memory for output
	output_arguments[0] = mxCreateDoubleMatrix(1,2,mxREAL);
	output_arguments[1] = mxCreateDoubleMatrix(1,NSTATE,mxREAL);
	output_arguments[2] = mxCreateDoubleMatrix(1,NSTATE,mxREAL);
	output_arguments[3] = mxCreateDoubleMatrix(1,NA,mxREAL);
	output_arguments[4] = mxCreateDoubleMatrix(1,3,mxREAL);
	output_arguments[5] = mxCreateCellMatrix(cellsize+NBOD,1); // extend the incoming cell array
	
	// create pointers to output
	tout				= (double *)mxGetPr(output_arguments[0]);
	state_out		= (double *)mxGetPr(output_arguments[1]);
	dstate_out	= (double *)mxGetPr(output_arguments[2]);
	rxn_torques	= (double *)mxGetPr(output_arguments[3]);
	bodyAngles	= (double *)mxGetPr(output_arguments[4]);

	// copy incoming cell array data in to new cell
	for ( i=0; i<cellsize; i++) {
		mxSetCell( output_arguments[5], i, mxDuplicateArray( mxGetCell( Cellin, i)));
	}

	// initializr local variables - load state variable before initialization call
	t = tin[0];
	cpy_vecd( NSTATE, state_in,  state);
	cpy_vecd( NSTATE,dstate_in, dstate);
	for (i=0; i<NU; i++)
		lock[i] = 0;
	flag = t>0 ? 0:1;

	// initialize SDFast
	initialize( t, lock, &err);
	switch (err) 
	{
		case 0:
			break;
		case 1:
			mexPrintf("Initial Velocities Error: Unable to meet velocity constraints\n");
			mexPrintf("\tTime: %1.4e\n", t);
			break;
		case 2:
			mexPrintf("Initial Velocities Error: SDFast was still in progress when MAXEVALS was exceeded\n");
			mexPrintf("\tMAXEVALS is currently set at: %i", MAXITER);
			/* initvel was not finished finding a configuraition in which the velocities exist */
			break;
		default:
			/* print error */
			mexPrintf("Initial Velocities Error: sdinitvel returned undefined error --- %i\n", err);
			break;
	}

	/* orient the feet and determine a location to apply the constraints and constraint forces */
	foot_select();

	// integrate step
	sdfmotion(&t, state, dstate, tin[1], CTOL, &flag, &errest, &err);
	switch (err) 
		{
			case 0:
				break;
			case 1:
				mexPrintf("Motion Error: \n");
				mexPrintf("\tTime: %1.4e\n", t);
				break;
			case 2:
				mexPrintf("Motion Error: Relative error between steps is not improving\n");
				/* initvel was not finished finding a configuraition in which the velocities exist */
				break;
			case 3:
				/* print error */
				mexPrintf("Motion Error: Contraints are violated by more than TOLERANCE\n");
				mexPrintf("\tTOLERANCE: %1.4e\n", CTOL);
				break;
			default:
				/* print error */
				mexPrintf("Initial Velocities Error: sdinitvel returned undefined error\n");
				break;
		}
	/* build array for data storage */
	double centerloc[3] = {0,0,0}, dc[3][3];
	tempcell = mxCreateDoubleMatrix( 1, 3+3+3, mxREAL);
	tempdarr = (double *)mxGetPr(tempcell);
	for ( i=0; i<NBOD; i++) {
		sdpos( i, centerloc, &tempdarr[0]);
		sdorient(i,dc);
		sddc2ang(dc, &tempdarr[3], &tempdarr[4], &tempdarr[5]);
		tempdarr[6] = bodydim[i][0];
		tempdarr[7] = bodydim[i][1];
		tempdarr[8] = bodydim[i][2];
		mxSetCell( output_arguments[5], cellsize+i, mxDuplicateArray( tempcell));
	}
	/* determine the body angle between the ground */
	getBodyAngle(bodyAngles);

	/* store return variables */
	tout[0] = t;
	tout[1] = tin[1];
	cpy_vecd(NSTATE,  state,  state_out);
	cpy_vecd(NSTATE, dstate, dstate_out);
	cpy_vecd(NA, Torques, rxn_torques);


	// clean up
}

void sduforce(double t, double q[NQ], double u[NU]) {
	for( int i=0; i<NA; i++) 
	{
		sdhinget(i+1, 0, Torques[i]);
	}
}

void sdumotion(double t, double q[NQ], double u[NU]) {
}



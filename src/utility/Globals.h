#ifndef Globals_h
#define Globals_h
#include <math.h>
#include "helper.h"
#include "mex.h"

/* sdfast specifics - emulating the set up from the matlab example */
#define NQ 9	/* number of state position variables */
#define NU 8	/* number of state velocity variables */
#define NA 2	/* number of actuators */
#define NSTATE (NQ+NU)
#define NUSERC 9	/* lagging and leading feet of each wheel and body */
#define NBOD 3
#define GND -1
#define BODY 0
#define LEFT_WHEEL 1
#define RIGHT_WHEEL 2
#define GND_ANG 0

/* Global Specifics */
#define PI 3.1415926536
#define ZZ 2
#define YY 1
#define XX 0
#define GROUND_LEVEL 0.0

/* system specifics */
#define FEET 8	/* set the number of feet desired - must be an even number... idk what happens otherwise */
#define NSPOKE FEET
#define MAX_ACTIVE_FEET 2
#define RADIUS 0.305
#define BODY_LENGTH (RADIUS - 0.25*RADIUS)
#define BODY_WIDTH (0.50*RADIUS)
#define BODY_MASS 2.72
#define WHEEL_MASS 0.5

/* Integrater Stuffs */
#define DT 5e-3
#define TOL 1e-4
#define CTOL 1e-4
#define INT_TOL 1e-6
#define MAXITER 1000

/* Time */
#define ENDTIME 20.0
#define STEPS (int) (ENDTIME/DT+1)

/* Files for data storage */
#define FILENAME "/Users/rbrothers/Desktop/School/Graduate/thesis/Simulation/sdfast/examples/MATLAB_SDFAST/rimless_robot/rot_free_rot/data/animate.dat"
#define TQU_FILENAME "/Users/rbrothers/Desktop/School/Graduate/thesis/Simulation/sdfast/examples/MATLAB_SDFAST/rimless_robot/rot_free_rot/data/state.dat"
#define DYNAMICS_FILENAME "/Users/rbrothers/Desktop/School/Graduate/thesis/Simulation/sdfast/examples/MATLAB_SDFAST/rimless_robot/rot_free_rot/data/control.dat"
#define SPEED_FILENAME "/Users/rbrothers/Desktop/School/Graduate/thesis/Simulation/sdfast/examples/MATLAB_SDFAST/rimless_robot/rot_free_rot/data/speed.dat"
#define DATA_FORMAT "%2.4e %2.4e %2.4e %2.4e %2.4e %2.4e %2.4e"

/* state variable containing system information */
extern double t, state[NSTATE], dstate[NSTATE];

/* body positions */                                                                  
extern double local_center[3];                                                        
extern double local_body_position[2][3];                                              
extern double local_lwf_position[FEET][3];                                            
extern double local_rwf_position[FEET][3];                                            
                                                                                      
/*double center_position[3], center_velocity[3], center_acceleration[3];*/            
extern double body_position[2][3], body_velocity[2][3], body_acceleration[2][3];      
extern double lwf_position[FEET][3], lwf_velocity[FEET][3], lwf_acceleration[FEET][3];
extern double rwf_position[FEET][3], rwf_velocity[FEET][3], rwf_acceleration[FEET][3];

#endif

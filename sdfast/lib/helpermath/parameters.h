//
//  parameters.h
//  darwin_sdc
//
//  Created by Robert Brothers on 5/24/16.
//  Copyright © 2016 Robert Brothers. All rights reserved.
//

#ifndef parameters_h
#define parameters_h

#include <stdio.h>

#define GROUND              (-1)
#define TORSO               0
#define R_SHOULDER_PITCH    1
#define L_SHOULDER_PITCH    2
#define R_SHOULDER_ROLL     3
#define L_SHOULDER_YAW      4
#define R_ELBOW_YAW         5
#define L_ELBOW_YAW         6
#define R_HIP_YAW           7
#define L_HIP_YAW           8
#define R_HIP_ROLL          9
#define L_HIP_ROLL          10
#define R_HIP_PITCH         11
#define L_HIP_PITCH         12
#define R_KNEE_PITCH        13
#define L_KNEE_PITCH        14
#define R_ANKLE_PITCH       15
#define L_ANKLE_PITCH       16
#define R_ANKLE_ROLL        17
#define L_ANKLE_ROLL        18
#define HEAD_YAW            19
#define HEAD_PITCH          20

#define NQ 21
#define NU 21
#define NSTATE (NQ+NU)

#define CTOL        0.0
#define INT_TOL     1e-12
#define DT          0.02
#define NSTEPS      10
#define TEND        3/0.02
#define COM {0,0,0}
#define MAXEVALS 1000

#pragma mark - Global Variables



//double zero_tics[NU-1];
//double limit_tics[NU-1][2];
//double scale_tics_to_rad[NU-1];
//double joint_limits_rad[NU-1][2];

#endif /* parameters_h */

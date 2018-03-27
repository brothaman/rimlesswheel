//
//  drawings.hpp
//  DarwinSim
//
//  Created by Robert Brothers on 6/21/16.
//  Copyright © 2016 Robert Brothers. All rights reserved.
//

/** @defgroup drawings Drawings
 Drawings is a library that runs in tandem with the Drawstuff library
 */


#ifndef drawings_hpp
#define drawings_hpp

#include <stdio.h>
#include "drawstuff.h" /* ODE Graphics stuff */
#include "drawstuff-cga.h" /* CGA stuff to make things clearer */
#include "mmath.h"
#include "string.h"


struct b_t {
    char * name;
    float p1[3],p2[3];
};
typedef struct b_t body;

void draw(const body b);
/**
 * @brief determines the object to draw with given name
 * @ingroup drawings
 * @param b body data structure containing the name and joint positions of a link
 */

void draw(const body b,  const float length, const float radius);
void drawArm(const float pos[3], const float R[12]);
void drawBody(const float pos[3], const float R[12]);
void drawForearm(const float pos[3], const float R[12]);
void drawLegs(const float pos[3], const float R[12]);
void drawJoint(const float pos[3], const float R[12]);
void drawHead(const float pos[3], const float R[12]);
void drawNeck(const float pos[3], const float R[12]);
void drawFoot(const float pos[3], const  float R[12]);
void drawPend(const float pos[3], const float R[12], const float sides[3]);
void drawLink(const float pos[3], const float R[12], const float radius, const float length);
void drawWheel(const float pos[3], const float R[12], const float length, const float radius);
void drawChasis(const float pos[3], const float R[12], const float lwh[3]);
#endif /* drawings_hpp */

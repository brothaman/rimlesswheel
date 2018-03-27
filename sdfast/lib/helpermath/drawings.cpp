//
//  drawings.cpp
//  DarwinSim
//
//  Created by Robert Brothers on 6/21/16.
//  Copyright © 2016 Robert Brothers. All rights reserved.
//

#include "drawings.hpp"

void draw(const body b, float length = 0.5, float radius = 0.025) {
    if (b.name!=NULL) {
        static float center[3];
        static float R[12], Rt[9],p1[3],p2[3];
        p1[0]=b.p1[0]; p1[1]=b.p1[1]; p1[2]=b.p1[2];
        p2[0]=b.p2[0]; p2[1]=b.p2[1]; p2[2]=b.p2[2];
        center[0] = b.p1[0] + (b.p2[0] - b.p1[0])/2;
        center[1] = b.p1[1] + (b.p2[1] - b.p1[1])/2;
        center[2] = b.p1[2] + (b.p2[2] - b.p1[2])/2 + 0.0f;
        
        // develop rotations
        rodrigues_rot_2pt(p1, p2, Rt);
        convR(Rt, R);
        
        // select a body
        if (strcmp(b.name, "TORSO")==0) {
            drawBody(center,R);
        } else if (strcmp(b.name, "R_SHOULDER_PITCH")==0 || strcmp(b.name, "L_SHOULDER_PITCH")==0) {
            drawJoint(center, R);
        }else if (strcmp(b.name, "R_SHOULDER_ROLL")==0 || strcmp(b.name, "L_SHOULDER_ROLL")==0) {
            drawArm(center, R);
        }else if (strcmp(b.name, "R_ELBOW_YAW")==0 || strcmp(b.name, "L_ELBOW_YAW")==0) {
            drawForearm(center, R);
        }else if (strcmp(b.name, "R_HIP_YAW")==0 || strcmp(b.name, "L_HIP_YAW")==0) {
            drawJoint(center, R);
        }else if (strcmp(b.name, "R_HIP_ROLL")==0 || strcmp(b.name, "L_HIP_ROLL")==0) {
            drawJoint(center, R);
        }else if (strcmp(b.name, "R_HIP_PITCH")==0 || strcmp(b.name, "L_HIP_PITCH")==0) {
            drawLegs(center, R);
        }else if (strcmp(b.name, "R_KNEE_PITCH")==0 || strcmp(b.name, "L_KNEE_PITCH")==0) {
            drawLegs(center, R);
        }else if (strcmp(b.name, "R_ANKLE_PITCH")==0 || strcmp(b.name, "L_ANKLE_PITCH")==0) {
            drawJoint(center, R);
        }else if (strcmp(b.name, "R_ANKLE_ROLL")==0 || strcmp(b.name, "L_ANKLE_ROLL")==0) {
            drawFoot(center, R);
        }else if (strcmp(b.name, "HEAD_YAW")==0) {
            drawNeck(center, R);
        }else if (strcmp(b.name, "HEAD_PITCH")==0) {
            drawHead(center, R);
        }else if (strcmp(b.name, "WHEEL")==0) {
            drawWheel(center, R, 0.025f, 0.5);
        }else if (strcmp(b.name, "BODY")==0) {
			float lwh[3] = {radius,radius,length};
            drawChasis(center, R, lwh);
        } else {
//            static float sides[] = {.046,.046,2};
            drawLink(center, R, length, radius);
        }

    }
}
void drawArm(const float pos[3], const float R[12]) {
    static float sides[3] = {.032,.032,.060};
    dsDrawBox(pos, R, sides);
}
void drawBody(const float pos[3], const float R[12]) {
    static float sides[3] = {.104,.164,.122};
    dsDrawBox(pos, R, sides);
}
void drawForearm(const float pos[3], const float R[12]) {
    static float sides[3] = {.032,.032,.129};
    dsDrawBox(pos, R, sides);
}
void drawLegs(const float pos[3], const float R[12]) {
    static float sides[3] = {.046,.046,.093};
    dsDrawBox(pos, R, sides);
}
void drawJoint(const float pos[3], const float R[12]) {
    dsDrawSphere(pos, R, .020);
}
void drawHead(const float pos[3], const float R[12]) {
    static float sides[3] = {.074,.074,.074};
    dsDrawBox(pos, R, sides);
}
void drawNeck(const float pos[3], const float R[12]) {
    static float radius = .0225, length = .0505;
    dsDrawCylinder(pos, R, length, radius);
}
void drawFoot(const float pos[3], const  float R[12]) {
    static float sides[3] = {.104,.066,.0335};
    dsDrawBox(pos, R, sides);
}
void drawPend(const float pos[3], const float R[12], const float sides[3]) {
//    static float sides[3] = {.046,.046,4.00};
    dsDrawCylinder(pos, R, sides[2],sides[1]);
}
void drawLink( const float pos[3], const float R[12], const float length, const float radius) {
	dsSetColor(1, 1, 1);
    dsDrawCylinder(pos, R, length ,radius);
}
void drawWheel(const float pos[3], const float R[12], const float length, const float radius) {
    dsDrawCylinder(pos, R, length, radius);
}
void drawChasis(const float pos[3], const float R[12], const float lwh[3]) {
    static float sides[3] = {2*lwh[0],lwh[1],lwh[2]};
	dsSetColor(.9, 0, 0);
    dsDrawBox(pos, R, sides);
}

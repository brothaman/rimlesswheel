//
//  mmath.hpp
//  darwin_sdc
//
//  Created by Robert Brothers on 6/1/16.
//  Copyright © 2016 Robert Brothers. All rights reserved.
//

#ifndef mmath_h
#define mmath_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// angle about the y axis
float absf(float);
double distd(double p1[3], double p2[3]);
float distf(float p1[3], float p2[3]);
double mag(double[3]);
float magf(float[3]); 
void rot_angles(double[3], double[2]);
void rot_anglesf(float[3], float[2]);
void rotx(double, double [12]);
void rotxf( float, float  [12]);
void roty(double, double [12]);
void rotyf( float, float  [12]);
void rotz(double, double [12]);
void rotzf( float, float  [12]);
void mult(double[12],double[12],double[12]);
void multf(const float[9], const float[9], float[3]);
void crossf(const float[3], const float[3], float[3]);
float dotf(const float[3], const float[3]);
void skewSymf(const float[3], float[9]);
void normf(float[3]);
float ang(const float[3],const float[3]);
void rodrigues_rot_2pt(const float[3], const float[3], float[9]);
void scaleMat(const float, const float[9],const float[9]);
void add(const float[9], const float[9], float[9]);
void convR(const float[9], float[12]);
void printMat(double[9]);
void printMatf(const char *, const float[9]);
void printVec(const char*, const double[3]);
void printVecf(const char *, const float[3]);
#endif /* mmath_h */

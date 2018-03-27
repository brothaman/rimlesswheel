//
//  mmath.cpp
//  darwin_sdc
//
//  Created by Robert Brothers on 6/1/16.
//  Copyright © 2016 Robert Brothers. All rights reserved.
//

#include "mmath.h"

float absf(float val) {
    val*=val;
    return powf(val, 0.5f);
}
double distd(double p1[3], double p2[3]) {
	int i;
	double result = 0;
	for (i=0; i<3; i++) {
		result = result + (p2[i]-p1[i])*(p2[i]-p1[i]);
	}
	return sqrt(result);
}
float distf(float p1[3], float p2[3]) {
	int i;
	float result = 0;
	for (i=0; i<3; i++) {
		result = result + (p2[i]-p1[i])*(p2[i]-p1[i]);
	}
	return sqrt(result);
}
double mag(double val[3]){
    double result = 0;
    for (int i = 0; i<3; i++) {
        result = result + val[i]*val[i];
    }
    return sqrt(result);
}
float magf(float val[3]) {
    float result = 0;
    //    result = powf(val[0]*val[0] + val[1]*val[1], 0.5f);
    //    result = powf(result*result + val[2]*val[2], 0.5f);
    for (int i = 0; i<3; i++) {
        result = result + val[i]*val[i];
    }
//    printf("%f^2 + %f^2 + %f^2 = %f\n",val[0],val[1],val[2],result);
    return sqrtf(result);//(result, 0.5f);
}

void rot_angles( double a[3], double angles[2]) {
    /** 
     Determines the angle necessary to rotate from z of equal length to vector
     @param a is an input vector of the form [x,y,z]
     @param angles is the vector where the angle of rotation about z and angle of rotation about y are stored
     */
    double rxy = pow(a[1]*a[1]+a[0]*a[0], 0.5);
    angles[0] = atan2(a[1], a[0]);//(a[1]/a[0]);
    angles[1] = atan2(a[2], rxy);//(a[2]/rxy);
}

void rot_anglesf(float a[3], float angles[2]) {
    /**
     Determines the angle necessary to rotate from z of equal length to vector
     @param a is an input vector of the form [x,y,z]
     @param angles is the vector where the angle of rotation about z and angle of rotation about y are stored
     */
    float rxy = powf(a[1]*a[1]+a[0]*a[0], 0.5);
    angles[0] = atan2f(a[1], a[0]);//(a[1]/a[0]);
    angles[1] = atan2f(a[2], rxy);//(a[2]/rxy);
    
}
void rotx(double angle, double R[12]) {
    double c = cos(angle);
    double s = sin(angle);
    R[ 0]= 1; R[ 1]= 0; R[ 2]= 0; R[ 3]= 0;
    R[ 4]= 0; R[ 5]= c; R[ 6]=-s; R[ 7]= 0;
    R[ 8]= 0; R[ 9]= s; R[10]= c; R[11]= 0;
    
}
void rotxf(float angle, float R[12]) {
    float c = cosf(angle);
    float s = sinf(angle);
    R[ 0]= c; R[ 1]=-s; R[ 2]= 0; R[ 3]= 0;
    R[ 4]= s; R[ 5]= c; R[ 6]= 0; R[ 7]= 0;
    R[ 8]= 0; R[ 9]= 0; R[10]= 1; R[11]= 0;
    
}

void roty(double angle, double R[12]) {
    double c = cos(angle);
    double s = sin(angle);
    R[ 0]= c; R[ 1]= 0; R[ 2]= s; R[ 3]= 0;
    R[ 4]= 0; R[ 5]= 1; R[ 6]= 0; R[ 7]= 0;
    R[ 8]=-s; R[ 9]= 0; R[10]= c; R[11]= 0;
    
}
void rotyf(float angle, float R[12]) {
    float c = cosf(angle);
    float s = sinf(angle);
    R[ 0]= c; R[ 1]= 0; R[ 2]= s; R[ 3]= 0;
    R[ 4]= 0; R[ 5]= 1; R[ 6]= 0; R[ 7]= 0;
    R[ 8]=-s; R[ 9]= 0; R[10]= c; R[11]= 0;
    
}

void rotz(double angle, double R[12]) {
    double c = cos(angle);
    double s = sin(angle);
    R[ 0]= c; R[ 1]=-s; R[ 2]= 0; R[ 3]= 0;
    R[ 4]= s; R[ 5]= c; R[ 6]= 0; R[ 7]= 0;
    R[ 8]= 0; R[ 9]= 0; R[10]= 1; R[11]= 0;
    
}
void rotzf(float angle, float R[12]) {
    float c = cosf(angle);
    float s = sinf(angle);
    R[ 0]= c; R[ 1]=-s; R[ 2]= 0; R[ 3]= 0;
    R[ 4]= s; R[ 5]= c; R[ 6]= 0; R[ 7]= 0;
    R[ 8]= 0; R[ 9]= 0; R[10]= 1; R[11]= 0;
    
}

void mult(double a[12], double b[12], double c[12]){
    int i=0, j=0,k=0;
    c[0] = c[1] = c[2] = c[3] = 0;
    c[4] = c[5] = c[6] = c[7] = 0;
    c[8] = c[9] = c[10] = c[11] = 0;
    
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            for (k=0; k<3; k++) {
                c[i*4+j] = a[i*4+k]+b[k*4+j]+c[i*4+j];
            }
            
        }
    }
}
void multf(const float a[9], const float b[9], float c[9]) {
    int i, j,k;
    c[0]=c[1]=c[2]=0;
    c[3]=c[4]=c[5]=0;
    c[6]=c[7]=c[8]=0;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            for (k=0; k<3; k++) {
                c[i*3+j] = a[i*3+k]*b[k*3+j]+c[i*3+j];
            }
            
        }
    }
}

void crossf(const float u[3], const float v[3], float ans[3]) {
    ans[0] =   u[1]*v[2] - v[1]*u[2];
    ans[1] = -(u[0]*v[2] - v[0]*u[2]);
    ans[2] =   u[0]*v[1] - v[0]*u[1];
}

float dotf(const float u[3], const float v[3]) {
    float ans = 0;
    for (int i = 0; i<3; i++) {
        ans = u[i]*v[i] + ans;
    }
    return ans;
}

void skewSymf(const float u[3], float R[9]) {
    R[0]=R[4]=R[8]=0;
    R[1]= -u[2]; R[3]=  u[2];
    R[2]=  u[1]; R[6]= -u[1];
    R[5]= -u[0]; R[7]=  u[0];
}

void normf(float u[3]) {
    float magn = magf(u);
    if (magn!=0) {
        u[0] = u[0]/magn;
        u[1] = u[1]/magn;
        u[2] = u[2]/magn;
    }
}

float ang(float u[3], float v[3]) {
    return acosf(dotf(u, v)/magf(u)/magf(v));
}
void scaleMat(const float scalar, const float mat[9], float ans[9]) {
    int i;
    for (i=0; i<9; i++) {
        ans[i]=scalar*mat[i];
    }
}
void add(const float m1[9], const float m2[9], float ans[9]) {
    int i;
    for (i=0; i<9;i++){
        ans[i] = m1[i]+m2[i];
    }
}
void rodrigues_rot_2pt(const float v[3], const float u[3], float R[9]) {
    // set up an Identity
    float I[9]={
        1,0,0,
        0,1,0,
        0,0,1
    };
    // set up the K matrix
    float vec[3] = {
        v[0]-u[0],
        v[1]-u[1],
        v[2]-u[2]
    };
    if (vec[0]==0 && vec[1]==0 && vec[2]==0) {
        for (int i=0; i<9; i++) {
            R[i]=I[i];
        }
    } else {
        float zax[3]={0,0,1};
        float angle;
        float k[3];
        float K[9]={0};
        float Ksq[9]={0};
        float temp[9], temp2[9], temp3[9];
        
        // get the K matrix for the rodrigues formula
        crossf(zax, vec, k);
        normf(k);
        skewSymf(k, K);
        
        // get K^2
        multf(K, K, Ksq);
        
        // get the angle
        angle = ang(vec, zax);
        
        // compute the parts of the rodrigues formula
        scaleMat(sinf(angle), K, temp);
        scaleMat(1-cosf(angle), Ksq,temp2);
        
        // compute the rotation matrix
        add(temp, temp2, temp3);
        add(I, temp3, R);
    }
}

void printMat(double R[9]) {
    printf("\nRotation matrix is:\n%f %f %f\n%f %f %f\n%f %f %f\n",
           R[0],R[1],R[2],
           R[3],R[4],R[5],
           R[6],R[7],R[8]);
}

void printMatf(const char * name, const float R[9]) {
    printf("\nThe %s matrix is:\n%f %f %f\n%f %f %f\n%f %f %f\n",
           name,
           R[0],R[1],R[2],
           R[3],R[4],R[5],
           R[6],R[7],R[8]);
}

void printVec(const char * name, const double u[3]){
    printf("\nThe %s vector is:\n%lf\n%lf\n%lf\n",name,u[0],u[1],u[2]);
}

void printVecf(const char * name, const float u[3]){
    printf("\nThe %s vector is:\n%f\n%f\n%f\n",name,u[0],u[1],u[2]);
}

void convR(const float R[9], float ans[12]){
    ans[0]=R[0]; ans[1]=R[1]; ans[2]=R[2]; ans[3]=0;
    ans[4]=R[3]; ans[5]=R[4]; ans[6]=R[5]; ans[7]=0;
    ans[8]=R[6]; ans[9]=R[7]; ans[10]=R[8]; ans[11]=0;
}

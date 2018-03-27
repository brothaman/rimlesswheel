#include "helper.h"


void cpy_vec(double *u, double *v, int size) {
	int i;
	for (i=0; i<size; i++)
		v[i] = u[i];
}

void cpy_ivec(int * u, int *v, int size) {
	int i;
	for (i=0; i<size; i++)
		v[i] = u[i];
}

double angle_between(double u[3], double v[3]) {
	int i;
	double mag1=0, mag2=0, dot=0;
	for (i=0; i<3; i++) {
		mag1 = mag1 + u[i]*u[i];
		mag2 = mag2 + v[i]*v[i];
		dot  = dot  + u[i]*v[i];
	}
	return acos(dot/(sqrt(mag1)*sqrt(mag2)));
}

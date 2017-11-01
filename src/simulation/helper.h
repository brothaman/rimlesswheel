#ifndef helper_h
#define helper_h
#include <math.h>
void cpy_vec(double *u, double *v, int size);
void cpy_ivec(int * u, int *v, int size);
double angle_between(double u[3], double v[3]);
void getEulerAngles(int body, double angles[3]);
#endif

# include "vfieldfunc.h"

/* Lorenz Vector Field.

 Input:  (t, Y, p)
    t -- scalar (ignored)
    Y -- phase-space vector [x; y; z]
    p -- parameter vector [s; r; b]

 Output: 3-vector f = [x_dot; y_dot; z_dot] where

   x_dot = -s*x + s*y
   y_dot =  r*x -   y  - x*z
   z_dot =  y*x        - b*z
*/

#define x (Y[0])
#define y (Y[1])
#define z (Y[2])
#define s (params[0])
#define r (params[1])
#define b (params[2])


void vfieldfunc(unsigned ndims,  double t, double* Y, double* params, double* f) {

  f[0] = s*(y-x);
  f[1] = -x*z + r*x  - y; 
  f[2] = x*y - b*z;

} 

/* when zdot = 0 */
void eventfunc (unsigned ndims, double t, double *Y, double *params, 
					   int ievent, double &value, int &isterminal, int &direction)
{
	switch (ievent)
	{
	case 1:
		value = x*y - b*z;
		isterminal = 0;
		direction = 1;
		break;
	}
}


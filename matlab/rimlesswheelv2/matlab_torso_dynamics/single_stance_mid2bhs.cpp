// WITH LU DECOMPOSITION 
// Called by onestepMEXm and has monodromy matrix in it.
// piecewise linear curent for hip and ankle, Current = Constant1 + Constant2*t.
// Copied from singleMEXm.cpp from 20091019Zop
#include "vfieldfunc.h"
#include "matrix.h"
#include <math.h>
#include "mex.h"
#define NMAT 3 //should be atleast nmat+1, here nmat = 2
//#define PI 3.14159265359

double PI = 3.14159265359;

//static double s, r, b;	// These will be initialized by vfieldfuncinit before the integration begins

void reshapeVEC2MAT(int , int ,int , double *, double *);
void reshapeMAT2VEC(int , int , double *, double *);
void zeros(int, int , double *);
void zeros3(int, int, int, double *);
void transpose(int , int , double *);
void inverse(int ,int ,double *,double *);
void multiplyMAT2MAT(int , int , int , int , double *, double *, double *);
void multiplyMAT2VEC(int , int , int , double *, double *, double *);
void subtract(int, int , double *, double *, double *);
void solve_ludecomp(int, double [][NMAT], double [], double []);
void ludecomp(int, double [][NMAT], int []);
void solve(int, double [][NMAT], double [], double [], int []);


void vfieldfunc(unsigned n,  double t, double* y,  mxArray* params, double* f)
{

		double* paramsarray = mxGetPr(params);
        double all_params[12];
        double q1, q2, u1, u2, ud1, ud2;
        
        static double m1, m2, c, w, g, I1, I2, gam, T2;
        static double n_spokes, disturb_ht, l;
        
        int  i, j;
        int nmat = 2; //nmat should be equal to state space else error 12/10/2009
        double M[nmat][nmat], RHS[nmat], Minv[nmat][nmat], udot[nmat];

        double M11, M12, M21, M22;
        double RHS1, RHS2;
   

        // Retrieve parameters
        j = 0;
        for (i=0;i<12;i++)
        {
            all_params[i] = paramsarray[j];
            j = j + 1;
        }
           
           
/* all_parms = [parms.m1 parms.m2 parms.c parms.w parms.l parms.g parms.I1 parms.I2 parms.n ...
        //      parms.gam parms.disturb.height parms.control.T2];*/
      
        m1 = all_params[0]; m2 = all_params[1];
        c = all_params[2]; w = all_params[3];
        l = all_params[4]; g = all_params[5];
        I1 = all_params[6]; I2 = all_params[7];
        n_spokes = all_params[8]; gam = all_params[9];
        disturb_ht = all_params[10]; T2 = all_params[11];
    
    q1    = y[0]   ;  
    u1    = y[1]   ;  
    q2    = y[2]   ;
    u2    = y[3]   ; 


    //mexPrintf("n_spokes = %f\n", n_spokes);
    //mexPrintf("Hello");
    //s = mxGetScalar(mxGetField(params,0,"s"));
    //r = mxGetScalar(mxGetField(params,0,"r"));
    //b = mxGetScalar(mxGetField(params,0,"b"));

//     M11 = I1 + l^2*m1 + l^2*m2 - c*l*m2*cos(q1 - q2) - l*m2*w*sin(q1 - q2);
//     M21 = -l*m2*(c*cos(q1 - q2) + w*sin(q1 - q2));
//     M12 = I2 + c^2*m2 + m2*w^2 - c*l*m2*cos(q1 - q2) - l*m2*w*sin(q1 - q2);
//     M22 = I2 + c^2*m2 + m2*w^2;
//     RHS1 = c*g*m2*sin(gam - q2) - g*m2*w*cos(gam - q2) - g*l*m1*sin(gam - q1) - g*l*m2*sin(gam - q1) - c*l*m2*u1^2*sin(q1 - q2) + c*l*m2*u2^2*sin(q1 - q2) + l*m2*u1^2*w*cos(q1 - q2) - l*m2*u2^2*w*cos(q1 - q2);
//     RHS2 = T2 + c*g*m2*sin(gam - q2) - g*m2*w*cos(gam - q2) - c*l*m2*u1^2*sin(q1 - q2) + l*m2*u1^2*w*cos(q1 - q2);
//  

    
    M11 = I1 + l*l*m1 + l*l*m2 - c*l*m2*cos(q1 - q2) - l*m2*w*sin(q1 - q2);
    M21 = -l*m2*(c*cos(q1 - q2) + w*sin(q1 - q2));
    M12 = I2 + c*c*m2 + m2*w*w - c*l*m2*cos(q1 - q2) - l*m2*w*sin(q1 - q2);
    M22 = I2 + c*c*m2 + m2*w*w;
    RHS1 = c*g*m2*sin(gam - q2) - g*m2*w*cos(gam - q2) - g*l*m1*sin(gam - q1) - g*l*m2*sin(gam - q1) - c*l*m2*u1*u1*sin(q1 - q2) + c*l*m2*u2*u2*sin(q1 - q2) + l*m2*u1*u1*w*cos(q1 - q2) - l*m2*u2*u2*w*cos(q1 - q2);
    RHS2 = T2 + c*g*m2*sin(gam - q2) - g*m2*w*cos(gam - q2) - c*l*m2*u1*u1*sin(q1 - q2) + l*m2*u1*u1*w*cos(q1 - q2);
 
    zeros(nmat,nmat,&M[0][0]);
    M[0][0] = M11;
    M[0][1] = M12;
    M[1][0] = M21;
    M[1][1] = M22;

    RHS[0] = RHS1;
    RHS[1] = RHS2;


    //This inverse matches with matlab inverse to 15 significant digits. 
    inverse(nmat,nmat,&M[0][0],&Minv[0][0]);

    multiplyMAT2VEC(nmat,nmat,nmat,&Minv[0][0],&RHS[0],&udot[0]);

    ud1 = udot[0];
    ud2 = udot[1];

    f[0] = u1;
    f[1] = ud1;
    f[2] = u2;
    f[3] = ud2;

   
} 

void eventfunc (unsigned ndims, double t, double *y, mxArray* params,
					   int ievent, double &value, int &isterminal, int &direction)
{
    
    double q1; //, q2, q3, q4;
    double* paramsarray = mxGetPr(params);
    static double n_spokes, disturb_ht, l;
    double all_params[12];
    int i,j;
    
    j = 0;
    for (i=0;i<12;i++)
    {
       all_params[i] = paramsarray[j];
       j = j + 1;
    }
    l = all_params[4];
    n_spokes = all_params[8];
    disturb_ht = all_params[10];
     
    q1  = y[0]   ; 
    
    //q2    = y[2]   ;
    //q3    = y[4]   ;    
    //q4    = y[6]   ;   
      
    //value = t-0.55;
    //isterminal = 1;
    //direction = 1;
    //n = parms.n;
   // q = x(1);


// %h = parms.l*cos(q) - parms.l*cos(pi/n)+parms.disturb.height; 
// %h = q+pi/n;
// isterminal=1; %= 1 if the integration is to terminate at a zero of this event function, otherwise, 0.
// direction = -1; %= 0 if all zeros are to be located (the default), +1 if only zeros where the event function is increasing, and -1 if only zeros where the event function is decreasing.
    //double n_spoke = 10;
    
	switch (ievent)
	{
	case 0:
        // h = parms.l*cos(q) - parms.l*cos(q+(2*pi/n))+parms.disturb.height;
         value = l*cos(q1)-l*cos(q1+(2*PI/n_spokes)); //+disturb_ht; 
        //value = l2*cos(q1)-l2*cos(q1+(2*PI/n_spokes2)); //+disturb_ht; 
        //mexPrintf("n_spokes = %f; l = %f; value = %f \n", n_spokes,l,value);
        //if (q3<-0.1)
        //    isterminal=1; //Ode should terminate is conveyed by 1, if you put 0 it goes till the final time u specify
        //else
        isterminal=1;
        direction=-1; // The t_final can be approached by any direction is indicated by this
		break;
	} 
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void zeros(int row, int col, double *Mat) //generate matrix full of zeros
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
	int i,j;
	for (i=0;i<row;i++)
		for (j=0;j<col;j++)
				*(Mat + i*col+j) = 0.0;		
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void zeros3(int no, int row, int col, double *Mat) //generate matrix full of zeros
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
	int i,j,k;
	for (k=0;k<no;k++) 
		for (i=0;i<row;i++)
			for (j=0;j<col;j++)
				*(Mat + k*row*col + i*col+j) = 0.0;		
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void subtract(int row, int col, double *ptr_A, double *ptr_B, double *ptr_Difference) //subtract two matrices
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
int i, j;
double A[row][col], B[row][col];

	for (i=0;i<row;i++)
		for (j=0;j<col;j++)
		{ A[i][j] = *(ptr_A + i*col+j); B[i][j] = *(ptr_B + i*col+j);}		

	for (i=0;i<row;i++)
		for (j=0;j<col;j++)
			*(ptr_Difference + i*col+j) = A[i][j] - B[i][j];
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void multiplyMAT2MAT(int row_A, int col_A, int row_B, int col_B, double *ptr_A, double *ptr_B, double *ptr_Multiply) //Multiply two matrices
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
int i, j, p;
double A[row_A][col_A], B[row_B][col_B], sum;

if (col_A != row_B)
	{ printf("ERROR: Columns of A should equal rows of B \n"); exit(1); }

	for (i=0;i<row_A;i++)
		for (j=0;j<col_A;j++)
			A[i][j] = *(ptr_A + i*col_A+j);
		
	for (i=0;i<row_B;i++)
		for (j=0;j<col_B;j++)
				 B[i][j] = *(ptr_B + i*col_B+j);		

	for (i=0;i<row_A;i++)
		for (j=0;j<col_B;j++)
		{
			sum = 0;
			for (p=0;p<col_A;p++)
				sum = sum + A[i][p]*B[p][j];
			
			*(ptr_Multiply + i*col_B+j) = sum;
		}

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void multiplyMAT2VEC(int row_A, int col_A, int row_b, double *ptr_A, double *ptr_b, double *ptr_x) //Multiply matrix to vector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
int i, j, p;
double A[row_A][col_A], b[row_b], sum;

if (col_A != row_b)
	{ printf("ERROR: Columns of A should equal rows of b \n"); exit(1); }

	for (i=0;i<row_A;i++)
		for (j=0;j<col_A;j++)
			A[i][j] = *(ptr_A + i*col_A+j);
	
	for (i=0;i<row_b;i++)
			b[i] = *(ptr_b + i);		

	for (i=0;i<row_A;i++)
		{
			sum = 0.0;
			for (p=0;p<col_A;p++)
				sum = sum + A[i][p]*b[p];
			
			*(ptr_x + i) = sum;
		}

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void transpose(int row, int col, double *ptr_A) //Take transpose of a matrix
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
	int i,j;
	double A[col][row]; //Is the transpose
	
	if (row != col)
	{ printf("ERROR: Transpose currently works only on square matrices \n"); exit(1); }
	
	for (i=0;i<row;i++)
		for (j=0;j<col;j++)
			A[j][i] = *(ptr_A + i*col+j); //get the transpose
			
	for (i=0;i<row;i++)
		for (j=0;j<col;j++)
			*(ptr_A + i*col+j) = A[i][j]; //stash back and send
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void reshapeMAT2VEC(int row,int col, double *ptr_A, double *ptr_a) //Matrix to vector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
	int i,j;
	double A[row][col];
	
	for (i=0;i<row;i++)
		for (j=0;j<col;j++)
			A[j][i] = *(ptr_A + i*col+j); //get the transpose
			
	for (i=0;i<row;i++)
		for (j=0;j<col;j++)
			*(ptr_a + i*col+j) = A[i][j]; //stash back and send

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void reshapeVEC2MAT(int row_a, int row_A,int col_A, double *ptr_a, double *ptr_A) //Vector to a matrix
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
int i, j, k;
double A[col_A][row_A]; //We are going to first assemble the transpose

if (row_a != row_A*col_A)
	{ printf("ERROR: Checks size of input matrices \n"); exit(1); }
	
	k = 0;
	for (i=0;i<row_A;i++)
		for (j=0;j<col_A;j++)
		{		
			A[j][i] = *(ptr_a + k); //get the transpose
			k = k + 1;
		}
		
	for (i=0;i<row_A;i++)
		for (j=0;j<col_A;j++)
			*(ptr_A + i*col_A+j) = A[i][j]; //stash back and send
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void inverse(int row,int col,double *ptr_A,double *ptr_Ainv) //invert matrix
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
int i, j, p,q;
double A[NMAT][NMAT], x[NMAT], b[NMAT]; //should be NMAT else will give error
double Ainv[row][col];

if (row != col)
	{ printf("ERROR: Matrix is not square and cannot be inverted \n"); exit(1); }

	for (i=1;i<=row;i++)
	{
			for (j=1;j<=row;j++)	
				{
				x[j] = 0;
			    if (i==j) b[j] = 1.0; else b[j] = 0.0;
				}
		   
		   	for (p=0;p<row;p++)
				for (q=0;q<col;q++)
					A[p+1][q+1] = *(ptr_A + p*col+q);	//Matrix starts from A[1][1]...
					
			solve_ludecomp(row, A, b, x);
			for (j=1;j<=row;j++)
				Ainv[i-1][j-1] = x[j];
	}		 
			
	transpose(row,col,&Ainv[0][0]);
	
	for (i=0;i<row;i++)
		for (j=0;j<col;j++)
			*(ptr_Ainv + i*row+j) = Ainv[i][j];
	
}

////////////////////////////////////////////////
//////////// Solve Ax = b //////////////////////
///////////////////////////////////////////////

/*
  Taken from http://comp.cs.ehime-u.ac.jp/~ogata/nac/index.html
  solve a linear equation Ax = b 
  by a LU decomposition PA = LU (with partial pivoting), 
  where L is a lower triangular matrix, 
  U is a upper triangular matrix and 
  P is a permutation matrix, 
  and estimate the condition number of A 
  by Natori-Tsukamoto's method
  
  copyright : Hidenori Ogata, 6 April 2004, ver.1
                             12 April 2004, ver.1.01
  
  (revisions)
  ver.1.01: Mistakes in the comment here are corrected.
  
  (usage)
  solve_ludecomp(nmat, a, b, x);
  ... if the condition number is not needed
  solve_cond_ludecomp(nmat, a, b, x, &cond);
  ... if the condition number is needed
  
  The parameters are as follows.
  (input)
  nmat    int             : the matrix size (must be < NMAT)
  a       double [][NMAT] : the coefficient matrix
  b       double []       : the r.h.s. vector
  (output)
  x       double []       : the solution
  cond    double *        : the condition number of A
  (remark)
  After the computation, 
  the elements of L are stored in the lower triangular part of the array 
  a[i][j], i > j, and 
  the elements of U are stored in the upper triangular part of the array 
  a[i][j], i <= j. 
  
*/

/*
  solve a linear equation Ax = b by the Gauss elimination method 
  with partial pivotting
  (input)
  nmat    int             : the matrix size (must be < NMAT)
  a       double [][NMAT] : the coefficient matrix
  b       double []       : the r.h.s. vector
  (output)
  x       double []       : the solution
  (remark)
  After the computation by the function "ludecomp", 
  the elements of L are stored in the lower triangular part of the array 
  a[i][j], i > j, and 
  the elements of U are stored in the upper triangular part of the array 
  a[i][j], i <= j. 
*/
void solve_ludecomp(int nmat, double a[][NMAT], double b[], double x[])
{
  int i, j;
  int p[NMAT];	/* index vector for partial pivotting */
  double a0[NMAT][NMAT];
  
  if (nmat >= NMAT)
    {
      mexPrintf("nmat (the matrix size)=%d\n", nmat);
      mexPrintf("nmat must be <= %d\n", NMAT-1);
      exit(0);
    }
  
  ludecomp(nmat, a, p);
  
  solve(nmat, a, b, x, p);
}
/*
  LU decomposition of the matrix A
  with partial pivotting
  
  (remark)
  After the computation by the function "ludecomp", 
  the elements of L are stored in the lower triangular part of the array 
  a[p[i]][j], i > j, and 
  the elements of U are stored in the upper triangular part of the array 
  a[p[i]][j], i <= j. 
*/
void ludecomp(int nmat, double a[][NMAT], int p[])
{
  int i, j, k, k1, l, kk;
  double akmax;
  
  for (i=1; i<=nmat; ++i)
    p[i] = i;
	
  /*
    the Gauss elimination 
  */
  for (k=1; k<=nmat-1; ++k)
    {
      k1 = k + 1;
      /*
	partial pivotting
      */
      l = k;
      akmax = fabs(a[p[k]][k]);
      for (i=k1; i<=nmat; ++i)
	if (fabs(a[p[i]][k]) > akmax)
	  {
	    l = i;
	    akmax = fabs(a[p[i]][k]);
	  }
      if (l > k)
	{
	  kk = p[k];
	  p[k] = p[l];
	  p[l] = kk;
	}
      
      for (i=k1; i<=nmat; ++i)
	{
	  if (a[p[k]][k] != 0.0)
	    {
	      a[p[i]][k] /= a[p[k]][k];
	      for (j=k1; j<=nmat; ++j)
		a[p[i]][j] -= a[p[i]][k] * a[p[k]][j];
	    }
	  else
	    {
	      mexPrintf("Step %2d\n", k);
	      mexPrintf("The (%2d,%2d)-element of the matrix is zero.\n", k, k);
	      exit(0);
	    }
	}
    }
}

/*
  solve the equation Ax = b 
  by solving the simultaneous linear equations 
  Ly = Pb, Ux = y.
*/
void solve(int nmat, double a[][NMAT], double b[], double x[], int p[])
{
  double y[NMAT];
  int i, j;
  /*
    solve Ly = Pb by forward substitution
  */
  for (i=1; i<=nmat; ++i)
    {
      y[i] = b[p[i]];
      for (j=1; j<=i-1; ++j)
	y[i] -= a[p[i]][j] * y[j];
    }
  /*
    solve Ux = y by backward substitution 
  */
  for (i=nmat; i>=1; --i)
    {
      x[i] = y[i];
      for (j=nmat; j>=i+1; --j)
        x[i] -= a[p[i]][j] * x[j];
      x[i] /= a[p[i]][i];
    }
}
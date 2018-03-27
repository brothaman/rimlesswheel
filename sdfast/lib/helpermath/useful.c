
//Example usage to get direction cosines
//char name_DC_RFOOT[]="DC_RFOOT";
//display(3, 3, &dircos[0][0], name_DC_RFOOT);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void display(int row, int col, double *Mat, char *name) //display the given matrix
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
	
    int i, j;
    
    for(i=0; i<strlen(name); i++)
    {
        printf("%c",name[i]);
    }
    printf("=[ ... \n");
        
	for (i=0;i<row;i++)
    {
		for (j=0;j<col;j++)
			printf("%2.3f \t",*(Mat + i*col+j)); //advance one column at a time
        printf("\n");
    }
    printf("];\n \n");
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void display2(int row, int col, double *Mat, char *name) //display the given matrix
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
	
    int i, j;
    
//    for(i=0; i<strlen(name); i++)
//    {
//        printf("%c",name[i]);
//    }
    //printf("=[ ... \n");
	
	for (i=0;i<row;i++)
    {
		for (j=0;j<col;j++)
			printf("%g ",*(Mat + i*col+j)); //advance one column at a time
        printf("; "); //printf("\n");
    }
//    printf("];\n \n");
};




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void rotation(int axis, double angle, double *Mat) //rotate a matrix along given axis by a given angle.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
	
	int i,j;
	int row=3, col=3;
	double c = cos(angle), s = sin(angle);
	
	for (i=0;i<row;i++)
		for (j=0;j<col;j++)
			*(Mat + i*col+j) = 0.0;	
	
	if (axis==1)
	{
		i=0; j=0; *(Mat + i*col+j) = 1.0;
		i=1; j=1; *(Mat + i*col+j) = c;
		i=1; j=2; *(Mat + i*col+j) = -s;
		i=2; j=1; *(Mat + i*col+j) = s;
		i=2; j=2; *(Mat + i*col+j) = c;
	}
	else if (axis == 2)
	{
		i=1; j=1; *(Mat + i*col+j) = 1.0;
		i=0; j=0; *(Mat + i*col+j) = c;
		i=0; j=2; *(Mat + i*col+j) = -s;
		i=2; j=0; *(Mat + i*col+j) = s;
		i=2; j=2; *(Mat + i*col+j) = c;
	}
	else if (axis == 3)
	{
		i=2; j=2; *(Mat + i*col+j) = 1.0;
		i=0; j=0; *(Mat + i*col+j) = c;
		i=0; j=1; *(Mat + i*col+j) = -s;
		i=1; j=0; *(Mat + i*col+j) = s;
		i=1; j=1; *(Mat + i*col+j) = c;
	}
	else
	{
		printf("\nERROR in rotation: The axis number for rotation are outside bounds \n");
	}
	
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void multiplySCALAR2MAT(int row, int col, double *ptr_A, double scalar, double *ptr_Result) //Multiply scaler to matrix
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
	int i, j;
	double A[row][col];
	
	for (i=0;i<row;i++)
		for (j=0;j<col;j++)
			A[i][j] = *(ptr_A + i*col+j);
	
    for (i=0;i<row;i++)
		for (j=0;j<col;j++)
			*(ptr_Result + i*row+j) = scalar*A[i][j];
    
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void multiplyMAT2VEC(int row_A, int col_A, int row_b, double *ptr_A, double *ptr_b, double *ptr_x) //Multiply matrix to vector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
	int i, j, p;
	double A[row_A][col_A], b[row_b], sum;
	
	if (col_A != row_b)
	{ printf("ERROR multiplyMAT2VEC: Columns of A should equal rows of b \n");}// exit(1); }
	
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
double normVEC(int row, double *ptr_b) //Norm of a vector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
	int i, j;
	double b[row], sum=0;
	
	
	for (i=0;i<row;i++)
		b[i] = *(ptr_b + i);		
	
    for (i=0;i<row;i++)
        sum = sum + b[i]*b[i];
    
    return sqrt(sum);
    
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void normalizeVEC(int row, double *ptr_b) //Normalize the vector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
	int i, j;
	double b[row], sum=0;
	double norm;
	
	for (i=0;i<row;i++)
		b[i] = *(ptr_b + i);
	
	norm = normVEC(row, &b[0]);
	
	if (norm!=0)
		for (i=0;i<row;i++)
			b[i] = b[i]/norm;
	
	for (i=0;i<row;i++)
			*(ptr_b + i) = b[i];	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void multiplyMAT2MAT(int row_A, int col_A, int row_B, int col_B, double *ptr_A, double *ptr_B, double *ptr_Multiply) //Multiply two matrices
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
	int i, j, p;
	double A[row_A][col_A], B[row_B][col_B], sum;
	
	if (col_A != row_B)
	{ printf("ERROR in multiplyMAT2MAT: Columns of A should equal rows of B \n"); //exit(1); 
	}
	
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
void transpose(int row, int col, double *ptr_A, double *ptr_At) //Take transpose of a matrix
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
	int i,j;
	double At[col][row]; //Is the transpose
	
	//if (row != col)
	//{ printf("ERROR: Transpose currently works only on square matrices \n"); exit(1); }
	
	for (i=0;i<row;i++)
		for (j=0;j<col;j++)
        {
			At[j][i] = *(ptr_A + i*col+j); //get the transpose
            
        }
    
//    for (i=0;i<col;i++)
//    {
//		for (j=0;j<row;j++) 
//        {
//            printf("%f ",At[i][j]);
//        }
//        printf("\n");
//    }
    
	for (i=0;i<col;i++)
		for (j=0;j<row;j++)
			*(ptr_At + i*row+j) = At[i][j]; //stash back and send
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void inverse(int row,int col,double *ptr_A,double *ptr_Ainv) //invert matrix
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
    int i, j, p,q;
    double A[NMAT][NMAT], x[NMAT], b[NMAT]; //should be NMAT else will give error
    double Ainv[row][col];
    double Atinv[col][row];
    
    if (row != col)
	{ printf("ERROR in inverse: Matrix is not square and cannot be inverted \n"); exit(1); }
    
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
            Atinv[i-1][j-1] = x[j];
	}		 
    
	transpose(row,col,&Atinv[0][0],&Ainv[0][0]);
	
	for (i=0;i<row;i++)
		for (j=0;j<col;j++)
			*(ptr_Ainv + i*row+j) = Ainv[i][j];
	
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void add(int row, int col, double *ptr_A, double *ptr_B, double *ptr_Sum) //add two matrices
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
    int i, j;
    double A[row][col], B[row][col];
    
	for (i=0;i<row;i++)
		for (j=0;j<col;j++)
		{ A[i][j] = *(ptr_A + i*col+j); B[i][j] = *(ptr_B + i*col+j);}		
    
	for (i=0;i<row;i++)
		for (j=0;j<col;j++)
			*(ptr_Sum + i*col+j) = A[i][j] + B[i][j];
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void identity(int row, double *Mat) //generate identity matrix
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
{
	int i,j;
	for (i=0;i<row;i++)
		for (j=0;j<row;j++)
		{
			if (i==j)
				*(Mat + i*row+j) = 1.0;
			else
				*(Mat + i*row+j) = 0.0;
		}		
}

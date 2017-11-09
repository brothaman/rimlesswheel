#include "link.h"

/* 
 *
 * CONSTRUCTORS 
 *
 */
LINK::LINK() {
	// set the name to a standard value
	this->_name = (char *)malloc(5);
	this->_name = "link";

	// copy the starting and ending points
	this->_0[0] = 0;
	this->_0[1] = 0;
	this->_0[2] = 0;

	this->_1[0] = 0;
	this->_1[1] = 0;
	this->_1[2] = 0;

	// initialize the orientation vector
	for (int i=0; i<9; i++)
		this->_R[i] = 0;

	// set the geometry name
	this->_geometry = (char *)malloc(8);
	this->_geometry = "capsule";
}
LINK::LINK( char * name, float body_center[3], float body_dimensions[3]) {
	// copy the string name into the name value
	this -> _name = (char *)malloc( strlen(name) +1);
	strcpy(this->_name, name);

	// copy body positional data
	this->center[0] = body_center[0];
	this->center[1] = body_center[1];
	this->center[2] = body_center[2];

	// copy body dimensional data
	this->length = body_dimensions[0];
	this->width  = body_dimensions[1];
	this->depth  = body_dimensions[2];
}



/* 
 *
 * Will be getting rid of the constructors using the start and end points
 *
 *
 */

LINK::LINK( char * name, float startPoint[3], float endPoint[3], char * shape) {
	// copy the string name into the name value
	this -> _name = (char *)malloc( strlen(name) +1);
	strcpy(this->_name, name);

	// copy the starting and ending points
	this->_0[0] = startPoint[0];
	this->_0[1] = startPoint[1];
	this->_0[2] = startPoint[2];

	this->_1[0] = endPoint[0];
	this->_1[1] = endPoint[1];
	this->_1[2] = endPoint[2];
	// fill the vectors with data

	// initialize the orientation vector
	for (int i=0; i<9; i++)
		this->_R[i] = 0;

	// copy the string shape into the private geometry
	this -> _geometry = (char *)malloc( strlen(shape) +1);
	strcpy(this->_geometry, shape);
}

LINK::LINK( float startPoint[3], float endPoint[3], char * shape) {
	// set the name to a standard value
	this->_name = (char *)malloc(5);
	this->_name = "link";

	// copy the starting and ending points
	this->_0[0] = startPoint[0];
	this->_0[1] = startPoint[1];
	this->_0[2] = startPoint[2];

	this->_1[0] = endPoint[0];
	this->_1[1] = endPoint[1];
	this->_1[2] = endPoint[2];
	// initialize the orientation vector
	for (int i=0; i<9; i++)
		this->_R[i] = 0;

	// copy the string shape into the private geometry
	this -> _geometry = (char *)malloc( strlen(shape) +1);
	strcpy(this->_geometry, shape);
}

LINK::LINK( float startPoint[3], float endPoint[3]) {
	// set the name to a standard value
	this->_name = (char *)malloc(5);
	this->_name = "link";

	// copy the starting and ending points
	this->_0[0] = startPoint[0];
	this->_0[1] = startPoint[1];
	this->_0[2] = startPoint[2];

	this->_1[0] = endPoint[0];
	this->_1[1] = endPoint[1];
	this->_1[2] = endPoint[2];
	
	// initialize the orientation vector
	for (int i=0; i<9; i++)
		this->_R[i] = 0;

	// set the geometry name
	this->_geometry = (char *)malloc(8);
	this->_geometry = "capsule";
}

LINK::LINK(LINK &link) {
	*this = link;
}

/********************************************************
 *                   FUNCTION MEMBERS
 *
 *
 *
 *                   FUNCTION MEMBERS 
 *********************************************************/
void LINK::calculateOrientation(arma::Mat<float> &R) {
}

// void getters
void LINK::getStartPoint( float p[3]) {
	p[0] = this->_0[0];
	p[1] = this->_0[1];
	p[2] = this->_0[2];
}
void LINK::getStartPoint( arma::fmat p) {
	p = arma::fmat(this->_0,3,1);
}
void LINK::getEndPoint( float p[3]) {
	p[0] = this->_1[0];
	p[1] = this->_1[1];
	p[2] = this->_1[2];
}
void LINK::getEndPoint( arma::fmat p) {
	p = arma::fmat(this->_1,3,1);
}
void LINK::getName( char * name) {
	int sz = strlen(this -> _name);
	name = new char[sz +1];
	strcpy(name, this->_name);
}
void LINK::getGeometry( char * shape) {
	int sz = strlen(this -> _geometry);
	shape = (char *)malloc(sz+1);
	shape = strcpy(shape, this->_geometry);
}
void LINK::getOrientation( float R[12]) {
	R[3]=R[7]=R[11] = 0;
	R[0] = this->_R[0]; R[1] = this->_R[1]; R[2] = this->_R[2];
	R[4] = this->_R[3]; R[5] = this->_R[4]; R[6] = this->_R[5];
	R[8] = this->_R[6]; R[9] = this->_R[7]; R[10]= this->_R[8];
}

void LINK::getOrientation( arma::fmat p) {
	p = arma::fmat(this->_R,3,3);
}

// setters
void LINK::setStartPoint( const float p[3]){
	for (int i=0; i<3; i++) 
		this->_0[i] = p[i];
}
void LINK::setEndPoint( const float p[3]){
	for( int i=0; i<3; i++)
		this->_1[i] = p[i];
}
void LINK::setName( const char * name){
	
}
void LINK::setOrientation( const float e[3]) {
	arma::Mat<float> R = euler_to_rotation( e);
	cpyfvec(R.memptr(), this->_R, 9);
}
void LINK::setOrientation( const float phi, const float theta, const float psi) {
	float e[3] = {phi, theta, psi};
	arma::Mat<float> R = euler_to_rotation( e);
	cpyfvec(R.memptr(), this->_R, 9);
}
void LINK::setGeometry( const char * shape){}

/* NON MEMBER FUNCTION
 *
 *
 *
 *
 * NON MEMBER FUNCTION */

void cpyfvec(float * a, float * b, int n=3) {
	for (int i = 0; i<n; i++)
		b[i] = a[i];
}

arma::Mat<float> rotx( float angle) {
	// rotation matrix to return
	arma::Mat<float> R(3,3);
	
	// if its empty and already filled
	R.fill(0);

	// assign values to correct positions
	R(0,0) = 1;
	R(1,1) = R(2,2) = cosf(angle);
	R(1,2) = -sinf(angle);
	R(2,1) = sinf(angle);

	return R;
}

arma::Mat<float> roty( float angle) {
	// rotation matrix to return
	arma::Mat<float> R(3,3);
	
	// if its empty and already filled
	R.fill(0);

	// assign values to correct positions
	R(1,1) = 1;
	R(0,0) = R(2,2) = cosf(angle);
	R(0,2) = sinf(angle);
	R(2,0) = -sinf(angle);

	return R;
}

arma::Mat<float> rotz( float angle) {
	// rotation matrix to return
	arma::Mat<float> R(3,3);
	
	// if its empty and already filled
	R.fill(0);

	// assign values to correct positions
	R(2,2) = 1;
	R(0,0) = cosf(angle);
 	R(1,1) = cosf(angle);
	R(0,1) = -sinf(angle);
	R(1,0) = sinf(angle);

	return R;
}

void skewSym(arma::Mat<float> &v, arma::Mat<float> &R) {
	// fill zeros across the diagnoal
	R(0,0) = R(1,1) = R(2,2) = 0;

	// fill the rest of the skew sym
	R(1,0) = -v(2);
	R(0,1) =  v(2);
	R(0,2) =  v(1);
	R(2,0) = -v(1);
	R(1,2) = -v(0);
	R(2,1) =  v(0);
}

void LINK::orientation(float thetax, float thetay, float thetaz) {
	//this->_R = rotx(thetax) * roty(thetay) * rotz(thetaz);
}

void rodrigues_2pt_rot( 
		const arma::Mat<float> k[3], const arma::Mat<float> v[3], arma::Mat<float> &R) {
	arma::Mat<float> K(3,3,arma::fill::zeros);
	
}

arma::Mat<float> euler_to_rotation(const float euler_angles[3]) {
	// psi
	float cs = cosf(euler_angles[2]);
	float ss = sinf(euler_angles[2]);

	// theta
	float ct = cosf(euler_angles[1]);
	float st = sinf(euler_angles[1]);

	// phi
	float cp = cosf(euler_angles[0]);
	float sp = sinf(euler_angles[0]);

	// rotation matrix ref: http://mathworld.wolfram.com/EulerAngles.html
	arma::fmat R = {
		{ cs*cp - ct*sp*ss, cp*st + ct*cp*ss, ss*st},
		{-ss*cp - ct*sp*cs,-ss*cp + ct*cp*cs, cs*st},
		{ st*sp,-st*cp, ct}
	};

	return R;
}
void quaternion_to_mat(float q[4], arma::Mat<float> R) {
	// row 1
	R(0,0) = 1 - 2*q[1]*q[1] - 2*q[2]*q[2];
	R(0,1) = 2*q[0]*q[1] + 2*q[3]*q[2];
	R(0,2) = 2*q[0]*q[2] - 2*q[3]*q[1];

	// row 2
	R(1,0) = 2*q[0]*q[1] - 2*q[3]*q[2];
	R(1,1) = 1 - 2*q[0]*q[0] - 2*q[2]*q[2];
	R(1,2) = 2*q[1]*q[2] + 2*q[3]*q[0];

	// row 3
	R(2,0) = 2*q[0]*q[2] + 2*q[3]*q[1];
	R(2,1) = 2*q[1]*q[2] - 2*q[3]*q[0];
	R(2,2) = 1 - 2*q[0]*q[0] - q[1]*q[1];
}

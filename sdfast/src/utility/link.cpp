#include "link.h"

/* 
 *
 * CONSTRUCTORS 
 *
 */
LINK::LINK() {
	// set the name to a standard value
	strcpy(this->_name, "link");

	// copy the starting and ending points
	this->center[0] = 0;
	this->center[1] = 0;
	this->center[2] = 0;

	this->length = 0;
	this->width = 0;
	this->depth = 0;

	// initialize the orientation vector
	for (int i=0; i<9; i++)
		this->_R[i] = 0;
	this->_R[0] = this->_R[4] = this->_R[8] = 1;

	// set the geometry name
//	this->_geometry = (char *)malloc(8);
	strcpy(this->_geometry,"capsule");
}
LINK::LINK( 
		char name[40],
		char geometry[40],
		float body_center[3],
		float orientation[3],
		float body_dimension[3]
		) 
{
	// copy the string name into the name value
	strcpy(this->_name, name);

	// copy the string geometry into the data member
//	this->_geometry = (char *)malloc(strlen(geometry)+1);
	strcpy(this->_geometry, geometry);

	// copy body positional data
	this->center[0] = body_center[0];
	this->center[1] = body_center[1];
	this->center[2] = body_center[2];

	// copy body dimensional data
	this->length = body_dimension[0];
	this->width  = body_dimension[1];
	this->depth  = body_dimension[2];

	// set the orientation using provided euler angles
	LINK::setOrientation( orientation);
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
void LINK::getName( char name[40]) {
//	name = (char *)malloc( sizeof(char)*(strlen(this->_name)+1));
	strcpy(name, this->_name);
}

void LINK::getGeometry( char geometry[40]) {
//	geometry = (char *)malloc( sizeof(char)*strlen(this->_geometry));
	strcpy(geometry, this->_geometry);
}

void LINK::getCenter(float r[3]) {
	r[0] = this->center[0];
	r[1] = this->center[1];
	r[2] = this->center[2];
}
void LINK::getDimensions(float r[3]) {
	r[0] = this->length;
	r[1] = this->width;
	r[2] = this->depth;
}
void LINK::getOrientation(float r[12]) {
	r[0] = this->_R[0];
	r[1] = this->_R[1];
	r[2] = this->_R[2];
	r[3] = 0;

	r[4] = this->_R[3];
	r[5] = this->_R[4];
	r[6] = this->_R[5];
	r[7] = 0;

	r[8] = this->_R[6];
	r[9] = this->_R[7];
	r[10] = this->_R[8];
	r[11] = 0;
}

/* SETTERS
 *
 * 
 *
 * SETTERS */

void LINK::setName( const char name[40]){
//	this->_name = (char *)malloc( sizeof(char)*strlen(name)+1);
	strcpy(this->_name, name);
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
void LINK::setGeometry( const char shape[40]){
//	this->_geometry = (char *)malloc( sizeof(char)*strlen(shape)+1);
	strcpy(this->_geometry, shape);
}

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

void rodrigues_2pt_rot( 
		const arma::Mat<float> k[3], const arma::Mat<float> v[3], arma::Mat<float> &R) {
	arma::Mat<float> K(3,3,arma::fill::zeros);
	
}

arma::Mat<float> euler_to_rotation(const float euler_angles[3]) {
	// psi
	float cpsi = std::cos(euler_angles[2]);
	float spsi = std::sin(euler_angles[2]);

	// theta
	float cthe = std::cos(euler_angles[1]);
	float sthe = std::sin(euler_angles[1]);

	// phi
	float cphi = std::cos(euler_angles[0]);
	float sphi = std::sin(euler_angles[0]);

/*	// DEBUG out put all the information coming in or going out
	std::cout << std::cos(0) << ", " << std::sin(0) << std::endl;
	std::cout << euler_angles[0] << ", " << euler_angles[1] << ", " << euler_angles[2] << std::endl;
	std::cout << cpsi << ", " << spsi << std::endl;
	std::cout << cpsi << ", " << spsi << std::endl;

	std::cout << cthe << ", " << sthe << std::endl;
	std::cout << cthe << ", " << sthe << std::endl;

	std::cout << cphi << ", " << sphi << std::endl;
	std::cout << cphi << ", " << sphi << std::endl;
*/
	// rotation matrix ref: http://mathworld.wolfram.com/EulerAngles.html
	arma::fmat R = {
		{ cpsi*cphi - cthe*sphi*spsi, cpsi*sthe + cthe*cphi*spsi, spsi*sthe},
		{-spsi*cphi - cthe*sphi*cpsi,-spsi*sphi + cthe*cphi*cpsi, cpsi*sthe},
		{ sthe*sphi, -sthe*cphi, cthe}
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

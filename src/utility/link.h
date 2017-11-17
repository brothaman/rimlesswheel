#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <cstring>
#include <armadillo>

class LINK {
	public:
		// Constructors
		LINK();
		LINK(
				char * name, 
				char * geometry, 
				float center[3], 
				float orientation[3], 
				float dimension[3]
				);
		LINK( float body_center[3]);
		LINK(LINK &link);

		// void getters
		void getName( char * name);
		void getGeometry( char * geometry);
		void getCenter(float r[3]);
		void getDimensions(float r[3]);
		void getOrientation(float r[12]);

		// setters
		void setName( const char * name);
		void setGeometry( const char * shape);
		void setOrientation( const float e[3]);
		void setOrientation( const float phi, const float theta, const float psi);
		void setDimensions(const float dims[3]);

	private:
		// private data members
		char * _name;
		char * _geometry;

		// info necessary for drawstuff
		float center[3];
		float length;
		float width;
		float depth;
		float _R[9];

		// private functional members
		void calculateOrientation(arma::Mat<float> &R);
		void calculateLength();
};

void cpyfvec(float * a, float * b, int n); 
arma::Mat<float> rotx( float angle);
arma::Mat<float> roty( float angle);
arma::Mat<float> rotz( float angle);
arma::Mat<float> euler_to_rotation(const float euler_angles[3]);
void rodrigues_2pt_rot( 
		const arma::Mat<float> k[3], 
		const arma::Mat<float> v[3], 
		arma::Mat<float> &R);
void convR(const arma::Mat<float> &R, float ans[12]);
void quaternion_to_mat(float quat, arma::Mat<float> R);

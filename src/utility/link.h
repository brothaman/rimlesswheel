#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <cstring>
#include <armadillo>

class LINK {
	public:
		// Constructors
		LINK();
		LINK(char * _name, float startPoint[3], float endPoint[3], char * shape);
		LINK(float startPoint[3], float endPoint[3], char * shape);
		LINK(float startPoint[3], float endPoint[3]);
		LINK(LINK &link);

		// void getters
		void getStartPoint( float p[3]);
		void getStartPoint( arma::fmat p);
		void getEndPoint( float p[3]);
		void getEndPoint( arma::fmat p);
		void getName( char * name);
		void getGeometry( char * shape);
		void getOrientation( float R[12]);
		void getOrientation( arma::fmat p);

		// setters
		void setStartPoint( const float p[3]);
		void setEndPoint( const float p[3]);
		void setName( const char * name);
		void setOrientation( const float e[3]);
		void setOrientation( const float phi, const float theta, const float psi);
		void setGeometry( const char * shape);

		void orientation(float thetax, float thetay, float thetaz);

	private:
		// private data members
		char * _name;
		char * _geometry;
		float _0[3];		// the zeroth point of the link
		float _1[3];		// the end point of the link
		// info necessary for drawstuff
		float center[3];
		float _length;
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

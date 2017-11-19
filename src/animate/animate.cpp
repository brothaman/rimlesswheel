//
//  main.c
//  animate
//
//  Created by Robert Brothers on 4/22/17.
//  Copyright © 2017 Robert Brothers. All rights reserved.
//

/*****************************************************************************/
#define XX 0
#define YY 1
#define ZZ 2
#define XXFLIP -
#define PI 3.14159265
/*****************************************************************************/
#include <armadillo>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <string.h>
#ifdef WIN32
#include <direct.h>
#define CWD _getcwd(NULL, 0)
#else
#include <unistd.h>
#define CWD getcwd(NULL, 0)
#endif

#include "drawstuff.h" /* ODE Graphics stuff */
#include "drawstuff-cga.h" /* CGA stuff to make things clearer */
#include "mmath.h"
#include "drawings.hpp"
#include "link.h"


/*****************************************************************************/

/*****************************************************************************/

// ************ Change this as per the problem being solved *********//
float x,y,z;
float point[3], p1[3], p2[3], angles[2];
float length;
static float xyz[3];
static float hpr[3];
float translate = 0.0f;
double normal_speed = 0;//(STEPS*1e6)168.0*1e6/TOTAL_TIME;
double slomo = 0;//2e8/180;
double videospeed = normal_speed;
int view = 0;
LINK * links;
unsigned int sz;

// *********************************************************************************** //


static void read_data(char * fname)
{
	/*
	 * this function will pull link a binary dat file containing links with body positions 
	 * and orientations to produce
	 */
	int file_length;
	float p[3];
	char str[40];
	std::streampos size;
	std::fstream inputFile(fname, std::ios::in|std::ios::binary);

	// make sure that number of entries equals the number of steps
	if(inputFile) {
		inputFile.seekg(0,std::ios::end);
		sz = (unsigned int)inputFile.tellg()/sizeof(LINK);
		inputFile.seekg(std::ios::beg);

		std::cout << sz << std::endl;
		links = new LINK[sz];
		for (int i=0; i<sz; i++)
			inputFile.read( reinterpret_cast<char *>( &links[i]), sizeof(LINK) );
		
		links[8].getName(str);
		std::cout << "Before getCenter()" << std::endl;
		links[8].getCenter(p);
		std::cout << "After getCenter() attempting to print out variables " << std::endl;
		std::cout << p[0] << ", " << p[1] << ", " << p[2] << std::endl;
		links[8].getDimensions(p);
		std::cout << p[0] << ", " << p[1] << ", " << p[2] << std::endl;

	} else{
		std::cout << "FILE NOT FOUND" << std::endl;
	}
}

/***************************************************************************************/

static void start()
{
    // set up view point
    switch (view) {
        case 0: // front
            xyz[0] = 0.0f;
            xyz[1] = 15.0f;
            xyz[2] = translate+0.5f;
            hpr[0] = -90.0f;
            hpr[1] = 0.0f;
            hpr[2] = 0.0f;
            break;
        case 1: // top
            xyz[0] = 6.0f;
            xyz[1] = 0.0f;
            xyz[2] = -1.0f;
            hpr[0] = 180.0f;
            hpr[1] = -30.0f;
            hpr[2] = 0.0f;
            break;
        case 2:
            xyz[0] = 2.5f;
            xyz[1] = 0.0f;
            xyz[2] = translate;
            hpr[0] = 180.0f;
            hpr[1] = 0.0f;
            hpr[2] = 0.0f;
            break;
        case 3:
            xyz[0] = -6.0f;
            xyz[1] = 0.0f;
            xyz[2] = 2.0f;
            hpr[0] = 0.0f;
            hpr[1] = 0.0f;
            hpr[2] = 0.0f;
            break;
            
        default:
            break;
    }
    dsSetViewpoint (xyz,hpr);
}

/********************************************************************/
// called when a key pressed
static void command (int cmd)
{
    // don't handle user input yet.
    dsPrint ("received command %d (`%c')\n",cmd,cmd);
}

/*****************************************************************************/



static void display (int pause)
{
	double length;
	for (int i=0; i<sz; i++) {
		char name[40];
		char geometry[40];
		float center[3];
		float dims[3];
		float orientation[12];
		std::cout << "before calling stored data" << std::endl;
		links[i].getName(name);
		links[i].getGeometry(name);
		links[i].getCenter(center);
		links[i].getDimensions(dims);
	 	links[i].getOrientation(orientation);
		std::cout << "after calling stored data" << std::endl;
		if ( strcmp(geometry, "box")==0 ) {
			dsDrawBox(
					center,
					orientation,
					dims
					);
		} else if ( strcmp(geometry, "capsule")==0 || strcmp(geometry, "pill")==0) {
			dsDrawCapsule(
					center,
					orientation,
					dims[0],
					dims[1]
					);
		} else if ( strcmp(geometry, "cylinder")==0) {
			dsDrawCylinder(
					center,
					orientation,
					dims[0],
					dims[1]
					);
		}
	}
//	float pos[3] = {0.0f,0.0f,0.0f};
//	float R[12]  = {
//		1,0,0,0,
//		0,1,0,0,
//		0,0,1,0};
//	float sides[3]={ 5.0f, 2.0f, 10.0f};
//	dsDrawBox(pos, R, sides);
    // delay
}

/*****************************************************************************/


/********************************************************************/

int main (int argc, char **argv)
{
	// read the data from the file
	read_data("datFile.dat");

		dsFunctions fn;
    
    // setup pointers to drawstuff callback functions
    fn.version = DS_VERSION;
    fn.start = &start;
    fn.step = &display;
    fn.command = &command;
    fn.stop = 0;
#ifdef WIN32
    fn.path_to_textures = strcat(CWD,"drawstuff-windows/textures");
#else
    fn.path_to_textures = strcat(CWD,"/drawstuff/textures");
#endif
    fn.path_to_textures = "/Users/rbrothers/Desktop/School/Graduate/thesis/Simulation/sdfast/lib/drawstuff/textures";
    
    // do display
    dsSimulationLoop( argc, argv, /* command line arguments */
                     640, 480, /* window size */
                     &fn ); /* callback info */
    //
    
    return 0;
}

/********************************************************************/

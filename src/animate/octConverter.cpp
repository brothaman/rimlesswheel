#include <fstream>
#include "Globals.h"
//#include <octave/oct.h>
#include <oct.h>
#include <Cell.h>
#include "link.h"
/*
 * octave converter
 * - this file provides support for conversion from state data to animation data
 *
 *   From octave you will need to pass a matrix of state information in the format
 *   [torso data, left wheel data, right wheel data]
 *
 *   each bodies data will need to be in the format shown below
 *   [center_x, center_y, center_z, (9 double for orientation)]
 *   the length of the spokes and dimensions of the torso are set in the Globals.h file
 */

void store_link( LINK *link, float * v, char * name, int &j);
void store_link( std::fstream &outputFile,  float * v, char * name, int &j);
DEFUN_DLD (
		generate_data,
		args,
		nargout,
		"This function take a matrix of size N by 36 to produce a binary data file of LINKs"
		) 
{
	int nargin, N, i;
	float * ftemp;
	FloatNDArray temp;
	LINK * links;
	char * fname;
	std::fstream outputFile("datFile.dat", std::ios::out | std::ios::binary | std::ios::trunc);
	// ensure that the function is being used correctly with only one argument
	nargin = args.length();
	if (nargin !=1)
		print_usage();
	else {
		// check and make sure that the vector coming in is correct
		Cell data = args(0).cell_value();
		N = data.numel();
		links = new LINK[N*(FEET+1)/NBOD]; 

		//
		int j = 0, jbefore;
		for (i=0; i<N; i++) {
			// create a link and store the info in the link
			temp = data(i).array_value();
			if ( i%3 == 0){
				jbefore = j;
				store_link( links,  temp.fortran_vec(), "body",  j);
			} else {
				jbefore = j;
				store_link( links,  temp.fortran_vec(), "spoke", j);
			}
			
			// write all the recently update data in binary file
			for ( int k = jbefore; k<j; k++)
				outputFile.write( reinterpret_cast<const char *>(&links[k]), sizeof(LINK));

		}
	}

	return octave_value_list();
}

void store_link( std::fstream &outputFile, float * v, char * name, int &j) {
	// incoming v array has [(1x3 position) (1x3 rotation) (1x3 dimension)]
	int a = (strcmp(name, "body")==0) ? 0:1;
	LINK link;

	char str1[40];
	char str2[40];
	switch (a) {
		case 0 :
			strcpy(str1, "BODY");
			strcpy(str2, "box");
			// store information for body
			link = LINK(str1, str2, &v[0], &v[3], &v[6]);

			// write the link in to the file
			outputFile.write(reinterpret_cast<const char *>(&link), sizeof(LINK));
			j++;
			break;
		case 1:
			strcpy(str1, "SPOKE");
			strcpy(str2, "pill");
			// store information
			for (int i=0; i<FEET/2; i++) {
				v[3] += 2*PI/FEET*i;
				link = LINK(str1, str2,  &v[0], &v[3], &v[6]);

				// write the link in to the file
				outputFile.write(reinterpret_cast<const char *>(&link), sizeof(LINK));
				j++;
			}
		default:
			break;
	}
}

void store_link( LINK *link, float * v, char * name, int &j) {
	// incoming v array has [(1x3 position) (1x3 rotation) (1x3 dimension)]
	int a = (strcmp(name, "body")==0) ? 0:1;

	std::cout << "made it here " << j << std::endl;
	switch (a) {
		case 0 :
			// store information for body
			link[j] = LINK("BODY", "box", &v[0], &v[3], &v[6]);
			j++;
			break;
		case 1:
			// store information
			for (int i=0; i<FEET/2; i++) {
				v[3] += 2*PI/FEET*i;
				link[j] = LINK("SPOKE", "pill",  &v[0], &v[3], &v[6]);
				j++;
			}
		default:
			break;
	}
}

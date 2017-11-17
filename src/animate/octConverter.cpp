#include <fstream>
#include "Globals.h"
//#include <octave/oct.h>
#include <oct.h>
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

void store_link( LINK &link, float * v, char * name, int * j);
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
		Cell data = args.cell_value();
		N = data.numel();
		links = new LINK[N*(FEET+1)/NBOD]; 

		//
		int j = 0;
		for (i=0; i<N; i++) {
			// create a link and store the info in the link
			temp = data(i).float_array_value();
			if ( i%3 == 0)
				store_link( links[j], temp.fortran_vec(), "body",  &j);
			else
				store_link( links[j], temp.fortran_vec(), "spoke", &j);


			// write the link in to the file
			outputFile.write(reinterpret_cast<const char *>(&links[i]), sizeof(LINK));

		}
	}

	return octave_value_list();
}

void store_link( LINK &link, float * v, char * name, int *j) {
	// incoming v array has [(1x3 position) (1x3 rotation) (1x3 dimension)]
	int a = (strcmp(name, "body")==0) ? 0:1;

	switch (a) {
		case 0 :
			// store information for body
			link = LINK("BODY", "box", &v[0], &v[3], &v[6]);
			*j++;
			break;
		case 1:
			// store information
			for (int i=0; i<FEET/2; i++) {
				v[3] += 2*PI/FEET*i;
				link = LINK("SPOKE", "pill",  &v[0], &v[3], &v[6]);
				*j++;
			}
		default:
			break;
	}
}

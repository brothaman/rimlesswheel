#include <fstream>
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

DEFUN_DLD (
		generate_data,
		args,
		nargout,
		"This function take a matrix of size N by 36 to produce a binary data file of LINKs"
		) 
{
	int nargin, N;
	float * ftemp;
	FloatNDArray temp;
	LINK * links;
	char * fname;
	std::fstream ofile = ("datFile.dat", std::ios::out | std::ios::binary | std::ios::trunc);
	// ensure that the function is being used correctly with only one argument
	nargin = args.length();
	if (nargin !=1)
		print_usage();
	else {
		// check and make sure that the vector coming in is correct
		Cell data = args.cell_value();
		N = data.numel();
		links = new LINK[N]; 

		//
		for (i=0; i<N; i++) {
			// create a link and store the info in the link
			temp = data(i).float_array_value();
			store_link( links[i], temp.fortran_value());

			// write the link in to the file
			ofile.write(reinterpret_cast<const char *>(&links[i]), sizeof(LINK));

		}
	}

	return octave_value_list();
}


find_package (Octave REQUIRED)

file (GLOB MEX_SRC
	"mexSim.c"
	)

file (GLOB SIMULATION_LIB
	"*.h"
	)

file (GLOB SIMULATION_SRC 
	"constraints.c"
	"helper.c"
	"initialize.c"
	)

set (UTILITY_DIR "${CMAKE_SOURCE_DIR}/src/utility/")
# compile the mexSim file
octave_add_oct (
	mexsim
	${MEXSRC}
	${SIMULATION_SRC} ${SIMULATION_LIB}
	EXTENSION " -mex -o mexsim.mex"
	)

target_link_libraries ( mexsim
	${OCTAVE_LIBRARIES}
	# add the sdfast libraries from the utilities folder
	${SDLIB}
	)

include_directories (
	${OCTAVE_INCLUDE_DIRS}
	${UTILITY_DIR}
	# need to add utilities directories for .h files
	)

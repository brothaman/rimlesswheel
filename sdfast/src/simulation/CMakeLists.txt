find_package (Octave )

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set (CMAKE_C_FLAGS_DEBUG "-w")
set (UTILITY_DIR "${CMAKE_SOURCE_DIR}/src/utility/")
set (SD_DIR "${CMAKE_SOURCE_DIR}/src/sd/")

file (GLOB MEXSRC
	"mexSim.c"
	)

file (GLOB SIMULATIONSRC 
	"constraints.c"
	"helper.c"
	"initialize.c"
	)
file (GLOB SDSRC
	"${SD_DIR}/sd*.c"
	)
# compile the mexSim file
octave_add_oct (
	mexsim
	${SIMULATIONSRC}
	${SDSRC}
	${MEXSRC}
	EXTENSION " -o ${CMAKE_SOURCE_DIR}/bin/mexsim.mex"
	)

target_link_libraries ( mexsim
	${OCTAVE_LIBRARIES}
	# add the sdfast libraries from the utilities folder
	)

include_directories (
	${OCTAVE_INCLUDE_DIRS}
	${UTILITY_DIR}
	# need to add utilities directories for .h files
	)

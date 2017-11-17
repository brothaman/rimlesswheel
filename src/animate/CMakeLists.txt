# set the c++ stdlib to 14 for armadillo
set (CMAKE_CXX_STANDARD 14)

# collect all necessary packages glut and opengl for 
find_package (Octave REQUIRED)
find_package (GLUT REQUIRED)
find_package (OpenGL REQUIRED)
find_package (Armadillo REQUIRED)

set (DRAWSTUFF_INCLUDE_DIR                  
	"${CMAKE_SOURCE_DIR}/lib/drawstuff/"
	)

set (HELPERMATHDIR
	"${CMAKE_SOURCE_DIR}/lib/helpermath/" 
	)

set (LINKDIR
	"${CMAKE_SOURCE_DIR}/src/utility"
	)

file (GLOB link_src
	"${LINKDIR}/link.cpp"
	)

file (GLOB link_inc
	"${LINKDIR}/link.h"
	)

file (GLOB helper_src
	"${HELPERMATHDIR}/mmath.cpp"
	"${HELPERMATHDIR}/drawings.cpp"
	)

file (GLOB helper_inc
	"${HELPERMATHDIR}/mmath.h"
	"${HELPERMATHDIR}/drawings.hpp"
	)

file (GLOB drawstuff_inc
	"${DRAWSTUFF_INCLUDE_DIR}/drawstuff.h"
	)
octave_add_oct ( octsim
	"octConverter.cpp"
	${link_src}
	EXTENSION " -o ${CMAKE_SOURCE_DIR}/bin/generate_data.oct"
	)

add_executable( animate animate.cpp
	${link_src}
	${helper_src}
	)

include_directories( 
	${DRAWSTUFF_INCLUDE_DIR}
	${OCTAVE_INCLUDE_DIRS}
	${LINKDIR}
	${HELPERMATHDIR}
	${OPENGL_INCLUDE_DIRS}/OpenGL
	${GLUT_INCLUDE_DIRS}
	${ARMADILLO_INCLUDE_DIRS}
	)

target_include_directories ( animate PUBLIC ${DRAWSTUFF_INCLUDE_DIR})

target_link_libraries( animate
	${OPENGL_LIBRARIES}
	${GLUT_LIBRARIES}
	${OCTAVE_LIBRARIES}
	${DRAWSTUFF_INCLUDE_DIR}/libdrawstuff64.a
	${ARMADILLO_LIBRARIES}
	)


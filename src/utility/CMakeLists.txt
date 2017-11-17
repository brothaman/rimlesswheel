find_package ( Armadillo REQUIRED)

set (CMAKE_CXX_FLAGS "-std=c++14")
file ( GLOB LINK_SRC
	"link.cpp"
	)
add_library ( LINK_LIB OBJECT ${LINK_SRC})
include_directories (
	${ARMADILLO_INCLUDE_DIRS}
	)

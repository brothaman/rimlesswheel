# adding the sd dynamics library

set (CMAKE_C_FLAGS_DEBUG "-w")
file (GLOB SD_SRC
	"sd*.c"
	)
add_library( SDLIB OBJECT ${SD_SRC})

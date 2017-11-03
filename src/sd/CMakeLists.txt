# adding the sd dynamics library

file (GLOB SD_SRC
	"sd*.c"
	)
add_library( SDLIB OBJECT ${SD_SRC})

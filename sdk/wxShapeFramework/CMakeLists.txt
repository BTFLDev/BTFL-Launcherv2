project(wxSF)

set(WXSF_INCLUDES
	"include"
	"src")

file(GLOB_RECURSE WXSF_SRCS src/*.cpp src/**/*.cpp)

find_package(wxWidgets COMPONENTS all REQUIRED)

if(wxWidgets_FOUND)
	include(${wxWidgets_USE_FILE})

	list(APPEND WXSF_INCLUDES ${wxWidgets_INCLUDE_DIRS})
	set(WXSF_LIBRARIES ${wxWidgets_LIBRARIES})

	add_library(wxSF ${WXSF_SRCS})

	target_include_directories(wxSF PUBLIC ${WXSF_INCLUDES})
	target_link_libraries(wxSF PRIVATE ${WXSF_LIBRARIES})
endif()

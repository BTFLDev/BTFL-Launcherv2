cmake_minimum_required(VERSION 3.29.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

list(APPEND CMAKE_PREFIX_PATH $ENV{WXWIN})

project(BTFL-Launcher)

add_subdirectory(sdk/wxShapeFramework)

set(BTFL_LAUNCHER_INCLUDES
	"src"
	"sdk/wxShapeFramework/include"
	"sdk/digestpp"
    "sdk/gaze/include")
file(GLOB_RECURSE BTFL_LAUNCHER_SRCS src/*.cpp src/**/*.cpp)
file(GLOB_RECURSE BTFL_LAUNCHER_RESOURCES assets/* assets/**/*)

list(APPEND BTFL_LAUNCHER_SRCS ${BTFL_LAUNCHER_RESOURCES})

set(BTFL_LAUNCHER_LIBRARIES
	wxSF)

find_package(wxWidgets COMPONENTS all REQUIRED)

if(wxWidgets_FOUND)
	include(${wxWidgets_USE_FILE})

	list(APPEND BTFL_LAUCHER_INCLUDES ${wxWidgets_INCLUDE_DIRS})
	list(APPEND BTFL_LAUNCHER_LIBRARIES ${wxWidgets_LIBRARIES})

	add_executable(BTFL-Launcher MACOSX_BUNDLE ${BTFL_LAUNCHER_SRCS})

	set_property(TARGET BTFL-Launcher PROPERTY CXX_STANDARD 20)

	set_target_properties(BTFL-Launcher PROPERTIES
		RESOURCE "${BTFL_LAUNCHER_RESOURCES}"
		MACOSX_FRAMEWORK_IDENTIFIER org.btfl.BTFL-Launcher
		MACOSX_BUNDLE TRUE)

    set_source_files_properties("assets/font/Lora-Regular.ttf" PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources/Fonts")

	target_include_directories(BTFL-Launcher PUBLIC ${BTFL_LAUNCHER_INCLUDES})
	target_link_libraries(BTFL-Launcher PUBLIC ${BTFL_LAUNCHER_LIBRARIES})
endif()

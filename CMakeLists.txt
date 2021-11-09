cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

message(STATUS "------------------------------------------------------------------------------------")

set(EXECUTABLE_NAME InteractiveSandbox)
project("${EXECUTABLE_NAME}")

# --------------------------------------------------------------
# global variables
# --------------------------------------------------------------
if (CMAKE_EXECUTABLE_SUFFIX STREQUAL ".js")
	set(HTML_BUILD True CACHE BOOL "whether this is an html build" FORCE) #TODO rename flag to emscripten_html_build 
	add_compile_definitions(HTML_BUILD)
else()
	set(HTML_BUILD False CACHE BOOL "whether this is an html build" FORCE) 
endif()
message(STATUS "HTML_BUILD Value: ${HTML_BUILD}")

# --------------------------------------------------------------
# Set up libraries
# --------------------------------------------------------------
# set up the engine library for all applications to link against
add_subdirectory(engine)

# --------------------------------------------------------------
# Set up applications
# --------------------------------------------------------------
add_subdirectory("applications/BuildSystemTest")
add_subdirectory("applications/HelloTriangle")

message(STATUS " ------------------------------------------------------------------------------------")
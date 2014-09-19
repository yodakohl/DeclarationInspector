cmake_minimum_required (VERSION 2.6)
project (AnalyserTest)

#Build Path
	include_directories(${CMAKE_SOURCE_DIR})
	SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
	SET(CMAKE_BUILD_TYPE "Release")
	SET(CMAKE_CXX_FLAGS " -std=c++0x") 
# Directorys-----------------------------------------------------------

#FILES
	SET(SOURCE
		main.cpp
	)

	#BOOST----------------------------
	FIND_PACKAGE(Boost REQUIRED unit_test_framework)

	LINK_DIRECTORIES ( ${Boost_LIBRARY_DIRS} )
	INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

	INCLUDE_DIRECTORIES(../Analyser)
	LINK_DIRECTORIES(../Analyser)

add_executable(AnalyserTest ${SOURCE})
TARGET_LINK_LIBRARIES(AnalyserTest ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES(AnalyserTest Analyser )







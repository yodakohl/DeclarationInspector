cmake_minimum_required (VERSION 2.6)
project (Analyser)

#Build Path	
	SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
	SET(CMAKE_BUILD_TYPE "Release")
	SET(CMAKE_CXX_FLAGS "-Wall -fpic -O3 -std=c++0x")
	
# Directorys-----------------------------------------------------------
	include_directories(${CMAKE_SOURCE_DIR})

#FILES
	SET(SOURCE
		Scanner.h
		Scanner.cpp
		Parser.h
		Parser.cpp
		Analyser.cpp
		SymbolTable.cpp
		Declaration.cpp
		DataType.cpp
	)

	SET(HEADERS
		SymbolTable.h
		Analyser.h
		Declaration.h
		DataType.h
	)


ADD_LIBRARY(Analyser STATIC ${SOURCE} ${HEADERS})


#install (TARGETS Analyser DESTINATION ${CMAKE_BINARY_DIR}/Release/lib)
#install (FILES ${HEADERS} DESTINATION ${CMAKE_BINARY_DIR}/Release/include/Analyser)







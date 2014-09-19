cmake_minimum_required (VERSION 2.6)
project (DeclarationInspector)

#Build Path	
	SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
	SET(CMAKE_BUILD_TYPE "Release")
	SET(CMAKE_CXX_FLAGS " -fpic -std=c++0x -O3") 

	SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
	SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
	SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
	SET(CMAKE_INSTALL_RPATH "./")
	LINK_DIRECTORIES(${CMAKE_BINARY_DIR})
	FIND_PACKAGE(Qt4 REQUIRED)
# Directorys-----------------------------------------------------------
	include_directories(${CMAKE_SOURCE_DIR})

#FILES
	SET(HEADERS
		visualizer.h
		memoryarea.h
		editor.h
		highligther.h
		editsidebar.h
		commonmemory.h
		classmemory.h
		tutorial.h
		boundingbox.h
	)

	SET(SOURCE
		main.cpp
		visualizer.cpp
		memoryarea.cpp
		editor.cpp
		highligther.cpp
		editsidebar.cpp
		commonmemory.cpp
		classmemory.cpp
		tutorial.cpp
		boundingbox.cpp
	)


QT4_WRAP_CPP(DeclarationInspector_HEADERS_MOC ${HEADERS})
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

ADD_EXECUTABLE(DeclarationInspector ${SOURCE} ${DeclarationInspector_HEADERS_MOC})
TARGET_LINK_LIBRARIES(DeclarationInspector ${QT_LIBRARIES})
TARGET_LINK_LIBRARIES(DeclarationInspector Analyser)



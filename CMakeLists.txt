cmake_minimum_required (VERSION 2.6)

ADD_SUBDIRECTORY(Visualizer)
ADD_SUBDIRECTORY(Analyser)
ADD_SUBDIRECTORY(Tests)

project (Tutorial)
INSTALL( DIRECTORY Tutorial DESTINATION ${CMAKE_BINARY_DIR}/Release )
INSTALL( FILES ${CMAKE_BINARY_DIR}/DeclarationInspector DESTINATION ${CMAKE_BINARY_DIR}/Release )







cmake_minimum_required( VERSION 2.6 )
set ( CMAKE_BUILD_TYPE Release )
add_definitions ( -Wall -std=c++0x )
include_directories ( ../../include )
set ( LIBRARY_OUTPUT_PATH ../../lib )
set ( proj_geom_SRCS
  conic.cpp
)

add_library ( proj_geom ${proj_geom_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS} )
target_link_libraries ( proj_geom  )

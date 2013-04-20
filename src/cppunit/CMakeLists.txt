cmake_minimum_required( VERSION 2.6 )
set ( CMAKE_BUILD_TYPE Debug )
add_definitions ( --std=c++0x -Wall -g )
include_directories ( ../../include )
set ( cppunit_HDRS
  vector3_t.hpp
  vector2_t.hpp
  matrix3_t.hpp
  matrix2_t.cpp
  point3_t.hpp
  point2_t.hpp
  line3_t.hpp
  cline_t.hpp
)

set ( cppunit_SRCS
  Main.cpp
  vector3_t.cpp
  vector2_t.cpp
  matrix3_t.cpp
  matrix2_t.cpp
  point3_t.cpp
  point2_t.cpp
  line3_t.cpp
  cline_t.cpp
)

add_executable ( cppunit2 ${cppunit_SRCS} )
link_directories ( ../lib )
target_link_libraries ( cppunit2 cppunit dl )

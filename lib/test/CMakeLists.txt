# Distributed under the MIT License (See accompanying file /LICENSE )

# CMake build : library tests

#configure variables
set (TEST_APP_NAME "${LIB_NAME}Test")

#configure directories
set (TEST_MODULE_PATH "${LIBRARY_MODULE_PATH}/test")

#configure test directories
set (TEST_SRC_PATH  "${TEST_MODULE_PATH}/src" )

#set includes
message(STATUS "Test: ${LIBRARY_INCLUDE_PATH} ")
include_directories (${LIBRARY_INCLUDE_PATH} ${TEST_THIRD_PARTY_INCLUDE_PATH} ${xtensor_INCLUDE_DIRS}  ${Boost_INCLUDE_DIR})

#set test sources
file (GLOB TEST_SOURCE_FILES "${TEST_SRC_PATH}/*.cpp")

#set concepts TS
# add_definitions ( -std=c++17 )

#set target executable
add_executable (${TEST_APP_NAME} ${TEST_SOURCE_FILES})

#add the library
target_link_libraries (${TEST_APP_NAME} ${LIB_NAME} Threads::Threads ${LIBS})

# Turn on CMake testing capabilities
enable_testing()

#parse catch tests
## ParseAndAddCatchTests (${TEST_APP_NAME})
add_test (NAME ${TEST_APP_NAME} COMMAND ${TEST_APP_NAME} )

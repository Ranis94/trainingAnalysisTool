#Not important
cmake_minimum_required(VERSION 3.0.0)
project(trainingAnalysisTool VERSION 1.0.0)
include(CTest)
enable_testing()

# Add all necessary sub-directories (sub-directory including executable should be added last)
add_subdirectory(trainingAnalysisTool_library)
add_subdirectory(trainingAnalysisTool_exe)

# Constructive message
message("${PROJECT_SOURCE_DIR}   ---  fuck c++")

# Not important 
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
# Create lib library
add_library(
    trainingAnalysisTool_lib
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/trainingInstance.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/trainingInstance.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/running.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/running.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/trainingArray.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/trainingArray.cpp
)

# Needed for libraries to be linked
target_include_directories(trainingAnalysisTool_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lib")
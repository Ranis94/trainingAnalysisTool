# Create lib library
add_library(
    trainingAnalysisTool_lib
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/cadenceExercise.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cadenceExercise.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/cardioTraining.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cardioTraining.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/cycling.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cycling.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/revolutionExercise.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/revolutionExercise.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/running.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/running.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/strokeExercise.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/strokeExercise.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/swimming.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/swimming.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/training.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/training.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/trainingArray.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/trainingArray.cpp
)

# Needed for libraries to be linked
target_include_directories(trainingAnalysisTool_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lib")
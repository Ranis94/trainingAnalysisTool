# Needed to be able to run project "exProj"
add_executable(trainingAnalysisTool main.cpp)

# Add libraries to project
target_link_libraries(trainingAnalysisTool PRIVATE trainingAnalysisTool_lib)
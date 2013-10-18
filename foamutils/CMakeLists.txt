
add_library(foamutils SHARED foamutils.cpp)
target_link_libraries(foamutils ${Boost_PYTHON_LIBRARY} ${DGTAL_LIBRARIES})

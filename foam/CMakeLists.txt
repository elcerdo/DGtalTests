
add_executable(extract extract.cpp)
target_link_libraries(extract ${DGTAL_LIBRARIES} ${Boost_PROGRAM_OPTIONS_LIBRARY})


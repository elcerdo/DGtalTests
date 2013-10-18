
add_executable(helloworld helloworld.cpp)
target_link_libraries(helloworld ${DGTAL_LIBRARIES})
add_executable(programoptions programoptions.cpp)
target_link_libraries(programoptions ${Boost_PROGRAM_OPTIONS_LIBRARY})
add_executable(board2d board2d.cpp)
target_link_libraries(board2d ${DGTAL_LIBRARIES})

add_executable(thresholder thresholder.cpp)
target_link_libraries(thresholder ${DGTAL_LIBRARIES} ${Boost_PROGRAM_OPTIONS_LIBRARY})



add_executable(helloworld helloworld.cpp)
target_link_libraries(helloworld ${DGTAL_LIBRARIES})
add_executable(dgtalcountedpointer dgtalcountedpointer.cpp)
target_link_libraries(dgtalcountedpointer ${DGTAL_LIBRARIES})
add_executable(board2d board2d.cpp)
target_link_libraries(board2d ${DGTAL_LIBRARIES})

add_executable(itkregion itkregion.cpp)
target_link_libraries(itkregion ${ITK_LIBRARIES})
add_executable(itksmartpointer itksmartpointer.cpp)
target_link_libraries(itksmartpointer ${ITK_LIBRARIES})

add_executable(programoptions programoptions.cpp)
target_link_libraries(programoptions ${Boost_PROGRAM_OPTIONS_LIBRARY})

add_executable(thresholder thresholder.cpp)
target_link_libraries(thresholder ${DGTAL_LIBRARIES} ${Boost_PROGRAM_OPTIONS_LIBRARY})


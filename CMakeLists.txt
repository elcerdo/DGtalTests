project(DGtalTests)

cmake_minimum_required(VERSION 2.6)

find_package(DGtal REQUIRED)
include_directories(${DGTAL_INCLUDE_DIRS})
link_directories(${DGTAL_LIBRARY_DIRS})

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(helloworld helloworld.cpp)
target_link_libraries(helloworld ${DGTAL_LIBRARIES})
add_executable(programoptions programoptions.cpp)
target_link_libraries(programoptions ${Boost_PROGRAM_OPTIONS_LIBRARY})
add_executable(board2d board2d.cpp)
target_link_libraries(board2d ${DGTAL_LIBRARIES})


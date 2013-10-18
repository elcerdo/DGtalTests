project(DGtalTests)

cmake_minimum_required(VERSION 2.6)

find_package(DGtal REQUIRED)
include_directories(${DGTAL_INCLUDE_DIRS})
link_directories(${DGTAL_LIBRARY_DIRS})

find_package(Boost REQUIRED COMPONENTS program_options)

subdirs(tests)

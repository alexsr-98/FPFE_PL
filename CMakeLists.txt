
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(yourG4application)

#No UI and visualization
#find_package(Geant4 REQUIRED)

#Visualization drivers
find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(main main.cc ${sources} ${headers})
target_link_libraries(main ${Geant4_LIBRARIES})


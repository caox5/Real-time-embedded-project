cmake_minimum_required(VERSION "3.14")

project(FallDetectionRpi)


set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)



add_executable(${PROJECT_NAME} 
                ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
include_directories(${OpenCV_INCLUDE_DIRS})

cmake_minimum_required(VERSION 3.4.1)
project("examples")

set(TARGET_NAME libsynexens3_demo)


message("configure ${TARGET_NAME}")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/x64)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third-party/opencv-4.4.0/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third-party/opencv-4.4.0/lib/x64/shared)


if(WIN32)
  set(OpenCV_LIBS 
    opencv_core440
    opencv_imgproc440
    opencv_imgcodecs440
    opencv_highgui440
    opencv_videoio440
    opencv_calib3d440)
set(LIBSYNEXENS3 ${LIBSYNEXENS3})

elseif(UNIX)
set(OpenCV_LIBS 
    opencv_core
    opencv_imgproc
    opencv_imgcodecs
    opencv_highgui
    opencv_videoio
    opencv_calib3d)

set(LIBSYNEXENS3 synexens3)

endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -fopenmp")

add_executable(depth depth.cpp)
target_link_libraries(depth  PRIVATE ${LIBSYNEXENS3} ${OpenCV_LIBS})
set_property(TARGET depth PROPERTY FOLDER Samples)


add_executable(pointcloud pointcloud.cpp)
target_link_libraries(pointcloud  PRIVATE ${LIBSYNEXENS3} ${OpenCV_LIBS})
set_property(TARGET pointcloud PROPERTY FOLDER Samples)


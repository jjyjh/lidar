cmake_minimum_required(VERSION 3.4.1)

set(TARGET_NAME libsynexens3_demo)

message("configure ${TARGET_NAME}")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(OpenCVShared)
if(OpenCV_FOUND)
  include_directories(${OpenCV_INCLUDE_DIR})
  link_directories(${OpenCV_LIBS_DIR})
endif(OpenCV_FOUND)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -fopenmp")


if(WIN32)
  set(APP_PREFIX  .exe)
  set(SY3_LIB  libsynexens3)
elseif(UNIX)
  set(APP_PREFIX  )
  set(SY3_LIB  synexens3)
  #link_directories(/home/wk/work/firmware/rockchip/rv1126/buildroot/output/rockchip_rv1126_rv1109_uvcc/build/eudev-3.2.7/src/libudev/.libs)
endif()

find_package(Pthread)
if(PTHREAD_FOUND)
  include_directories(${PTHREAD_FOUND_INCLUDE_DIR})
  link_directories(${PTHREAD_FOUND_LIBS_DIR})
endif(PTHREAD_FOUND)

add_executable(depth depth.cpp)
target_link_libraries(depth  PRIVATE ${SY3_LIB} ${OpenCV_LIBS}  )
set_property(TARGET depth PROPERTY FOLDER Samples)
install(FILES ${OUTPUT_BIN_DIR}/depth${APP_PREFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})

add_executable(rgb rgb.cpp)
target_link_libraries(rgb  PRIVATE ${SY3_LIB} ${OpenCV_LIBS})
set_property(TARGET rgb PROPERTY FOLDER Samples)
install(FILES ${OUTPUT_BIN_DIR}/rgb${APP_PREFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})


add_executable(align align.cpp)
target_link_libraries(align PRIVATE ${SY3_LIB} ${OpenCV_LIBS})
set_property(TARGET align PROPERTY FOLDER Samples)
install(FILES ${OUTPUT_BIN_DIR}/align${APP_PREFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})


add_executable(pointcloud pointcloud.cpp)
target_link_libraries(pointcloud PRIVATE ${SY3_LIB} ${OpenCV_LIBS})
set_property(TARGET pointcloud PROPERTY FOLDER Samples)
install(FILES ${OUTPUT_BIN_DIR}/pointcloud${APP_PREFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})


add_executable(raw raw.cpp)
target_link_libraries(raw PRIVATE ${SY3_LIB} ${OpenCV_LIBS})
set_property(TARGET raw PROPERTY FOLDER Samples)


# add_executable(burn-intrinsics burn-intrinsics.cpp)
# target_link_libraries(burn-intrinsics PRIVATE ${SY3_LIB})
# set_property(TARGET burn-intrinsics PROPERTY FOLDER Samples)


if(UNIX)
    set(INSTALL_LIB_SUFFIX  so)
    set(LIB_PREFIX  lib)       
    install(FILES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libsynexens3.${INSTALL_LIB_SUFFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION ${SDK_INSTALL_DIR})
    install(DIRECTORY ${OpenCV_DIR} DESTINATION ${SDK_INSTALL_DIR}/third-party)

elseif(WIN32)
    set(INSTALL_LIB_SUFFIX  dll)
    install(FILES ${OUTPUT_BIN_DIR}/libsynexens3.${INSTALL_LIB_SUFFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})
    install(FILES ${OpenCV_LIBS_DIR}/${LIB_PREFIX}opencv_core440.${INSTALL_LIB_SUFFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})
    install(FILES ${OpenCV_LIBS_DIR}/${LIB_PREFIX}opencv_imgproc440.${INSTALL_LIB_SUFFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})
    install(FILES ${OpenCV_LIBS_DIR}/${LIB_PREFIX}opencv_imgcodecs440.${INSTALL_LIB_SUFFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})
    install(FILES ${OpenCV_LIBS_DIR}/${LIB_PREFIX}opencv_highgui440.${INSTALL_LIB_SUFFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})
    install(FILES ${OpenCV_LIBS_DIR}/${LIB_PREFIX}opencv_videoio440.${INSTALL_LIB_SUFFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})
    install(FILES ${OpenCV_LIBS_DIR}/${LIB_PREFIX}opencv_calib3d440.${INSTALL_LIB_SUFFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})
    install(FILES ${OpenCV_LIBS_DIR}/${LIB_PREFIX}opencv_features2d440.${INSTALL_LIB_SUFFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})
    install(FILES ${OpenCV_LIBS_DIR}/${LIB_PREFIX}opencv_flann440.${INSTALL_LIB_SUFFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})


    install(FILES ${OUTPUT_BIN_DIR}/csreconstruction.${INSTALL_LIB_SUFFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})
    install(FILES ${OUTPUT_BIN_DIR}/pthreadVC2.${INSTALL_LIB_SUFFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})
    install(FILES ${OUTPUT_BIN_DIR}/SonixCamera.${INSTALL_LIB_SUFFIX} DESTINATION ${SDK_INSTALL_DIR}/bin/${TARGET_PLATFORM})


    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION ${SDK_INSTALL_DIR})
    install(DIRECTORY ${OpenCV_DIR} DESTINATION ${SDK_INSTALL_DIR}/third-party)


endif()

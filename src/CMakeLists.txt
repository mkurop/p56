add_library(p56 SHARED asl_P56.cpp  asl_P56_emxAPI.cpp  asl_P56_emxutil.cpp  asl_P56_initialize.cpp  asl_P56_terminate.cpp  filter.cpp  P56.cpp  rtGetInf.cpp  rtGetNaN.cpp  rt_nonfinite.cpp)

target_include_directories(p56 PUBLIC "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include;${CMAKE_SOURCE_DIR}/api>" "$<INSTALL_INTERFACE:>")

install(FILES ${CMAKE_SOURCE_DIR}/api/P56.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS p56 EXPORT p56_export DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(EXPORT p56_export FILE p56-config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR})



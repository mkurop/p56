add_library(p56 SHARED asl_P56.cpp  asl_P56_emxAPI.cpp  asl_P56_emxutil.cpp  asl_P56_initialize.cpp  asl_P56_terminate.cpp  filter.cpp  P56.cpp  rtGetInf.cpp  rtGetNaN.cpp  rt_nonfinite.cpp)

target_include_directories(p56 PUBLIC "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include;${CMAKE_SOURCE_DIR}/api>" "$<INSTALL_INTERFACE:>")



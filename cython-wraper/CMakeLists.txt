add_cython_target(p56_measurement CXX)

add_library(p56_measurement MODULE ${p56_measurement})

python_extension_module(p56_measurement)

target_link_libraries(p56_measurement p56 ${PYTHON_LIBRARIES})

target_include_directories(p56_measurement PUBLIC ${CMAKE_SOURCE_DIR}/api ${PYTHON_INCLUDE_DIRS} ${NumPy_INCLUDE_DIRS})

install(TARGETS p56_measurement LIBRARY DESTINATION p56)

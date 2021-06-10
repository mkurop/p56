add_executable(p56-example p56-example.cpp)

target_include_directories(p56-example PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/api ${CMAKE_SOURCE_DIR}/AudioFile)

target_link_libraries(p56-example p56)

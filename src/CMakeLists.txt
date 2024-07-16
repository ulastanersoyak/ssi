add_executable(ssi main.cpp)

target_compile_definitions(ssi PRIVATE TEST=1)
target_include_directories(ssi PRIVATE ${CMAKE_SOURCE_DIR}/includes ${CMAKE_SOURCE_DIR}/test)

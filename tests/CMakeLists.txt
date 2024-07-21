include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB src_files "${PROJECT_SOURCE_DIR}/src/session.c")

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/test_*.c")
foreach(file ${files})
  get_filename_component(name ${file} NAME_WE)

  add_executable(${name} ${file} ${src_files})
  add_test(NAME ${name} COMMAND ${name})
endforeach()
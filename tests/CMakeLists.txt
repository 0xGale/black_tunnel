include_directories(${PROJECT_SOURCE_DIR}/include)


aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
list(REMOVE_ITEM DIR_SRCS "${PROJECT_SOURCE_DIR}/src/tunnel_server.c")
list(REMOVE_ITEM DIR_SRCS "${PROJECT_SOURCE_DIR}/src/tunnel_client.c")


file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/test_*.c")
foreach(file ${files})
  get_filename_component(name ${file} NAME_WE)

  add_executable(${name} ${file} ${DIR_SRCS})
  add_test(NAME ${name} COMMAND ${name})
endforeach()
cmake_minimum_required(VERSION 3.22)
project(black_tunnel C)

set(CMAKE_C_STANDARD 11)


#add_executable(server server.c)
#add_executable(client client.c)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
list(REMOVE_ITEM DIR_SRCS "${PROJECT_SOURCE_DIR}/src/tunnel_server.c")
list(REMOVE_ITEM DIR_SRCS "${PROJECT_SOURCE_DIR}/src/tunnel_client.c")


add_executable(tunnel_server ${PROJECT_SOURCE_DIR}/src/tunnel_server.c ${DIR_SRCS})

add_executable(tunnel_client ${PROJECT_SOURCE_DIR}/src/tunnel_client.c ${DIR_SRCS})

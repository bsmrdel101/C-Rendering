cmake_minimum_required(VERSION 3.10)
project(C_RENDERING C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_PREFIX_PATH "C:/vcpkg/installed/x64-windows/share" CACHE STRING "")

file(GLOB_RECURSE SOURCES src/*.c)
add_executable(app ${SOURCES})

include_directories(C:\\vcpkg\\installed\\x64-windows\\include)
link_directories(C:\\vcpkg\\installed\\x64-windows\\lib)

# Packages
find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)
find_package(cJSON CONFIG REQUIRED)

target_link_libraries(app PRIVATE
  SDL3::SDL3
  $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>
  cjson
)

set_target_properties(app PROPERTIES WIN32_EXECUTABLE TRUE)

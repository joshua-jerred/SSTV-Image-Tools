cmake_minimum_required(VERSION 3.14)
project(SSTV-Image-Tools VERSION 0.4)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug) # Change to Release for production
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
	-fno-omit-frame-pointer \
	-pedantic \
	-Wall \
	-Wextra \
	-Weffc++ \
	-Wunused-variable \
	-Wno-type-limits \
	-Wno-float-equal")
# no type limits and no float equal are for the ImageMagick library

include_directories(include)
add_library(sstv-image-tools
	src/sstv-image-tools.cpp
)
target_include_directories(sstv-image-tools PUBLIC include)
add_definitions(-DMAGICKCORE_QUANTUM_DEPTH=8)
add_definitions(-DMAGICKCORE_HDRI_ENABLE=1) # Required or there are linking errors with Magick::Color::Color
find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})
target_link_libraries(sstv-image-tools ${ImageMagick_LIBRARIES})

# Example
add_executable(example-images
  example/example.cpp
)
target_link_libraries(example-images sstv-image-tools)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/example/test1.png ${CMAKE_CURRENT_BINARY_DIR}/test1.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/example/test2.png ${CMAKE_CURRENT_BINARY_DIR}/test2.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/example/test3.jpg ${CMAKE_CURRENT_BINARY_DIR}/test3.jpg COPYONLY)
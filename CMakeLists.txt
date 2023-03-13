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
	-Wdisabled-optimization \
	-Wno-unused-variable")

include_directories(src)

add_executable(example
  example/example.cpp
  src/sstv-image-tools.cpp
)
add_definitions(-DMAGICKCORE_QUANTUM_DEPTH=8)
add_definitions(-DMAGICKCORE_HDRI_ENABLE=1) # Required or there are linking errors with Magick::Color::Color
find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})
target_link_libraries(example ${ImageMagick_LIBRARIES})
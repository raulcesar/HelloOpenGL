cmake_minimum_required(VERSION 3.1)
project(HelloOpenGL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)


find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
add_subdirectory(glfw)
add_executable(HelloOpenGL ${SOURCE_FILES})

target_link_libraries (HelloOpenGL
	${GLEW_LIBRARIES}
	glfw ${GLFW_LIBRARIES}

)
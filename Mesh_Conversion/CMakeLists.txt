# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


cmake_minimum_required(VERSION 3.1...3.15)
project( Mesh_Conversion )


find_package(CGAL QUIET)
find_package(CGAL REQUIRED COMPONENTS Core)
find_package(Eigen3 3.2.0) #(requires 3.2.0 or greater)
include(CGAL_Eigen_support)

if ( CGAL_FOUND )
	if (TARGET CGAL::Eigen_support)
		add_executable(conversion_exe main.cpp)
		target_link_libraries(conversion_exe CGAL::CGAL CGAL::CGAL_Core CGAL::Eigen_support)
	endif()
else()

    message(STATUS "This program requires the CGAL library, and will not be compiled.")

endif()


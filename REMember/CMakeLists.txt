# CMakeList.txt : CMake project for REMember, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (REMember "src/main.cpp" "inc/member.hpp")
set_property(TARGET REMember PROPERTY CXX_STANDARD 17)

# TODO: Add tests and install targets if needed.

# Specify the minimum version
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)
##set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the project name
project(ex_maps_advanced_AKD)

# Add sources
set(
  PROG_SRCS
  ex_maps_advanced.cpp
  generate_randomstring.cpp
  random_order_generator.cpp
)

#add_executable(ex_strings ex_strings.cpp)
# Specify what is needed to create the main target.
add_executable(${PROJECT_NAME} ${PROG_SRCS})

# Specify how to install the binary.
install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)


#Spefify compile options
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic -fstack-protector-all -std=c++17 -D_FORTIFY_SOURCE=2 -g )

#Specify link options
target_link_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic -fstack-protector-all -std=c++17 -D_FORTIFY_SOURCE=2 -g )

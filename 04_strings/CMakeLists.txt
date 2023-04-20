# Specify the minimum version
cmake_minimum_required(VERSION 3.0.0)

# Specify the project name
project(ex_strings)

# Add sources
set(
  PROG_SRCS
  ex_strings.cpp
)

#add_executable(ex_strings ex_strings.cpp)
# Specify what is needed to create the main target.
add_executable(${PROJECT_NAME} ${PROG_SRCS})

# Specify how to install the binary.
install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

#Spefify compile options
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic -fstack-protector-all -D_FORTIFY_SOURCE=2 -g -O2)

#Specify link options
target_link_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic -fstack-protector-all -D_FORTIFY_SOURCE=2 -g -O2)

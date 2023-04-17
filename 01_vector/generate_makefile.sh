#!/bin/bash

TARGET=01_ex_string_vector
CXX=g++
CXXFLAGS="-Wall -Wextra -pedantic -std=c++11"

OBJECTS=""
for file in *.cpp; do
    OBJECTS+="$(basename "$file" .cpp).o "
done

cat << EOF > Makefile
TARGET=${TARGET}
CXX=${CXX}
CXXFLAGS=${CXXFLAGS}
OBJECTS=${OBJECTS}

\$(TARGET): \$(OBJECTS)
	\$(CXX) \$(CXXFLAGS) \$(OBJECTS) -o \$(TARGET)

%.o: %.cpp
	\$(CXX) \$(CXXFLAGS) -c \$< -o \$@

.PHONY: clean
clean:
	rm -f \$(TARGET) \$(OBJECTS)
EOF

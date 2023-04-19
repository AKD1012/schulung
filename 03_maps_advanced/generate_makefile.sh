#!/bin/bash

TARGET=03_ex_maps_advanced
CXX=g++
CXXFLAGS="-Wall -Wextra -pedantic -fstack-protector-all -D_FORTIFY_SOURCE=2 -g -O2 -std=c++11"

OBJECTS=""
for file in *.cpp; do
    OBJECTS+="$(basename "$file" .cpp).o "
done

cat << EOF > Makefile
TARGET=${TARGET}
CXX=${CXX}
CXXFLAGS=${CXXFLAGS}
OBJECTS=${OBJECTS}

all: \$(TARGET)

\$(TARGET): \$(OBJECTS)
	\$(CXX) \$(CXXFLAGS) \$(OBJECTS) -o \$(TARGET)

%.o: %.cpp
	\$(CXX) \$(CXXFLAGS) -c \$< -o \$@

.PHONY: clean
clean:
	rm -f \$(TARGET) \$(OBJECTS)
EOF

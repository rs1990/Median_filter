CXX = g++
CXXFLAGS = -std=c++11 $(DEBUG)

all:  lidar.h main.cpp
	@$(CXX) $(CXXFLAGS) lidar.h main.cpp -o result
	@ echo Compiled.

.PHONY: clean

clean:
	@ -rm -f result
	@ echo clean finished
	



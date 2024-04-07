CROSS_COMPLIE=aarch64-linux-gnu-
CXX=$(CROSS_COMPLIE)g++
LD=$(CROSS_COMPLIE)ld
CXXFLAGS=-std=c++11
OBJ=*.o
SRC=*.cpp
EXE=tx2_exe

all:$(EXE)

$(EXE):$(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

$(OBJ):$(SRC)
	$(CXX) $(CXXFLAGS) -c $?

clean:
	rm -f $(EXE)
	rm -f $(OBJ)


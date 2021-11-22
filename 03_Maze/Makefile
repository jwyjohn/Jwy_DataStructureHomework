CXXFLAGS   = -std=c++11
CXX        = g++
RM         = rm -f
OBJ        = a.out
SOURCE     = main.o
DEPEND     = main.cpp

build : $(SOURCE)
	$(CXX) $(SOURCE) -o $(OBJ)

%.o:%cpp $(DEPEND)
	$(CXX) -o $@ $<

.PHONY : clean
clean:
	$(RM) *.bak $(SOURCE) $(OBJ)
	touch *.*

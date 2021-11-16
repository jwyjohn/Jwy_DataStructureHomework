CFLAGS   = -c -Wall -Werror -std=c++11 
CXX  = g++
RM       = rm -f
OBJ      = keyword
SOURCE   = main.o
DEPEND   = main.cpp main_header.h

build : $(SOURCE)
	$(CXX) $(SOURCE) -o $(OBJ) 
	$(RM) $(SOURCE)

%.o:%cpp $(DEPEND)
	$(CXX) $(CFLAGS) -o $@ $< 

.PHONY : clean
clean:
	$(RM) *.bak $(OBJ)
	touch *.*
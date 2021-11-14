CFLAGS   = -c -Wall -Werror
COMPILE  = g++
RM       = rm -f
OBJ      = a.out
SOURCE   = main.o
DEPEND   = main.cpp sort.h

build : $(SOURCE)
	$(COMPILE) $(SOURCE) -o $(OBJ) 

%.o:%cpp $(DEPEND)
	$(COMPILE) $(CFLAGS) -o $@ $< 

.PHONY : clean
clean:
	$(RM) *.bak $(SOURCE) $(OBJ)
	touch *.*
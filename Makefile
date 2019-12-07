CC=g++
CCFLAGS= -Wall -std=c++11 -g
LIBFLAGS=
SRC= $(wildcard *.cc)
OBJ= $(SRC:.cc=.o)
EXEC= projet


all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LIBFLAGS) $^ -o $@

%.o: %.cc
	$(CC) $(CCFLAGS) -o $@ -c $<

.depend:
	g++ -MM $(SRC) > .depends
-include .depends

clean:
	rm -f $(OBJ) $(EXEC)

CXX = g++
N ?= 5
CXXFLAGS = -Wall -ansi -pedantic -ftemplate-depth=50000

all: hanoi bridge-dynamic-static

hanoi: hanoi.o
	$(CXX) $< -o $@

bridge-dynamic-static: bridge-dynamic-static.o
	$(CXX) $< -o $@

.cc.o: $<
	$(CXX) $(CXXFLAGS) -DN=$(N) -c $< -o $@

clean:
	$(RM) *.o

distclean: clean
	$(RM) hanoi bridge-dynamic-static
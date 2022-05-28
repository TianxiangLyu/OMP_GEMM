CC = g++ #g++
CFLAGS += -std=c++11 -O3 -ffast-math -funroll-loops
#CFLAGS += -Xpreprocessor -fopenmp 
CFLAGS += -fopenmp
#LIBS = -lomp
CPPOBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
CPPHDRS = $(wildcard *.h)
PROGRAM = gemm.out

.PHONY: clean all

all:    $(CPPOBJS) $(CPPHDRS)
	@echo "Linking object files..."
	@$(CC) $(CFLAGS) $(WARNINGS) $(CPPOBJS) -o $(PROGRAM) $(LIBS) $(INC_PATH)
	@echo "Link Success! [$(PROGRAM)]"

%.o:    %.cpp $(CPPHDRS)
	@echo "Bulding $< ..."
	@$(CC) -c $< $(CFLAGS) $(WARNINGS) $(INC_PATH)
	@echo "[$< OK]"

clean:
	-rm *.out *.o

distclean: clean
	rm -rf result
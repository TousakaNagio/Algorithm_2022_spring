# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

all	: bin/cl
	@echo -n ""

# optimized version
bin/cl	: CellLegalization_opt.o main_opt.o lib
			$(CC) $(OPTFLAGS) CellLegalization_opt.o main_opt.o -ltm_usage -Llib -o bin/cl
main_opt.o 	   	: src/main.cpp lib/tm_usage.h
			$(CC) $(CFLAGS) $< -Ilib -o $@
CellLegalization_opt.o	: src/CellLegalization.cpp src/CellLegalization.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# DEBUG Version
dbg : bin/cl_dbg
	@echo -n ""

bin/cl_dbg	: CellLegalization_dbg.o main_dbg.o lib
			$(CC) $(DBGFLAGS) CellLegalization_dbg.o main_dbg.o -ltm_usage -Llib -o bin/cl_dbg
main_dbg.o 	   	: src/main.cpp lib/tm_usage.h
			$(CC) $(CFLAGS) $< -Ilib -o $@
CellLegalization_dbg.o	: src/CellLegalization.cpp src/CellLegalization.h
			$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

lib: lib/libtm_usage.a

lib/libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<
tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $<

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*


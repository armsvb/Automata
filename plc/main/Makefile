include ../../Makefile.inc

all: $(BASE)/bin/lib/libautomataPLC.a
	
	
$(BASE)/bin/lib/libautomataPLC.a: $(BASE)/build/plc/TaskPromise.o
	#gcc -c src/TaskPromise.cc $(CFLAGS) $(LDFLAGS) -I ./include -o $(BASE)/build/TaskPromise.o
	ar rcs $(BASE)/bin/lib/libautomataPLC.a $(BASE)/build/plc/TaskPromise.o
	
$(BASE)/build/plc/TaskPromise.o: src/TaskPromise.cc ./include/IScheduler.h
	gcc $(DEBUG) -c src/TaskPromise.cc $(CFLAGS) -I ./include -o $(BASE)/build/plc/TaskPromise.o
	

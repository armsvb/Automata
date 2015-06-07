include ../../Makefile.inc

all: $(BASE)/bin/lib/libautomataPLC.a
	
	
$(BASE)/bin/lib/libautomataPLC.a: $(BASE)/build/plc/TaskPromise.o $(BASE)/build/plc/ITask.o
	ar rcs $(BASE)/bin/lib/libautomataPLC.a $(BASE)/build/plc/TaskPromise.o $(BASE)/build/plc/ITask.o
	
$(BASE)/build/plc/ITask.o: src/ITask.cc ./include/IScheduler.h
	$(CC) $(DEBUG) -c src/ITask.cc $(CFLAGS) -I ./include -o $(BASE)/build/plc/ITask.o
	
$(BASE)/build/plc/TaskPromise.o: src/TaskPromise.cc ./include/IScheduler.h
	$(CC) $(DEBUG) -c src/TaskPromise.cc $(CFLAGS) -I ./include -o $(BASE)/build/plc/TaskPromise.o
	

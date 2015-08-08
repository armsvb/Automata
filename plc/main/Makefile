include ../../Makefile.inc

all: $(BASE)/bin/lib/libautomataPLC.a
	
	
$(BASE)/bin/lib/libautomataPLC.a: $(BASE)/build/plc/Scheduler.o
	ar rcs $(BASE)/bin/lib/libautomataPLC.a $(BASE)/build/plc/Scheduler.o
	

$(BASE)/build/plc/Scheduler.o: src/Scheduler.cc ./include/Scheduler.h
	$(CC) $(DEBUG) -c src/Scheduler.cc $(CFLAGS) -I ./include -o $(BASE)/build/plc/Scheduler.o

	

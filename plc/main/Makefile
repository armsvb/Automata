include ../../Makefile.inc

all: $(BASE)/bin/lib/libautomataPLC.a
	
	
$(BASE)/bin/lib/libautomataPLC.a: $(BASE)/build/plc/DefaultScheduler.o
	ar rcs $(BASE)/bin/lib/libautomataPLC.a $(BASE)/build/plc/DefaultScheduler.o
	

$(BASE)/build/plc/DefaultScheduler.o: src/DefaultScheduler.cc ./include/IScheduler.h
	$(CC) $(DEBUG) -c src/DefaultScheduler.cc $(CFLAGS) -I ./include -o $(BASE)/build/plc/DefaultScheduler.o	

	

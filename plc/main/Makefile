include ../../Makefile.inc

all: $(BASE)/bin/lib/libautomataPLC.a
	
	
$(BASE)/bin/lib/libautomataPLC.a: $(BASE)/build/plc/OneShot.o
	ar rcs $(BASE)/bin/lib/libautomataPLC.a $(BASE)/build/plc/OneShot.o
	

$(BASE)/build/plc/OneShot.o: src/OneShot.cc ./include/IScheduler.h
	$(CC) $(DEBUG) -c src/OneShot.cc $(CFLAGS) -I ./include -o $(BASE)/build/plc/OneShot.o	

	

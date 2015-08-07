include ../../../../Makefile.inc

export LD_LIBRARY_PATH=$(BASE)/lib/boost/bin/lib;$LD_LIBRARY_PATH

all: $(BASE)/bin/test/testScheduler

test: $(BASE)/bin/test/testScheduler 
	$(BASE)/bin/test/testScheduler --show_progress
	
$(BASE)/bin/test/testScheduler: testOneShot.cc testInterval.cc $(BASE)/bin/lib/libautomataPLC.a
	$(CC) $(DEBUG) $(CFLAGS) -o $(BASE)/bin/test/testScheduler testInterval.cc testOneShot.cc $(LDFLAGS) -L$(BASE)/bin/lib -lautomataPLC  -lboost_unit_test_framework 
	


include ../../../../Makefile.inc

export LD_LIBRARY_PATH=$(BASE)/lib/boost/bin/lib;$LD_LIBRARY_PATH

all: $(BASE)/bin/test/testScheduler

test: $(BASE)/bin/test/testScheduler 
	$(BASE)/bin/test/testScheduler --show_progress
	
$(BASE)/bin/test/testScheduler: testTaskPromise.cc testITask.cc $(BASE)/bin/lib/libautomataPLC.a
	$(CC) $(DEBUG) -o $(BASE)/bin/test/testScheduler testTaskPromise.cc testITask.cc $(CFLAGS) $(LDFLAGS) -L$(BASE)/bin/lib -lautomataPLC  -lboost_unit_test_framework  
	


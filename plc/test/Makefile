include ../../Makefile.inc

all: scheduler

scheduler : force_look
	cd src/Scheduler; $(MAKE) $(MFLAGS)
	
	
test: force_look
	cd src/Scheduler; $(MAKE) $(MFLAGS) test

force_look :
	true

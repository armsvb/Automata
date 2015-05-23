include Makefile.inc


all : prep plc
	true

prep: force_look
	mkdir -p build/plc
	mkdir -p bin
	mkdir -p bin/test
	mkdir -p bin/lib


clean: force_look
	rm -rf build
	rm -rf bin

plc : force_look
	$(MAKE) $(MFLAGS) -C plc
	
test: force_look
	$(MAKE) $(MFLAGS) -C plc/test test

force_look :
	true
	

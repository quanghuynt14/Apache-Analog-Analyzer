CPP = g++
CPPFLAGS = -g -Wall -Werror -pedantic -ansi -DSPEEDTEST -DMAP 
OPTIMIZATION = -O3
EXE = analog
INT = $(wildcard src/*.h)
REAL = $(INT:.h=.cpp) src/ApacheLogAnalyzer.cpp
ECHO = @echo
.PHONY: clean tests

help:
	$(ECHO) " help    : Display this message"
	$(ECHO) " debug   : Build debug version of <ApacheLogAnalyzer>"
	$(ECHO) " release : Build release version of <ApacheLogAnalyzer>"
	$(ECHO) " tests   : Run all tests"
	$(ECHO) " clean   : Delete binary files"

debug:
	$(ECHO) "Building debug version of <$(EXE)> ..."
	@ $(CPP) $(CPPFLAGS) -std=c++11 -o $(EXE) $(REAL)

release:
	$(ECHO) "Building release version of <$(EXE)> ..."
	@ $(CPP) $(OPTIMIZATION) -std=c++11 -o $(EXE) $(REAL)

test:
	$(ECHO) "Running tests ..."
	@ cd Tests/ && bash ./mktest.sh

clean:
	@ rm analog
	$(ECHO) "analog is now deleted"

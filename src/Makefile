EXENAME = main
OBJS = main.o graph.o vertex.o utility.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

#object file dependncies
main.o : main.cpp graph.cpp graph.h 
	$(CXX) $(CXXFLAGS) main.cpp

graph.o : graph.cpp graph.h vertex.cpp vertex.h utility.h utility.cpp
	$(CXX) $(CXXFLAGS) graph.cpp

vertex.o : vertex.cpp vertex.h utility.h utility.cpp
	$(CXX) $(CXXFLAGS) vertex.cpp 

utility.o : utility.cpp utility.h
	$(CXX) $(CXXFLAGS) utility.cpp

# Custom Clang version enforcement Makefile rule:
# for using 'make test'
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1'. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

output_msg: ; $(CLANG_VERSION_MSG)

test: output_msg ../catch/catchmain.cpp ../tests/graph-tests.cpp graph.cpp vertex.cpp utility.cpp
	$(LD) ../catch/catchmain.cpp ../tests/graph-tests.cpp graph.cpp vertex.cpp utility.cpp $(LDFLAGS) -o test

.PHONY: output_msg
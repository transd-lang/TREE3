# In case a c++ compiler is not automatically detected, please set
# the CC variable manually with the command or path of your c++ compiler.
# For example: CC = /usr/bin/g++
CC =

ifeq (, $(CC))
ifneq (,$(shell which g++ 2>/dev/null))
CC := g++
else
ifneq (,$(shell which clang++ 2>/dev/null))
CC := clang++
endif
endif
endif

ifeq (, $(CC))
$(error Error: no known c++ compilers found. Please, set the CC variable in the Makefile manually.)
endif

CPPFILES := src/transd.cpp src/main.cpp

all: $(CPPFILES)
	$(CC) -static -std=c++14 -O2 $(CPPFILES) -D__LINUX__ -lpthread -o frend

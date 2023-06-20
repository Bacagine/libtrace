## 
## \file Makefile
## 
## \brief Makefile for the project logger
## 
## This is the a Makefile to my personal logger C library
##
## \author NAME <gustavo.bacagine@protonmail.com>
##
## \date: 2023-06-18 
##

TARGET     = liblog.so
SRCDIR     = ./src
INCDIR     = ./include/log
MANDIR     = ./man
OBJDIR     = ./obj
LIBDIR     = ./lib
BINDIR     = ./bin
TESTDIR    = ./tests
MAN        = $(MANDIR)/$(TARGET).1
SRC        = $(wildcard $(SRCDIR)/*.c)
OBJS       = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
LIB        = $(LIBDIR)/$(TARGET)
LDFLAGS    = -L $(LIBDIR)
LDLIBS     = -lm -pthread -lncurses
CFLAGS     = -I $(INCDIR) -Wall -Wextra -O3
DEBUGFLAGS = -g -O0 -DDEBUG_COMPILATION
CC         = gcc

ifdef DEBUG_COMPILATION
	CFLAGS += $(DEBUGFLAGS) 
	LDFLAGS += $(DEBUGFLAGS)
endif

run: all
	$(BIN)

all: $(OBJDIR) $(LIBDIR) $(BINDIR) $(LIB)
	
$(LIB): $(OBJS)
	$(CC) -shared -o $@ $(OBJS) $(CFLAGS) $(LDLIBS)

$(BINDIR):
	mkdir $@
$(LIBDIR):
	mkdir $@
$(OBJDIR):
	mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -fPIC -c $< -o $@ $(CFLAGS) $(LDLIBS)

debug: clean all

clean:
	rm -rvf $(OBJDIR)

install: all
	cp -r include/log/ /usr/include/
	cp -r $(LIB) /usr/lib/$(TARGET)

uninstall:
	rm -r /usr/include/log
	rm -r $(LIB) /usr/lib/$(TARGET)

test: $(LIB)
	export LD_LIBRARY_PATH=LD_LIBRARY_PATH:$(CURDIR)/lib
	$(CC) -o $(BINDIR)/trace $(TESTDIR)/trace.c  $(CFLAGS) $(LDFLAGS) -llog
	$(CC) -o $(BINDIR)/debug $(TESTDIR)/debug.c  $(CFLAGS) $(LDFLAGS) -llog
	$(CC) -o $(BINDIR)/colored $(TESTDIR)/colored.c  $(CFLAGS) $(LDFLAGS) -llog
	
distclean: clean
	rm -rvf *.log
	rm -rvf $(LIBDIR)
	rm -rvf $(BINDIR)/trace
	rm -rvf $(BINDIR)/debug
	rm -rvf $(BINDIR)/colored
	
.PHONY: all clean debug install uninstall test check dist distclean


## 
## \file Makefile
## 
## \brief Makefile for the project logger
## 
## This is the a Makefile to my personal logger C library
##
## \author Gustavo Bacagine <gustavo.bacagine@protonmail.com>
##
## \date: 2023-06-16
##

TARGET     = liblog.so
SRCDIR     = src
INCDIR     = include/log
OBJDIR     = obj
LIBDIR     = lib
BINDIR     = bin
TESTDIR    = tests
SRC        = $(wildcard $(SRCDIR)/*.c)
OBJS       = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
LIB        = $(LIBDIR)/$(TARGET)
LDFLAGS    = -L $(LIBDIR)
LDLIBS     = -lm -pthread
CFLAGS     = -I $(INCDIR) -Wall -Wextra -O3
DEBUGFLAGS = -g -O0 -DDEBUG_COMPILATION
CC         = gcc

ifdef DEBUG_COMPILATION
	CFLAGS += $(DEBUGFLAGS) 
	LDFLAGS += $(DEBUGFLAGS)
endif

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

test: all
	$(CC) -o $(BINDIR)/trace $(TESTDIR)/trace.c  $(CFLAGS) $(LDFLAGS) -llog
	$(CC) -o $(BINDIR)/debug $(TESTDIR)/debug.c  $(CFLAGS) $(LDFLAGS) -llog
	$(CC) -o $(BINDIR)/colored $(TESTDIR)/colored.c  $(CFLAGS) $(LDFLAGS) -llog
	
distclean: clean
	rm -rvf *.log
	rm -rvf $(LIBDIR)
	rm -rvf $(BINDIR)
	
.PHONY: all clean debug install uninstall test check dist distclean


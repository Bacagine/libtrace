# 
# Makefile
# 
# Makefile for the project logger
# 
# This is the a Makefile to my personal logger C library
#
# Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
#
# Date: 2023-06-16
#

TARGET     = libtrace.so
SRCDIR     = src
INCDIR     = include/trace
OBJDIR     = obj
LIBDIR     = lib
BINDIR     = bin
TESTDIR    = tests
SRC        = $(wildcard $(SRCDIR)/*.c)
OBJS       = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
LIB        = $(LIBDIR)/$(TARGET)
LDFLAGS    = -L $(LIBDIR)
LDLIBS     = -lm -pthread
CFLAGS     = -I $(INCDIR) -Wall -Wextra
DEBUGFLAGS = -g -O0 -DDEBUG_COMPILATION
CC         = gcc

ifdef LINUX
	CFLAGS += -DLINUX
	LDFLAGS += -DLINUX
endif

ifdef _WIN32
	CFLAGS += -D_WIN32
	LDFLAGS += -D_WIN32
endif

ifdef DEBUG
	CFLAGS += $(DEBUGFLAGS) 
	LDFLAGS += $(DEBUGFLAGS)
else
	CFLAGS += -O3
endif

all: distclean $(OBJDIR) $(LIBDIR) $(LIB)
	
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

clean:
	rm -rvf $(OBJDIR)

install: all
	./install.sh

uninstall:
	./uninstall.sh

test: all $(BINDIR)
	$(CC) -o $(BINDIR)/hello_trace $(TESTDIR)/hello_trace.c  $(CFLAGS) $(LDFLAGS) -ltrace
	$(CC) -o $(BINDIR)/trace_function $(TESTDIR)/trace_function.c  $(CFLAGS) $(LDFLAGS) -ltrace
	$(CC) -o $(BINDIR)/trace_level $(TESTDIR)/trace_level.c  $(CFLAGS) $(LDFLAGS) -ltrace
	$(CC) -o $(BINDIR)/debug $(TESTDIR)/debug.c  $(CFLAGS) $(LDFLAGS) -ltrace
	$(CC)	-c $(TESTDIR)/module1.c -o $(OBJDIR)/module1.o $(CFLAGS) $(LDFLAGS) -ltrace
	$(CC)	-c $(TESTDIR)/module2.c -o $(OBJDIR)/module2.o $(CFLAGS) $(LDFLAGS) -ltrace
	$(CC) -o $(BINDIR)/module $(OBJDIR)/module1.o $(OBJDIR)/module2.o $(CFLAGS) $(LDFLAGS) -ltrace
	
distclean: clean
	./remove_logs.sh
	rm -rvf $(LIBDIR)
	rm -rvf $(BINDIR)
	
.PHONY: all clean debug install uninstall test check dist distclean


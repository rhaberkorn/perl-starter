CC := gcc
RC := windres

#PERL := perl
PERL := /c/strawberry/perl/bin/perl

PERL_CCOPTS := $(shell $(PERL) -MExtUtils::Embed -e ccopts)
#PERL_LDOPTS := $(shell $(PERL) -MExtUtils::Embed -e ldopts)
PERL_LDOPTS := -L/c/strawberry/perl/lib/CORE -lperl510

CFLAGS := $(PERL_CCOPTS) -std=gnu99
CPPFLAGS :=
LDFLAGS := $(PERL_LDOPTS) -mwindows

all : kephra.exe

starter_xsi.c:
	$(PERL) -MExtUtils::Embed -e xsinit -- -o $@

kephra.o : kephra.rc kephra_proton.ico kephra.manifest
	$(RC) $< $@

kephra.exe : starter.o starter_xsi.o kephra.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o starter_xsi.c kephra.exe

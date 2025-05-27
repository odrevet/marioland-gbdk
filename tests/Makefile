LCC = $(GBDK_HOME)/bin/lcc
PROJECTNAME = $(FILE)
BINS	    = $(PROJECTNAME).gb
CSOURCES := $(shell find src -name '*.c' ! -name 'main.c') tests/$(FILE).c
CFLAGS = -autobank -Wm-yt0x1A -Wm-yo8 -Wm-ya4 

all:	$(BINS)

$(BINS):	$(CSOURCES)
	$(LCC) $(CFLAGS) -o $@ hUGEDriver.o $(CSOURCES) $(CPPFLAGS)

clean:
	rm -f $(BINS)

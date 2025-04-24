LCC = $(GBDK_HOME)/bin/lcc
PROJECTNAME = marioland
BINS	    = $(PROJECTNAME).gb
CSOURCES := $(shell find src -name '*.c')
CFLAGS = -autobank -Wm-yt0x1A -Wm-yo8 -Wm-ya4 

DEBUG=no
ifeq ($(DEBUG),yes)
	CPPFLAGS = -DDEBUG
endif


all:	$(BINS)

$(BINS):	$(CSOURCES)
	$(LCC) $(CFLAGS) -o $@ hUGEDriver.o $(CSOURCES) $(CPPFLAGS)

clean:
	rm -f src/levels/* $(BINS)

clean_graphics:
	rm -f src/graphics/*

clean_sounds:
	rm -f src/sounds/*
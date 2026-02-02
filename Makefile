SHELL := /bin/bash
LCC = $(GBDK_HOME)/bin/lcc
TARGETS=nes gb
# Configure platform specific LCC flags here:
LCCFLAGS_gb      = -Wl-yt0x19 -Wm-yn"$(PROJECTNAME)"
LCCFLAGS_pocket  = -Wl-yt0x19 -Wm-yn"$(PROJECTNAME)"
LCCFLAGS_duck    = -Wl-yt0x19 -Wm-yn"$(PROJECTNAME)"
LCCFLAGS_sms     = 
LCCFLAGS_gg      =
LCCFLAGS_nes     = -Wb-min=0
LCCFLAGS += $(LCCFLAGS_$(EXT)) # This adds the current platform specific LCC Flags
LCCFLAGS += -Wl-j -Wm-yoA -autobank -Wb-ext=.rel # MBC + Autobanking related flags
LCCFLAGS += -Wl-j -Wl-w -Wm-yS
# LCCFLAGS += -debug      # Uncomment to enable debug output
LCCFLAGS += -v -Wb-v    # Uncomment for lcc verbose output#
LCCFLAGS += -Wa-l -Wl-u

# Conditional compilation flags and includes based on PORT
ifeq ($(PORT),sm83)
CFLAGS   = -Wf-DUSE_COMPRESSED_LEVELS -Wf-Isrc -Wf-I$(PORT) -Wf-Ilevel_maps_compressed -Wf-MMD
EXTRA_OBJ := hUGEDriver.o
LEVEL_DIR := level_maps_compressed
else
CFLAGS   = -Wf-Isrc -Wf-I$(PORT) -Wf-Ilevel_maps -Wf-MMD
LEVEL_DIR := level_maps
endif

#CFLAGS   += -Wf'--max-allocs-per-node 50000'
# You can set the name of the ROM file here
PROJECTNAME = marioland
SRCDIR      = src
OBJDIR      = obj#/$(EXT)
RESDIR      = res
BINDIR      = build/$(EXT)
MKDIRS      = $(OBJDIR) $(BINDIR) # See bottom of Makefile for directory auto-creation
BINS        = $(OBJDIR)/$(PROJECTNAME).$(EXT)

CSOURCES := $(shell find $(PORT) -name '*.c')
CSOURCES += $(shell find $(LEVEL_DIR) -name '*.c')
CSOURCES += $(shell find $(SRCDIR) -name '*.c')

all:    $(BINS)

$(BINS):    $(CSOURCES) $(EXTRA_OBJ)
	$(LCC) $(LCCFLAGS) $(CFLAGS) -o $(BINDIR)/$(PROJECTNAME).$(EXT) $(EXTRA_OBJ) $(CSOURCES)

clean:
	@echo Cleaning
	@for target in $(TARGETS); do \
		$(MAKE) $$target-clean; \
    done

# Include available build targets
include Makefile.targets

# create necessary directories after Makefile is parsed but before build
# info prevents the command from being pasted into the makefile
ifneq ($(strip $(EXT)),)           # Only make the directories if EXT has been set by a target
$(info $(shell mkdir -p $(MKDIRS)))
endif
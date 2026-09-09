ifndef GBDK_HOME
    $(error GBDK_HOME is not defined. Please set it before running make)
endif

PNG2ASSET = $(GBDK_HOME)/bin/png2asset 
LCC = $(GBDK_HOME)/bin/lcc 
UGE2SOURCE = $(HOME)/bin/hUGETracker-1.0.11-linux/uge2source
VGM2DATA = python3 $(HOME)/projects/VGM2GBSFX/utils/vgm2data.py

# Set platforms to build here, spaced separated. (These are in the separate Makefile.targets)
# They can also be built/cleaned individually: "make gg" and "make gg-clean"
# Possible are: gb gbc pocket megaduck sms gg
TARGETS=gb pocket megaduck sms gg nes

# You can set flags for LCC here
# For example, you can uncomment the line below to turn on debug output
# LCCFLAGS = -debug

# You can set the name of the .gb ROM file here
PROJECTNAME    = marioland

SRCDIR      = src
DISTDIR      = dist
OBJDIR      = obj/$(EXT)
RESDIR      = res
GENDIR      = gen/$(EXT)/src
BINDIR      = build/$(EXT)
MKDIRS      = $(GENDIR) $(OBJDIR) $(BINDIR) # See bottom of Makefile for directory auto-creation
BINS	    = $(OBJDIR)/$(PROJECTNAME).$(EXT)
CSOURCES    = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c))) 
GENSOURCES    = $(foreach dir,$(GENDIR), $(wildcard $(dir)/*.c))
ASMSOURCES  = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.s)))
OBJS       = $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.s=$(OBJDIR)/%.o)

# sm83-specific
ifeq ($(PORT),sm83)
EXTRA_OBJ := hUGEDriver.o
endif

# PORT specific
PORTSOURCES := $(notdir $(wildcard $(PORT)/*.c))
PORTOBJS := $(PORTSOURCES:%.c=$(OBJDIR)/%.o)
OBJS += $(PORTOBJS)
CFLAGS += -Wf-I$(PORT)

LCCFLAGS += -Wl-j -Wm-yoA -Wm-ya4 -Wb-ext=.rel $(LCCFLAGS_$(EXT)) # This adds the current platform specific LCC Flags


# Configure platform specific LCC flags here:
LCCFLAGS_gb      = -Wm-ys -Wl-yt0x1B -autobank # Set an MBC for banking (1B-ROM+MBC5+RAM+BATT)
LCCFLAGS_pocket  = -Wm-ys -Wl-yt0x1B -autobank # Usually the same as required for .gb
LCCFLAGS_duck    = -Wm-ys -Wl-yt0x1B -autobank # Usually the same as required for .gb
LCCFLAGS_gbc     = -Wm-ys -Wl-yt0x1B -Wm-yc -autobank # Same as .gb with: -Wm-yc (gb & gbc) or Wm-yC (gbc exclusive)
LCCFLAGS_sms     = -Wm-ys -Wl-yt0x1B -autobank
LCCFLAGS_gg      = -Wm-ys -Wl-yt0x1B -autobank
LCCFLAGS_nes     = -Wm-ys -Wl-yt0x1B -autobank

all: $(TARGETS)

assets: png2asset

ifeq ($(PORT),sm83)
build-target: png2asset uge2source vgm2data $(BINS)
else 
build-target: png2asset $(BINS)
endif

compile-target: $(BINS)

# png2asset settings for backgrounds
PNG2ASSET_BKG_SETTINGS_gg=-pack_mode sms -bpp 4
PNG2ASSET_BKG_SETTINGS_sms=-pack_mode sms -bpp 4
PNG2ASSET_BKG_SETTINGS_nes=-noflip -bpp 2 -pack_mode nes
PNG2ASSET_BKG_SETTINGS_gb=
PNG2ASSET_BKG_SETTINGS_gbc=
PNG2ASSET_BKG_SETTINGS_duck=
PNG2ASSET_BKG_SETTINGS_pocket=

# png2asset settings for sprites
PNG2ASSET_SPRITE_SETTINGS_gg=-noflip -pack_mode sms -bpp 4
PNG2ASSET_SPRITE_SETTINGS_sms=-noflip -pack_mode sms -bpp 4
PNG2ASSET_SPRITE_SETTINGS_nes=
PNG2ASSET_SPRITE_SETTINGS_gb=
PNG2ASSET_SPRITE_SETTINGS_gbc=
PNG2ASSET_SPRITE_SETTINGS_duck=
PNG2ASSET_SPRITE_SETTINGS_pocket=

LEVEL_TILESET_1 = birabuto
LEVEL_TILESET_2 = muda
LEVEL_TILESET_3 = easton
LEVEL_TILESET_4 = chai

define BUILD_LEVEL_ASSETS
for f in res/graphics/levels/$(1)/*.png; do n=$$(basename $$f .png); $(PNG2ASSET) $$f -c $(GENDIR)/level_$$n.c -noflip -map -maps_only -tile_origin 40 -source_tileset res/graphics/tilesets/common.png -source_tileset res/graphics/tilesets/$(LEVEL_TILESET_$(1)).png $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -keep_duplicate_tiles -b 255; done
endef

ifneq ($(filter sm83 mod6502,$(PORT)),)
	TILE_ORIGIN := 0
	ENEMIES_TILE_ORIGIN := 53
	COMMON_TILE_ORIGIN := 60
	WORLD_ENEMIES_TILE_ORIGIN := 73
else
	TILE_ORIGIN := 0
	ENEMIES_TILE_ORIGIN := 102
	COMMON_TILE_ORIGIN := 109
	WORLD_ENEMIES_TILE_ORIGIN := 122
endif

png2asset:
# title
	$(PNG2ASSET) res/graphics/title-screen.png -c $(GENDIR)/TitleScreen.c -noflip -map $(PNG2ASSET_BKG_SETTINGS_$(EXT))  -b 255

# sprites
	$(PNG2ASSET) res/graphics/sprites/mario-$(SPRITES).png -o $(GENDIR)/marioSprites.c -sw 16 -sh 16 -spr8x8 -keep_palette_order -tile_origin $(TILE_ORIGIN) $(PNG2ASSET_SPRITE_SETTINGS_$(EXT)) -b 255
	$(PNG2ASSET) res/graphics/sprites/enemies_common-$(SPRITES).png -o $(GENDIR)/enemiesSprites.c -sw 8 -sh 16 -spr8x8 -keep_palette_order -tile_origin $(ENEMIES_TILE_ORIGIN) $(PNG2ASSET_SPRITE_SETTINGS_$(EXT)) -b 255
	$(PNG2ASSET) res/graphics/sprites/common-$(SPRITES).png -o $(GENDIR)/commonSprites.c -sw 8 -sh 8 -spr8x8 -keep_palette_order -tile_origin $(COMMON_TILE_ORIGIN) $(PNG2ASSET_SPRITE_SETTINGS_$(EXT)) -b 255
	$(PNG2ASSET) res/graphics/sprites/enemies_birabuto-$(SPRITES).png -o $(GENDIR)/enemiesBirabutoSprites.c -sw 16 -sh 16 -spr8x8 -keep_palette_order -tile_origin $(WORLD_ENEMIES_TILE_ORIGIN) $(PNG2ASSET_SPRITE_SETTINGS_$(EXT)) -b 255
	$(PNG2ASSET) res/graphics/sprites/enemies_muda-$(SPRITES).png -o $(GENDIR)/enemiesMudaSprites.c -sw 16 -sh 16 -spr8x8 -keep_palette_order -tile_origin $(WORLD_ENEMIES_TILE_ORIGIN) $(PNG2ASSET_SPRITE_SETTINGS_$(EXT)) -b 255
	$(PNG2ASSET) res/graphics/sprites/enemies_easton-$(SPRITES).png -o $(GENDIR)/enemiesEastonSprites.c -sw 16 -sh 16 -spr8x8 -keep_palette_order -tile_origin $(WORLD_ENEMIES_TILE_ORIGIN) $(PNG2ASSET_SPRITE_SETTINGS_$(EXT)) -b 255
	$(PNG2ASSET) res/graphics/sprites/enemies_chai-$(SPRITES).png -o $(GENDIR)/enemiesChaiSprites.c -sw 16 -sh 16 -spr8x8 -keep_palette_order -tile_origin $(WORLD_ENEMIES_TILE_ORIGIN) $(PNG2ASSET_SPRITE_SETTINGS_$(EXT)) -b 255

# tilesets
	$(PNG2ASSET) res/graphics/tilesets/text.png -o $(GENDIR)/textTileset.c -keep_palette_order -keep_duplicate_tiles -noflip -map $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -b 255
	$(PNG2ASSET) res/graphics/tilesets/common.png -o $(GENDIR)/commonTileset.c -keep_palette_order -keep_duplicate_tiles -noflip -map -tile_origin 40 $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -b 255
	$(PNG2ASSET) res/graphics/tilesets/birabuto.png -o $(GENDIR)/birabutoTileset.c -keep_palette_order -keep_duplicate_tiles -noflip -map -tile_origin 96 $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -b 255
	$(PNG2ASSET) res/graphics/tilesets/muda.png -o $(GENDIR)/mudaTileset.c -keep_palette_order -keep_duplicate_tiles -noflip -map -tile_origin 96 $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -b 255
	$(PNG2ASSET) res/graphics/tilesets/chai.png -o $(GENDIR)/chaiTileset.c -keep_palette_order -keep_duplicate_tiles -noflip -map -tile_origin 96 $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -b 255
	$(PNG2ASSET) res/graphics/tilesets/easton.png -o $(GENDIR)/eastonTileset.c -keep_palette_order -keep_duplicate_tiles -noflip -map -tile_origin 96 $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -b 255
	
# levels pages
	$(call BUILD_LEVEL_ASSETS,1)
	$(call BUILD_LEVEL_ASSETS,2)
	$(call BUILD_LEVEL_ASSETS,3)
	$(call BUILD_LEVEL_ASSETS,4)

# levels gates, stage end and underground pages
	$(PNG2ASSET) res/graphics/levels/misc/gates.png -c $(GENDIR)/level_gates.c -noflip -map -maps_only -tile_origin 40 -source_tileset res/graphics/tilesets/common.png $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -keep_duplicate_tiles -b 255
	$(PNG2ASSET) res/graphics/levels/misc/stage_end.png -c $(GENDIR)/stage_end.c -noflip -map -maps_only -tile_origin 40 -source_tileset res/graphics/tilesets/common.png $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -keep_duplicate_tiles -b 255
	$(PNG2ASSET) res/graphics/levels/misc/underground_0.png -c $(GENDIR)/underground_0.c -noflip -map -maps_only -tile_origin 40 -source_tileset res/graphics/tilesets/common.png $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -keep_duplicate_tiles -b 255
	$(PNG2ASSET) res/graphics/levels/misc/underground_1.png -c $(GENDIR)/underground_1.c -noflip -map -maps_only -tile_origin 40 -source_tileset res/graphics/tilesets/common.png $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -keep_duplicate_tiles -b 255
	$(PNG2ASSET) res/graphics/levels/misc/underground_2.png -c $(GENDIR)/underground_2.c -noflip -map -maps_only -tile_origin 40 -source_tileset res/graphics/tilesets/common.png $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -keep_duplicate_tiles -b 255
	$(PNG2ASSET) res/graphics/levels/misc/underground_3.png -c $(GENDIR)/underground_3.c -noflip -map -maps_only -tile_origin 40 -source_tileset res/graphics/tilesets/common.png $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -keep_duplicate_tiles -b 255
	$(PNG2ASSET) res/graphics/levels/misc/underground_4.png -c $(GENDIR)/underground_4.c -noflip -map -maps_only -tile_origin 40 -source_tileset res/graphics/tilesets/common.png $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -keep_duplicate_tiles -b 255
	$(PNG2ASSET) res/graphics/levels/misc/underground_5.png -c $(GENDIR)/underground_5.c -noflip -map -maps_only -tile_origin 40 -source_tileset res/graphics/tilesets/common.png $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -keep_duplicate_tiles -b 255
	$(PNG2ASSET) res/graphics/levels/misc/underground_6.png -c $(GENDIR)/underground_6.c -noflip -map -maps_only -tile_origin 40 -source_tileset res/graphics/tilesets/common.png $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -keep_duplicate_tiles -b 255
	$(PNG2ASSET) res/graphics/levels/misc/underground_7.png -c $(GENDIR)/underground_7.c -noflip -map -maps_only -tile_origin 40 -source_tileset res/graphics/tilesets/common.png $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -keep_duplicate_tiles -b 255
	$(PNG2ASSET) res/graphics/levels/misc/underground_8.png -c $(GENDIR)/underground_8.c -noflip -map -maps_only -tile_origin 40 -source_tileset res/graphics/tilesets/common.png $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -keep_duplicate_tiles -b 255
	$(PNG2ASSET) res/graphics/levels/misc/underground_9.png -c $(GENDIR)/underground_9.c -noflip -map -maps_only -tile_origin 40 -source_tileset res/graphics/tilesets/common.png $(PNG2ASSET_BKG_SETTINGS_$(EXT)) -keep_duplicate_tiles -b 255

# Generate music and sound sources (only for sm83 targets)
ifeq ($(PORT),sm83)
build-target: uge2source vgm2data

uge2source:
	@for f in res/musics/*.uge; do \
		n=$$(basename $$f .uge); \
		$(UGE2SOURCE) $$f -b 255 $$n $(GENDIR)/$$n.c; \
		sed -i ':a;N;$$!ba;s/= {\n};/= {{\n}};/g' $(GENDIR)/$$n.c; \
	done

vgm2data:
	@for f in res/sounds/*.vgm; do \
		n=$$(basename $$f .vgm); \
		echo $$f; \
		$(VGM2DATA) -o $(GENDIR)/$$n.c -i $$n $$f; \
	done
endif

# Compile .c files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.c 
	$(LCC) $(LCCFLAGS) $(CFLAGS) -I$(GENDIR) -Ires -c -o $@ $<

# Compile .c files in "sm83/" to .o object files
$(OBJDIR)/%.o:	sm83/%.c
	$(LCC) $(LCCFLAGS) $(CFLAGS) -I$(GENDIR) -Ires -c -o $@ $<

# Compile .s assembly files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.s
	$(LCC) $(LCCFLAGS) $(CFLAGS) -c -o $@ $<

# If needed, compile .c files in "src/" to .s assembly files
# (not required if .c is compiled directly to .o)
$(OBJDIR)/%.s:	$(SRCDIR)/%.c
	$(LCC) $(LCCFLAGS) $(CFLAGS) -S -o $@ $<

# Link the compiled object files into a .gb ROM file
$(BINS):	$(OBJS) $(EXTRA_OBJ)
	$(LCC) $(LCCFLAGS) $(CFLAGS) -I$(GENDIR) -o $(BINDIR)/$(PROJECTNAME).$(EXT) $(OBJS) $(EXTRA_OBJ) $(GENSOURCES)


prepare:
	mkdir -p $(OBJDIR)
	mkdir -p $(DISTDIR)
	mkdir -p $(GENDIR)

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
An attempt to recreate Super Mario Land using GBDK.

The project prioritizes code readability over optimization.

The resulting ROM is significantly larger than the original, as level data is generated from PNG-based tables.

The main goal remains to produce a playable game.

# Roadmap

* Platforms
* Enemies
* Blocks interaction
* Power ups : Mushroom / 1 up / Flower / star
* Pipes
* Bonus rooms
* Plane / submarin
* Bosses
* Cutscenes / ending
* background animations (torchs, falls, waves …)
* Super Mario Land musics / sound effects

# Level data

Map data are from https://vgmaps.com/Atlas/GB-GBC/ 

Splitted, resized and edited to remove sprites such as plateforms and bonuses.  

## images color mode

Images has 4 indexed colors from: fff 555 aaa 000 (exported as `assets/palette.txt`)

Colors must match between the tileset and the level map, otherwise png2asset will not match tiles in the tileset. 

With gimp: 

https://docs.gimp.org/3.0/en/gimp-image-convert-indexed.html

* Image → Mode → Indexed
* Generate optimum palette with 4 maximum number of colors

If needed, adjust each color of the palette using the color map window

* Windows → Dockable Dialogs → Colormap

or apply `assets/palette.txt`

# Sound and music data 

Sounds and musics from Super Mario Bros Mini https://github.com/Mico27/SuperMarioBrosMini/ 

(The musics and sounds are from Super Mario Bros until I found Super Mario Land ones)

VGM converted using VGM2GBSFX https://github.com/untoxa/VGM2GBSFX

UGE converted using hUGETracker uge2source https://github.com/SuperDisk/hUGETracker

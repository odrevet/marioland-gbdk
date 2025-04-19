An attempt to recreate Super Mario Land using GBDK.

The project prioritizes code readability over optimization.

The resulting ROM is significantly larger than the original, as level data is generated from PNG-based tables.

The main goal remains to produce a playable game.

# images color mode

Images has 4 indexed colors from: fff 555 aaa 000 (exported as `assets/palette.txt`)

Colors must match between the tileset and the level map, otherwise png2asset will not match tiles in the tileset. 

With gimp: 

https://docs.gimp.org/3.0/en/gimp-image-convert-indexed.html

* Image → Mode → Indexed
* Generate optimum palette with 4 maximum number of colors

If needed, adjust each color of the palette using the color map window

* Windows → Dockable Dialogs → Colormap

or apply `assets/palette.txt`
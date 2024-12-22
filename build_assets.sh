# sprite
png2asset "assets/mario.png" -o "src/graphics/mario.c" -sw 16 -sh 16
png2asset "assets/enemies.png" -o "src/graphics/enemies.c" -sw 16 -sh 16

text_tiles_count=40
common_tiles_count=40
birabuto_tiles_count=60
muda_tiles_count=60

# background
png2asset "assets/text.png" -o "src/graphics/text.c" -keep_palette_order -map -tiles_only -noflip -b 255
png2asset "assets/tilesets/common.png" -o "res/common" -map -bin -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $text_tiles_count
png2asset "assets/tilesets/birabuto.png" -o "res/birabuto" -map -bin -tiles_only -noflip  -keep_duplicate_tiles -b 255 -tile_origin $(($text_tiles_count + $common_tiles_count))
#png2asset "assets/tilesets/muda.png" -o "res/muda" -map -bin -tiles_only -noflip  -keep_duplicate_tiles -b 255 -tile_origin $(($text_tiles_count + $common_tiles_count))

convert_level_asset() {
    local level_number=$1
    local source_tileset=$2

    png2asset "assets/level_${level_number}.png" \
        -o "res/level_${level_number}" \
        -source_tileset "assets/tilesets/common.png" \
        -source_tileset "assets/tilesets/${source_tileset}.png" \
        -map -bin -transposed -noflip -keep_duplicate_tiles \
        -tile_origin "$text_tiles_count"

    # Compress the map file using RLE algorithm
    gbcompress --alg=rle "res/level_${level_number}_map.bin" "res/level_${level_number}_map.bin.rle"

    # Remove the original map file
    rm "res/level_${level_number}_map.bin"
}

echo "level 1_1"
convert_level_asset 1_1 birabuto

echo "level 1_2"
convert_level_asset 1_2 birabuto

echo "level 1_3"
convert_level_asset 1_3 birabuto

#echo "level 2_1"
#convert_level_asset 2_1 muda

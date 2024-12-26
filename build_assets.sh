text_tiles_count=40
common_tiles_count=40
birabuto_tiles_count=60
muda_tiles_count=60

common_tileset_starts=$text_tiles_count
level_tileset_starts=$(($common_tileset_starts + $common_tiles_count))

convert_level_asset() {
    local level_number=$1
    local source_tileset=$2

    level_image="assets/levels/raw_${level_number}.png"
    
    for page in 0 1; do
        local x_offset=$((page * 1200))
        # split the image
        convert $level_image -strip -crop 1200x+${x_offset}+0 +repage +adjoin "assets/levels/${level_number}_${page}.png"
        
        # convert image to bin
        png2asset "assets/levels/${level_number}_${page}.png" \
            -o "src/levels/level_${level_number}_${page}.c" \
            -source_tileset "assets/tilesets/common.png" \
            -source_tileset "assets/tilesets/${source_tileset}.png" \
            -map -noflip -keep_duplicate_tiles \
            -tile_origin "$text_tiles_count" -b 255
    done
}

# sprite
png2asset "assets/sprites/mario.png" -o "src/graphics/mario.c" -sw 16 -sh 16
png2asset "assets/sprites/enemies.png" -o "src/graphics/enemies.c" -sw 16 -sh 16

# background
png2asset "assets/text.png" -o "src/graphics/text.c" -keep_palette_order -map -tiles_only -noflip -b 255
png2asset "assets/tilesets/common.png" -o "src/graphics/common.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $common_tileset_starts
png2asset "assets/tilesets/birabuto.png" -o "src/graphics/birabuto.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $(($text_tiles_count + $common_tiles_count))
png2asset "assets/tilesets/muda.png" -o "src/graphics/muda.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $(($text_tiles_count + $common_tiles_count))

echo "level 1_1"
convert_level_asset 1_1 birabuto

echo "level 1_2"
convert_level_asset 1_2 birabuto

echo "level 1_3"
convert_level_asset 1_3 birabuto

#echo "level 2_1"
#convert_level_asset 2_1 muda

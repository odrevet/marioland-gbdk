get_define_value() {
  grep "#define $1" "$2" | awk '{print $3}'
}

convert_level_asset() {
    local level_number=$1
    local source_tileset=$2
    
    png2asset "assets/levels/${level_number}.png" \
    -o "src/levels/level_${level_number}.c" \
    -source_tileset "assets/tilesets/common.png" \
    -source_tileset "assets/tilesets/${source_tileset}.png" \
    -map -noflip -keep_duplicate_tiles \
    -tile_origin "$text_tiles_count" -b 255
}

# sprite
png2asset "assets/sprites/mario.png" -o "src/graphics/mario.c" -sw 16 -sh 16
png2asset "assets/sprites/enemies.png" -o "src/graphics/enemies.c" -sw 16 -sh 16

# background
png2asset "assets/text.png" -o "src/graphics/text.c" -keep_palette_order -map -tiles_only -noflip -b 255
text_tiles_count=$(get_define_value text_TILE_COUNT "src/graphics/text.h")

common_tileset_origin=$text_tiles_count

png2asset "assets/tilesets/common.png" -o "src/graphics/common.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $common_tileset_origin
common_tiles_count=$(get_define_value common_TILE_COUNT "src/graphics/common.h")

level_tiles_origin=$(($text_tiles_count + $common_tiles_count))
png2asset "assets/tilesets/birabuto.png" -o "src/graphics/birabuto.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $level_tiles_origin
png2asset "assets/tilesets/muda.png" -o "src/graphics/muda.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $level_tiles_origin

convert_level_asset 1_1 birabuto
convert_level_asset 1_2 birabuto
convert_level_asset 1_3 birabuto
convert_level_asset 2_1 muda
convert_level_asset 2_2 muda

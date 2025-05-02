get_define_value() {
  grep "#define $1" "$2" | awk '{print $3}'
}

convert_level_asset() {
    local level_number=$1
    local source_tileset=$2
    local tile_origin=$3
    
    png2asset "assets/levels/${level_number}.png" \
    -o "src/levels/level_${level_number}.c" \
    -source_tileset "assets/tilesets/common.png" \
    -source_tileset "assets/tilesets/${source_tileset}.png" \
    -map -noflip -keep_duplicate_tiles \
    -tile_origin "$tile_origin" -b 255
}

# sprite
tile_origin=0
echo "mario sprites"
png2asset "assets/sprites/mario.png" -o "src/graphics/mario.c" -sw 16 -sh 16 -tile_origin $tile_origin -b 255
tile_origin=$((tile_origin + $(get_define_value mario_TILE_COUNT "src/graphics/mario.h")))

echo "enemies sprites"
png2asset "assets/sprites/enemies.png" -o "src/graphics/enemies.c" -sw 8 -sh 16 -tile_origin $tile_origin -b 255
tile_origin=$((tile_origin + $(get_define_value enemies_TILE_COUNT "src/graphics/enemies.h")))

echo "common sprites"
png2asset "assets/sprites/common.png" -o "src/graphics/sprite_common.c" -sw 8 -sh 8 -spr8x8 -tile_origin $tile_origin -b 255

# background
echo "text background"
png2asset "assets/text.png" -o "src/graphics/text.c" -keep_palette_order -map -tiles_only -noflip -b 255
text_tiles_count=$(get_define_value text_TILE_COUNT "src/graphics/text.h")

common_tileset_origin=$text_tiles_count

echo "common background"
png2asset "assets/tilesets/common.png" -o "src/graphics/common.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $common_tileset_origin
common_tiles_count=$(get_define_value common_TILE_COUNT "src/graphics/common.h")

level_tiles_origin=$(($text_tiles_count + $common_tiles_count))
png2asset "assets/tilesets/birabuto.png" -o "src/graphics/birabuto.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $level_tiles_origin
png2asset "assets/tilesets/muda.png" -o "src/graphics/muda.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $level_tiles_origin
png2asset "assets/tilesets/easton.png" -o "src/graphics/easton.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $level_tiles_origin
png2asset "assets/tilesets/chai.png" -o "src/graphics/chai.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $level_tiles_origin

echo "1_1"
convert_level_asset 1_1 birabuto $common_tileset_origin

echo "1_2"
convert_level_asset 1_2 birabuto $common_tileset_origin

echo "1_3"
convert_level_asset 1_3 birabuto $common_tileset_origin

echo "2_1"
convert_level_asset 2_1 muda $common_tileset_origin

echo "2_2"
convert_level_asset 2_2 muda $common_tileset_origin

echo "2_3"
convert_level_asset 2_3 muda $common_tileset_origin

echo "3_1"
convert_level_asset 3_1 easton $common_tileset_origin

echo "3_2"
convert_level_asset 3_2 easton $common_tileset_origin

echo "3_3"
convert_level_asset 3_3 easton $common_tileset_origin

echo "4_1"
convert_level_asset 4_1 chai $common_tileset_origin

echo "4_2"
convert_level_asset 4_2 chai $common_tileset_origin

echo "4_3"
convert_level_asset 4_3 chai $common_tileset_origin

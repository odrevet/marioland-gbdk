get_define_value() {
  grep "#define $1" "$2" | awk '{print $3}'
}

tile_origin=0

echo "mario sprites"
png2asset "assets/sprites/mario.png" -o "src/graphics/mario.c" -sw 16 -sh 16 -spr8x8 -keep_palette_order -tile_origin $tile_origin -b 255
tile_origin=$((tile_origin + $(get_define_value mario_TILE_COUNT "src/graphics/mario.h")))

echo "enemies sprites"
png2asset "assets/sprites/enemies.png" -o "src/graphics/enemies.c" -sw 8 -sh 16 -spr8x8 -keep_palette_order -tile_origin $tile_origin -b 255
tile_origin=$((tile_origin + $(get_define_value enemies_TILE_COUNT "src/graphics/enemies.h")))

echo "common sprites"
png2asset "assets/sprites/common.png" -o "src/graphics/sprite_common.c" -sw 8 -sh 8 -spr8x8 -keep_palette_order -tile_origin $tile_origin -b 255
tile_origin=$((tile_origin + $(get_define_value sprite_common_TILE_COUNT "src/graphics/sprite_common.h")))

echo "enemies sprites large"
png2asset "assets/sprites/enemies_large.png" -o "src/graphics/enemies_large.c" -sw 16 -sh 16 -spr8x8 -keep_palette_order -tile_origin $tile_origin -b 255
tile_origin=$((tile_origin + $(get_define_value enemies_large_TILE_COUNT "src/graphics/enemies_large.h")))


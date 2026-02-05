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

echo "enemies sprites large birabuto"
png2asset "assets/sprites/enemies_large_birabuto.png" -o "src/graphics/enemies_large_birabuto.c" -sw 16 -sh 16 -spr8x8 -keep_palette_order -tile_origin $tile_origin -b 255

echo "enemies sprites large muda"
png2asset "assets/sprites/enemies_large_muda.png" -o "src/graphics/enemies_large_muda.c" -sw 16 -sh 16 -spr8x8 -keep_palette_order -tile_origin $tile_origin -b 255

echo "enemies sprites large easton"
png2asset "assets/sprites/enemies_large_easton.png" -o "src/graphics/enemies_large_easton.c" -sw 16 -sh 16 -spr8x8 -keep_palette_order -tile_origin $tile_origin -b 255

echo "enemies sprites large chai"
png2asset "assets/sprites/enemies_large_chai.png" -o "src/graphics/enemies_large_chai.c" -sw 16 -sh 16 -spr8x8 -keep_palette_order -tile_origin $tile_origin -b 255

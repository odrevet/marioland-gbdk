get_define_value() {
  grep "#define $1" "$2" | awk '{print $3}'
}

output_dir="level_maps"

convert_level_asset() {
  local level_number=$1
  local page=$2
  local source_tileset=$3
  local tile_origin=$4
  local bank=$5
  
  png2asset "assets/levels/pages/${level_number}_${page}.png" \
    -o "$output_dir/level_${level_number}_${page}.c" \
    -source_tileset "assets/tilesets/common.png" \
    -source_tileset "assets/tilesets/${source_tileset}.png" \
    -map -noflip -keep_duplicate_tiles \
    -tile_origin "$tile_origin" -b $bank
}

# background
tile_origin=0

echo "text background"
png2asset "assets/text.png" -o "src/graphics/text.c" -keep_palette_order -map -tiles_only -noflip -b 255
tile_origin=$((tile_origin + $(get_define_value text_TILE_COUNT "src/graphics/text.h")))

echo "1_1"
for i in {0..6}; do
  convert_level_asset 1_1 $(printf "%02d" $i) birabuto $tile_origin 255
done

echo "1_2"
for i in {0..6}; do
  convert_level_asset 1_2 $(printf "%02d" $i) birabuto $tile_origin 255
done

echo "1_3"
for i in {0..10}; do
  convert_level_asset 1_3 $(printf "%02d" $i) birabuto $tile_origin 255
done

echo "2_1"
for i in {0..7}; do
  convert_level_asset 2_1 $(printf "%02d" $i) muda $tile_origin 255
done

echo "2_2"
for i in {0..7}; do
  convert_level_asset 2_2 $(printf "%02d" $i) muda $tile_origin 255
done

echo "2_3"
for i in {0..5}; do
  convert_level_asset 2_3 $(printf "%02d" $i) muda $tile_origin 255
done

echo "3_1"
for i in {0..11}; do
  convert_level_asset 3_1 $(printf "%02d" $i) easton $tile_origin 255
done

echo "3_2"
for i in {0..10}; do
  convert_level_asset 3_2 $(printf "%02d" $i) easton $tile_origin 255
done

echo "3_3"
for i in {0..8}; do
  convert_level_asset 3_3 $(printf "%02d" $i) easton $tile_origin 255
done

echo "4_1"
for i in {0..9}; do
  convert_level_asset 4_1 $(printf "%02d" $i) chai $tile_origin 255
done

echo "4_2"
for i in {0..11}; do
  convert_level_asset 4_2 $(printf "%02d" $i) chai $tile_origin 255
done

echo "4_3"
for i in {0..9}; do
  convert_level_asset 4_3 $(printf "%02d" $i) chai $tile_origin 255
done

echo "gates"
png2asset "assets/levels/pages/gates.png" \
  -o "$output_dir/level_gates.c" \
  -source_tileset "assets/tilesets/common.png" \
  -map -noflip -keep_duplicate_tiles \
  -tile_origin "$tile_origin" -b 255

echo "stage_end"
png2asset "assets/levels/pages/stage_end.png" \
  -o "$output_dir/stage_end.c" \
  -source_tileset "assets/tilesets/common.png" \
  -map -noflip -keep_duplicate_tiles \
  -tile_origin "$tile_origin" -b 255

echo "undergrounds"
for i in {0..9}; do
echo "underground ${i}"
png2asset "assets/levels/pages/underground_${i}.png" \
  -o "$output_dir/underground_${i}.c" \
  -source_tileset "assets/tilesets/common.png" \
  -map -noflip -keep_duplicate_tiles \
  -tile_origin "$tile_origin" -b 255
done

echo "common background"
png2asset "assets/tilesets/common.png" -o "src/graphics/common.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $tile_origin

common_tiles_count=$(get_define_value common_TILE_COUNT "src/graphics/common.h")
level_tiles_origin=$(($tile_origin + $common_tiles_count))

png2asset "assets/tilesets/birabuto.png" -o "src/graphics/birabuto.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $level_tiles_origin
png2asset "assets/tilesets/birabuto_torch.png" -o "src/graphics/birabuto_torch.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $level_tiles_origin
png2asset "assets/tilesets/muda.png" -o "src/graphics/muda.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $level_tiles_origin
png2asset "assets/tilesets/easton.png" -o "src/graphics/easton.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $level_tiles_origin
png2asset "assets/tilesets/chai.png" -o "src/graphics/chai.c" -map -tiles_only -noflip -keep_duplicate_tiles -b 255 -tile_origin $level_tiles_origin

echo "title screen"
png2asset "assets/title.png" -o "src/graphics/title.c" -map -noflip -b 255 -tile_origin $level_tiles_origin

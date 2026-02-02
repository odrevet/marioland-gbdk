input_dir='level_maps'
output_dir='level_maps_compressed'

compress_level() {
  local level_number=$1
  local page=$2
  local bank=$3

  gbcompress --cin --cout \
    --varname="level_${level_number}_${page}" \
    --bank=$bank \
    "$input_dir/level_${level_number}_${page}.c" \
    "$output_dir/level_${level_number}_${page}.c"
}

echo "1_1"
for i in {0..6}; do
  compress_level 1_1 $(printf "%02d" $i) 255
done

echo "1_2"
for i in {0..6}; do
  compress_level 1_2 $(printf "%02d" $i) 255
done

echo "1_3"
for i in {0..10}; do
  compress_level 1_3 $(printf "%02d" $i) 255
done

echo "2_1"
for i in {0..7}; do
  compress_level 2_1 $(printf "%02d" $i) 255
done

echo "2_2"
for i in {0..7}; do
  compress_level 2_2 $(printf "%02d" $i) 255
done

echo "2_3"
for i in {0..5}; do
  compress_level 2_3 $(printf "%02d" $i) 255
done

echo "3_1"
for i in {0..11}; do
  compress_level 3_1 $(printf "%02d" $i) 255
done

echo "3_2"
for i in {0..10}; do
  compress_level 3_2 $(printf "%02d" $i) 255
done

echo "3_3"
for i in {0..8}; do
  compress_level 3_3 $(printf "%02d" $i) 255
done

echo "4_1"
for i in {0..9}; do
  compress_level 4_1 $(printf "%02d" $i) 255
done

echo "4_2"
for i in {0..11}; do
  compress_level 4_2 $(printf "%02d" $i) 255
done

echo "4_3"
for i in {0..9}; do
  compress_level 4_3 $(printf "%02d" $i) 255
done

gbcompress --cin --cout --varname="level_gates" --bank=255 "$input_dir/level_gates.c" "$output_dir/level_gates.c"

gbcompress --cin --cout --varname="stage_end" --bank=255 "$input_dir/stage_end.c" "$output_dir/stage_end.c"

for i in {0..9}; do
  gbcompress --cin --cout --varname="underground_${i}" --bank=255 "$input_dir/underground_${i}.c" "$output_dir/underground_${i}.c"
done

# correct level map name by adding _map
find level_maps_compressed -type f \( -name "*.h" -o -name "*.c" \) -exec sed -i 's/\[\]/_map[]/g' {} +
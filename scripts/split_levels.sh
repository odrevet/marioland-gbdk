mkdir -p assets/levels/pages

for file in assets/levels/*.png; do
  basename="${file##*/}"
  convert "$file" +repage -crop 160x0 +repage "assets/levels/pages/${basename%.png}_%02d.png"
done

fdupes -rN assets/levels/pages

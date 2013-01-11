#!/bin/sh

echo "<html><head></head><body>" > index.html

for svg in *.svg
do
 	echo "<object type=\"image/svg+xml\" data=\"${svg}\"></object>" >> index.html
done

echo "</body></html>" >> index.html

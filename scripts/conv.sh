#/bin/bash

# This scripts convers sources files in bsp folder from GB2312 encoding
# to UTF-8

script_dir=$(realpath $(dirname $0))
working_dir=$(realpath $script_dir/../CH573)

source=$(find $working_dir -name "*.[ch]")
echo Conver From GB 2312 to UTF-8
for f in $source; do
  echo Convert $f
  iconv -f CSGB2312 -t UTF-8//TRANSLIT $f -o $f.converted
  rm -f $f.origin
  mv $f.converted $f
done

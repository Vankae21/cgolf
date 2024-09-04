#!/bin/bash

CC="gcc"

if [ "$1" == "win" ]; then
	CC="x86_64-w64-mingw32-gcc"
fi

SRC_DIR="src"
INCLUDE_DIR="$SRC_DIR/include"
OBJ_DIR="objects"
FLAGS="-Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Lsrc/sealapi/ -lsealapi"
OUT="golf"

mkdir -p $OBJ_DIR

for file in $SRC_DIR/*.c; do
	gcc -c $file -I $INCLUDE_DIR -o "$OBJ_DIR/$(basename $file .c).o" $FLAGS
done

$CC $OBJ_DIR/*.o -o $OUT $FLAGS

rm -r $OBJ_DIR

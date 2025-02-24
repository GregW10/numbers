#!/bin/bash

f="veggieFibonacci_1M.bin"

if ! [ -f $f ]; then
	exit 1
fi

shasum -a 512 -b $f > $f.sha512
touch -r $f $f.sha512

echo "Done SHA-ing."

xz -9 -T 4 $f
shasum -a 512 -b $f.xz > $f.xz.sha512
touch -r $f.xz $f.xz.sha512

echo "Done compressing."

s3cmd put -P --multipart-chunk-size-mb=1024 $f.sha512 $f.xz $f.xz.sha512 s3://veggiebucket/numbers/

echo "Done uploading."

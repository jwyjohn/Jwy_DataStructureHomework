#!/bin/bash

for fn in $(/usr/bin/find.exe . -type f)
do
	echo $fn
	sha256sum.exe $fn >> sha256sum.txt
done
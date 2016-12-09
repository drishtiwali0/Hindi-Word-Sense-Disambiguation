#!/bin/sh

#DESCRIPTION: Replacing all white spaces with newlines and reduces multiple blank lines to one. Hence, output file wil have each word on a new line.

echo "Processing file $1\nPlease wait..."
#root=~/../corpus/
out=lined_$1

tr '\t' '\n' < $1 | tr ' ' '\n' | sed -e '/^$/d' > $out

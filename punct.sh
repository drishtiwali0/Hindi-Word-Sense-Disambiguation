#!/bin/sh

in=$1
out=filt_$1

sed 's/[।[:punct:]]*//g' < $in > $out

#awk 'FNR==NR{for(i=1;i<=NF;i++)w[$i];print $i;next}(!($1 in w))' awkIn en_sample.txt

#!/bin/sh

#This is for removing all but hindi words and spaces in a text file

root=../resources/
in=hin_uni.txt
out=fil$in

sed 's/[0-9a-zA-Z[:punct:]]*//g' < $root$in |\
tr '\r' ' '| tr '\t' ' ' | tr '\n' ' ' |\
sed 's/   */ /g'>$out

#!/bin/sh

#For finding occurrences of a word in a corpus, akong with the surrounding words

#Requires input file to contain each word on a new line.
#(Use wordliner.sh script to perform this^)
#Outputs a +-12 neighbourhood of each occurence of an input word. 
#Use as: ./findword.sh <WORD>
#Output stored in out.txt file

echo "Now finding word $1 in text file\nPlease wait.."
file=$2
out=found_$file

grep -w -A 6 -B 6 $1 - < $file | sed "s/$1[^ ]/NONE/g" |  sed "s/[^ ]$1/NONE/g" | tr '\n' ' ' | sed 's/--/\n/g' | grep -v NONE > $out

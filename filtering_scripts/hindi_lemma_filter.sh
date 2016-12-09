#!/bin/sh

#This filter is used to remove all but the lemma forms of hindi
#words in the HindMonoCorp export file

#The stepwise process is:
#1. Removing hyphens for hyphen-separated words, and hindi fullstops
#2. Only keeping lemmas
#3. Removing alphanumeric and punctuations
#4. Replacing 2 or more spaces with a single space

read in
echo "Now filtering file $in \nPlease wait..."
out=fil$in

sed -e 's/[-।]//g' \
-e 's/[^0-9a-zA-Z[:blank:][:punct:]]*|//g' \
-e 's/[0-9a-zA-Z[:punct:]]*//g' \
< $in | \
tr '\n' ' '| \
sed 's/   */ /g'>$out

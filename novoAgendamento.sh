#!/bin/bash

data=$( date +%Y-%m-%d )

awk -F ":" '{ OFS = ":" } { print $2, $1, $4 }' cidadaos.txt > tmp.txt 



while read line; do
  localCid=$( echo "$line" | grep -o -E "([A-Za-z])+$" )
  enfData=$( grep '1$' enfermeiros.txt | grep -i "$localCid" | awk -F ":" '{ OFS = ":"} { print $2, $1, $3 }' )
  #echo "$localCid"
  #echo "$enfData"
  echo "$enfData:$line:$data" | sed -e "s/CS$localCid:// ; s/$localCid/CS$localCid/"
done < tmp.txt

nrLines=$( wc -l tmp.txt ) #para saber quantas linhas ficaram

while read line; do
  if[[ ! $line =~ "^:" ]]; then
    echo "$line"
    echo "$line" >> tmp.txt
  done 

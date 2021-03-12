#!/bin/bash


verifDisp() {

  if grep -q '1$' enfermeiros.txt; then
   true 
  else
    false
  fi

}

if verifDisp true; then

  data=$( date +%Y-%m-%d )

  awk -F ":" '{ OFS = ":" } { print $2, $1, $4 }' cidadaos.txt > tmp.txt 

  IFS=$'\n'

  while read line; do
    localCid=$( echo "$line" | grep -o -E "([A-Za-z])+$" )
    enfData=$( grep '1$' enfermeiros.txt | grep -i "$localCid" | awk -F ":" '{ OFS = ":"} { print $2, $1, $3 }' )
    echo "$enfData:$line:$data" | sed -e "s/CS$localCid:// ; s/$localCid/CS$localCid/" >> tmp2.txt
  done < tmp.txt


  nrLines=$( cat tmp.txt | wc -l ) #para saber quantas linhas ficaram depois de escrever para o tmp2.txt

  while read line; do
    if [[ ! $line =~ ^: ]]; then
      echo "$line" >> tmp.txt
    fi 
  done < tmp2.txt

  tail -n +$(( $nrLines + 1 )) tmp.txt > agendamento.txt
  rm tmp2.txt tmp.txt
  exit 0

else
  echo "não existem enfermeiros disponíveis!"
  echo "sem vacinações hoje!" > agendamento.txt
  exit 1
fi


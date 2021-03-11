#!/bin/bash

###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos
##
## Aluno: Nº:       Nome: 
## Nome do Módulo: agendamento.sh
## Descrição/Explicação do Módulo: 
##
##
###############################################################################

#ordenar cidadãos por localidade
#verificar que enfermeiros estão disponíveis
#corresponder a cada cidadão o enfermeiro da zona respectiva

declare -a enfData #inicializa array enfData para guardar dados pertinentes dos enfermeiros
declare -a cidData #inicializa array cidData para guardar dados pertinentes dos cidadãos


verifDisp() {

  if grep -q '1$' enfermeiros.txt; then
   true 
  else
    false
  fi

}


getEnfData() {
  
  grep '1$' enfermeiros.txt | awk -F ":" ' { OFS = ":" } { print $2, $1, $3 }' > tmp.txt

  i=0
  
  IFS=$'\n'

  while read line; do
    enfData+=("$line")
    #echo "${enfData[$i]}"
    i=$(( $i + 1 ))
  done < tmp.txt

  rm tmp.txt
    
}

#teste para função getEnfData
#getEnfData
#echo "${#enfData[@]}"


getCidData() {
  
 awk -F ":" '{ OFS = ":" } { print $2, $1, $4 }' cidadaos.txt > tmp.txt 

  i=0

  IFS=$'\n'

  while read line; do
    cidData+=("$line")
    #echo "${cidData[$i]}"
  done < tmp.txt

  rm tmp.txt
    
}

#teste para função getCidData
#getCidData
#echo "${#cidData[@]}"

getEnfData
getCidData

nrCid="${#cidData[@]}"
nrEnf="${#enfData[@]}"
matchRawData() {
  for (( i=0; i < $nrCid; i++ )); do
    for (( j=0; j < $nrEnf ;j++)); do

      cidLocal=$( echo "${cidData[$i]}" | cut -d ':' -f3 )
      enfLocal=$( echo "${enfData[$j]}" | cut -d ':' -f3 | sed 's/CS//g' )

      if [ $cidLocal = $enfLocal ]; then
        echo "${enfData[$j]}:${cidData[$i]}"
      fi
    done
  done
}
#cidLocal=$( echo "${cidData[0]}" | cut -d ':' -f3  )
#echo "${cidData[0]}"
#echo "$cidLocal"
#echo "$nrEnf"
#echo "$nrCid"

    










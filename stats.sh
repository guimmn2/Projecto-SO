#!/bin/bash

###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos
##
## Aluno: Nº:       Nome: 
## Nome do Módulo: stats.sh
## Descrição/Explicação do Módulo: 
##
##
###############################################################################


nrCidadaos=$( grep -i "$1" 'cidadaos.txt' | wc -l )

if [[ $1 == 'enfermeiros' ]]; then
  grep '1$' enfermeiros.txt | awk -F ':' '{ print $2 }'

elif [[ $1 == 'registados' ]]; then
  awk -F ':' '{ print $1, $2, $3 }' cidadaos.txt | grep "[6-9][0-9]$" | sort -k 4 -n -r

elif [ -z $1 ]; then
  echo "ERRO! campos possíveis: enfermeiros; registados ou <localidade>"
  exit 1

elif grep -w -q -i "$1" cidadaos.txt; then 
  echo "O número de cidadãos registados em $1 é $nrCidadaos"  #aqui a localização aparece na msg como a pessoa a escreve (não sei formatar)
else
  echo "não existem enfermeiros nesta localidade"
  exit 1
fi


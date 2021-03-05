#!/bin/bash

###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos
##
## Aluno: Nº:       Nome: 
## Nome do Módulo: adiciona_enfermeiros.sh
## Descrição/Explicação do Módulo: 
##
##
###############################################################################

if [ $# -gt 4 ]; then
  echo "tem argumentos a mais!"
  echo "SYNTAX ERROR: [nome = <nome> <apelido>] [nº de cédula = xxxxx] [Centro de Saúde = CS<localidade>] [disponibilidade = 0 ou 1]"
  exit 1
fi


if [[ $(echo "$2" | wc -c) != 6 ]]; then
  echo "nº de utente inválido, deve ter exactamente 5 dígitos"
  echo "SYNTAX ERROR: [nome = <nome> <apelido>] [nº de cédula = xxxxx] [Centro de Saúde = CS<localidade>] [disponibilidade = 0 ou 1]"
  exit 1
fi

if [[ ! $( echo "$3" | grep "^CS" ) ]]; then
   echo "SYNTAX ERROR: [nome = <nome> <apelido>] [nº de cédula = xxxxx] [Centro de Saúde = CS<localidade>] [disponibilidade = 0 ou 1]"
  exit 1
fi

case $4 in
    [^01]) echo "disponibilidade tem de ser 0 ou 1"
  exit 1
esac

echo "$1:$2:$3:$4"


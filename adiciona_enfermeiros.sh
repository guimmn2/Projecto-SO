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


syntax="<'Nome Apelido'> <'nº de cédula (5 digitos)> <'CS[localidade]> <disponibilidade (0 ou 1)>"


#verifica o 'field':disponibilidade
if [[ ! $4 =~ [0-1] ]]; then
  echo "SYNTAX ERROR: $syntax"
  exit 1
#verifica o 'field':CSlocalidade
elif [[ ! $3 =~ ^CS ]]; then
  echo "SYNTAX ERROR: $syntax"
  exit 1
#verifica o 'field':cédula
elif [[ ! $2 =~ [0-9][0-9][0-9][0-9][0-9] ]]; then
  echo "SYNTAX ERROR: $syntax"
  exit 1
#verifica o 'field':nome
elif [[ ! $1 =~ ^[A-Za-z]+( [A-Za-z]+)*$ ]]; then
  echo "nome inválido !" 
  echo "SYNTAX ERROR: $syntax"
  exit 1
fi


echo $1:$2:$3:$4 








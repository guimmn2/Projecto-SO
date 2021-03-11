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


verifDisp() {

  if grep -q '1$' enfermeiros.txt; then
   true 
  else
    false
  fi

}

#if verifDisp true ; then
#  echo 'existem!'
#else
#  echo 'n existem'
#fi

#cria array com dados pertinentes dos enfermeiros

declare -a dados 

getEnfData() {

  i=0

  while read line; do
    dados+=("$line")
    echo "este é o $iº enfermeiro -->   "${dados[$i]}""
    i=$(( $i + 1 ))
  done < enfermeiros.txt

}

getEnfData











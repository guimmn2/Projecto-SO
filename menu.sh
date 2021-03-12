#!/bin/bash

###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos
##
## Aluno: Nº:       Nome: 
## Nome do Módulo: menu.sh
## Descrição/Explicação do Módulo: 
##
##
###############################################################################

flag=0

menu() {

  echo "1. Listar Cidadãos
2. Adicionar enfermeiro
3. Stats
4. Agendar vacinação
0. Sair"

  read option

if [ $option = 1 ]; then
  ./lista_cidadaos.sh

elif [ $option = 2 ]; then
  echo "introduza o nome e apelido"
  read nome
  echo "introduza o nº de cédula"
  read ced
  echo "introduza a localidade começada por CS, como no exemplo: CSAlentejo"
  read loc
  echo "introduza a disponibilidade"
  read disp
  ./adiciona_enfermeiros.sh "$nome" $ced $loc $disp

elif [ $option = 3 ]; then
  echo "introduza opção, escreva:
  enfermeiros - obtem nº de enfermeiros disponíveis
  registados - obtem informação acerca de cidadãos com idade superior a 60 anos
  <localidade> (ex: Lisboa, Porto, etc) - obtem informação acerca do nº de cidadãos registados em <localidade>"
  read dados
  echo $'\n'
  ./stats.sh "$dados"
  echo $'\n'

elif [ $option = 4 ]; then
  ./agendamento.sh

elif [ $option = 0 ]; then
  flag=1
fi
}

until [ $flag = 1 ]; do
  menu
done




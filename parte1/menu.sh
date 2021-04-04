#!/bin/bash

###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos
##
## Aluno: Nº:98662       Nome:Guilherme Nunes 
## Nome do Módulo: menu.sh
## Descrição/Explicação do Módulo: 
##
##
###############################################################################


flag=0 #variável para controlar duração do while, enquanto estiver a 0 o while funciona

menu() {

    #mostra a lista de opções
echo "1. Listar Cidadãos
2. Adicionar enfermeiro
3. Stats
4. Agendar vacinação
0. Sair"

    #lê opção seleccionada pelo cliente
    read option

    #echo $'\n' serve para escrever um espaço no terminal antes e depois do output do respectivo script para facilitar legibilidade
  if [ $option = 1 ]; then
    echo $'\n'
    ./lista_cidadaos.sh
    echo $'\n'

  #recebe todos os dados (read) sequencialmente e aplica-os ao script adiciona_enfermeiros.sh
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

  #recebe dados (read) e aplica-os ao script stats.sh
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
    echo $'\n'
    ./agendamento.sh
    echo $'\n'

  #levanta a flag de término, alterando o seu valor para 1
  elif [ $option = 0 ]; then
    flag=1
  else
    echo $'\n'
    echo "opção inválida!" #se for introduzido qualquer outro input que não esteja entre [0-4] devolve opção inválida
    echo $'\n'
  fi
}

#até que a flag seja igual a 1 a função menu (em cima) é invocada
until [ $flag = 1 ]; do
  menu
done



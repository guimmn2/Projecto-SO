#!/bin/bash

###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos
##
## Aluno: Nº:98662       Nome:Guilherme Nunes 
## Nome do Módulo: stats.sh
## Descrição/Explicação do Módulo: 
## 
##
###############################################################################


#se o input do cliente for enfermeiros então faz grep de todas as linhas terminadas em 1 ('1$') e, com o awk, mostra apenas a segunda coluna
#as linhas terminadas em 1 correspondem aos enfermeiros disponíveis e a coluna 2 ($2) aos nomes (sendo que são separados por ':' por causa de -F)

if [[ $1 == 'enfermeiros' ]]; then
  grep '1$' enfermeiros.txt | awk -F ':' '{ print $2 }'

#se o input do cliente for registados então awk obtem as primeirs três colunas separadas por ':' (-F ':'), 
#que correspondem ao id, nome e idade
#com o grep filtra as linhas em que encontra o nº 60 ou superior ([6-9][0-9]$, isto permite apenas 2 digitos, o primeiro entre 6-9, o outro [0-9])
#com o sort -k 4 escolhe a coluna das idades (colunas delimitadas por espaços), com o -n -r faz um sort numérico ascendente, -r torna descendente

elif [[ $1 == 'registados' ]]; then
  awk -F ':' '{ print $1, $2, $3 }' cidadaos.txt | grep "[6-9][0-9]$" | sort -k 4 -n -r

#se o input do cliente for nulo, devolve um erro e sai do script

elif [ -z $1 ]; then
  echo "ERRO! campos possíveis: enfermeiros; registados ou <localidade>"
  exit 1

#obtem o nº de cidadãos da localidade colocada pelo user em $1 , ou seja na primeira coluna
#a partir do uso do grep com as flags -w e -i obtem apenas as palavras inteiras ignorando o 'case', respectivamente.

nrCidadaos=$( grep -w -i "$1" 'cidadaos.txt' | wc -l )

#se o input do cliente for uma localidade, ou seja um string que não seja 'enfermeiros' ou 'registados'
#o grep procura a palavra inteira, ignorando case e suprimindo o output (-w, -i, -q respectivamente) em cidadaos.txt
#se o grep encontrar a localidade devolve a variável nrCidadaos, que contem o nº de linhas que o grep filtrou
#caso contrário nenhum enfermeiro se existe registado na localidade em questão, devolve a mensagem conforme

elif grep -w -q -i "$1" cidadaos.txt; then 
  echo "O número de cidadãos registados em $1 é $nrCidadaos"  #aqui a localização aparece na msg como a pessoa a escreve (não sei formatar)
else
  echo "não existem enfermeiros nesta localidade"
  exit 1
fi


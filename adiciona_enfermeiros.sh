#!/bin/bash

###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos
##
## Aluno: Nº:       Nome: 
## Nome do Módulo: adiciona_enfermeiros.sh
## Descrição/Explicação do Módulo: 
## 
##   Para este script acabei por usar uma abordagem talvez não muito elegante.
##   Decidi criar uma espécie de cadeia condicional (com if e elifs) que serve como um conjunto de "failsafes"
##   para verificar a integridade do input do user, ou seja se não tem erros de sintaxe, e também para verificar
##   se o enfermeiro já existe ou se a localidade já tem um enfermeiro designado.
##   Se tiver erros de sintax mostra a sintaxe de forma a que o cliente possa comparar com o seu 'input'.
##   Fiz isto usando, como já aludi, essencialmente, 'if statements' e expressões regulares.
##   A explicação mais detalhada encontra-se nos comentários ao longo do script.
##
###############################################################################


##Mensagem de erro que é mostrada caso haja problemas com o input do cliente.
syntax="<'Nome Apelido'> <'nº de cédula (5 digitos)> <'CS[localidade]> <disponibilidade (0 ou 1)>"

ficheiro='enfermeiros.txt'

#Para facilitar a legibilidade do script declarei estas variáveis.
nome=$1
id=$2
loc=$3
disp=$4


#verifica se não existe ficheiro enfermeiros.txt usando a flag -f e o shebang '!' antes, se não existir cria-o.
if [ ! -f $ficheiro ]; then
  touch $ficheiro
fi

## Nas seguintes condições o usdo duplo de [] serve para conseguir usar o operador =~ 
## de forma a que as condições if e elif consigam interpretar expressões regulares

#verifica o 'field':disponibilidade usando a 'regex' [0-1] 
#se o que for inserido não for um inteiro ou, sendo inteiro, não se encontrar entre 0-1 devole erro.
if [[ ! $disp =~ [0-1] ]]; then
  echo "SYNTAX ERROR: $syntax"
  exit 1

#verifica o 'field':CSlocalidade usando a 'regex' ^CS
#se o que for inserido não começar por CS (^CS) 
#e não for apenas um 'string' constituido por um ou mais (+) caracteres alfabéticos até ao fim [A-Za-z]+$ devolve erro.
elif [[ ! $loc =~ ^CS[A-Za-z]+$ ]]; then
  echo "SYNTAX ERROR: $syntax"
  exit 1

#verifica o 'field':cédula:
#se o input for constituido por mais do que 5 digitos {5} (que têm de estar entre [0-9]) devolve erro.

elif [[ ! $id =~ ^[0-9]{5}$ ]]; then
  echo "SYNTAX ERROR: $syntax"
  exit 1


#verifica o 'field':nome.
#se os diferentes strings do input não forem constituidos por caracteres alfabéticos devolve erro.
#^[A-Za-z] garante que o início (primeiro string) tem que ser constituido apenas por caracteres alfabéticos.
#+( [A-Za-z]+)*$ garante que pode ser adicionado mais 1 ou mais strings (+) constituidos apenas por caracteres alfabéticos ([A-Za-z]),
# o que tem de ser assim até ao fim *$ não admitindo quaisquer outros caracteres.
# O espaço antes do [A-Za-z], dentro dos parentesis, garante que se podem adicionar nomes dentro de plicas separados por espaços.

elif [[ ! $nome =~ ^[A-Za-z]+( [A-Za-z]+)*$ ]]; then
  echo "SYNTAX ERROR: $syntax"
  exit 1


#verifica se já existe enfermeiro pelo nº da cédula.
#procura com o comando grep a cédula no ficheiro enfermeiros.txt, 
#se o encontrar é porque o enfermeiro já está registado.

elif grep '$id' $ficheiro ; then
  echo "enfermeiro já se encontra registado!"
  echo "SYNTAX ERROR: $syntax"
  exit 1


#verifica se já existe enfermeiro em dada localidade.
#procura com o comando grep -i (para ignorar o case) a localidade no ficheiro enfermeiros.txt, 
#se o encontrar é porque já existe um enfermeiro registado na localidade.

elif grep -i '$loc' $ficheiro; then
  echo "localidade já tem enfermeiro registado!"
  echo "SYNTAX ERROR: $syntax"
  exit 1
fi


#finalmente, se nenhum dos failsafes anteriores for activado o enfermeiro é registado com sucesso
#fazendo echo do input com o formato correcto para o ficheiro enfermeiros.txt

echo $id:$nome:$loc:0:$disp >> $ficheiro

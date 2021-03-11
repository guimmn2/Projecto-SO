#!/bin/bash

###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos
##
## Aluno: Nº:       Nome: 
## Nome do Módulo: agendamento.sh
## Descrição/Explicação do Módulo: 
##  
##  Neste script criei 3 funções. A primeira e mais importante é a verifDisp que verifica se existe sequer algum enfermeiro disponível.
##  A segunda e a terceira são idênticas. Servem para guardar num array as informações importantes dos enfermeiros e cidadãos.
##  Para finalizar a parte de criar o ficheiro não é uma função, mas está contingente na existência de enfermeiros. Se existirem enfermeiros
##  então as duas funções são chamadas e é criado a partir dos arrays um output bem formatado, que é redireccionado para o ficheiro agendamento.txt.
##  Caso contrário, as funções de informação não são chamadas, o script dá erro, pois não existem enfermeiros disponíveis.
##  
##  Os pormenores técnicos podem ser encontrados ao longo do código nos comentários (isto é, a explicação do funcionamento do script concretamente).
##
###############################################################################

#ordenar cidadãos por localidade
#verificar que enfermeiros estão disponíveis
#corresponder a cada cidadão o enfermeiro da zona respectiva

declare -a enfData #inicializa array enfData para guardar dados pertinentes dos enfermeiros
declare -a cidData #inicializa array cidData para guardar dados pertinentes dos cidadãos


#usando um grep com o flag -q para suprimir o output
#verifica se existe alguma linha terminada em 1 (se algum enfermeiro está disponível) 
#retorna true ou false conforme encontra ou não algum enfermeiro

verifDisp() {

  if grep -q '1$' enfermeiros.txt; then
   true 
  else
    false
  fi

}


#com o uso do grep e awk obtem as informações importantes (id, nome e localidade) dos enfermeiros disponíveis
#OFS = ":" garante output separado por ":"

getEnfData() {
  
  grep '1$' enfermeiros.txt | awk -F ":" ' { OFS = ":" } { print $2, $1, $3 }' > tmp.txt

  i=0
  
  #define do delimitador do read como um newline '\n', de forma a que leia linha a linha o ficheiro
  IFS=$'\n'

  #lê o ficheiro tmp.txt linha a linha e carrega as informações para o array enfData
  while read line; do
    enfData+=("$line")
    i=$(( $i + 1 ))
  done < tmp.txt

  #remove o ficheiro tmp.txt que serviu apenas para facilitar o armazenamento de informação no array
  rm tmp.txt
    
}

#esta função é idêntica à anterior, mas aplicada ao ficheiro cidadaos.txt
#obtem o id nome e localidade

getCidData() {
  
 awk -F ":" '{ OFS = ":" } { print $2, $1, $4 }' cidadaos.txt > tmp.txt 

  i=0

  IFS=$'\n'

  while read line; do
    cidData+=("$line")
  done < tmp.txt

  rm tmp.txt
    
}


#funções só são usadas se houver pelo menos 1 enfermeiro disponível
#se não houver nenhum enfermeiro disponível não vale a pena preencher os arrays com os dados, pois nenhuma vacinação será agendada

if verifDisp true; then 

getEnfData                  #invocação das funções para preencher os arrays devidamente
getCidData      

nrCid="${#cidData[@]}"      #nr de cidadãos retirado do length do array cidData
nrEnf="${#enfData[@]}"      #nr de enfermeiros disponiveis retirado do length do array enfData
data=$(date +%y-%m-%d)      #guarda a data 

  for (( i=0; i < $nrCid; i++ )); do      #a cada cidadão no array cidData
    for (( j=0; j < $nrEnf ;j++)); do     #por cada cidadão verifica o array enfData

      cidLocal=$( echo "${cidData[$i]}" | cut -d ':' -f3 )                      #para obter a localização de cada cidadadão (na 3ª coluna por ':')
      enfLocal=$( echo "${enfData[$j]}" | cut -d ':' -f3 | sed 's/CS//g' )      #para obter a localização de cada enfermeiro (na 3ª coluna por ':')
                                                                                #retira o CS com sed para comparar facilmente as localidades

      if [ $cidLocal = $enfLocal ]; then      #se as localidades forem iguais junta com o formato certo o cidadão com o enfermeiro respectivo      

        #echo + awk para formatar correctamente output para um ficheiro temporário
        #"CS"$6 adiciona o CS à localidade e o sed -e permite regex adiciona no fim ($) a variável $data
        #OFS = ":" garante output separado por ":"

        echo "${enfData[$j]}:${cidData[$i]}" | awk -F ":" '{ OFS = ":" } { print $1, $2, $4, $5, "CS"$6 }' | sed -e "s/$/:$data/g" >> tmp.txt

      fi
    done
  done
cat tmp.txt > agendamento.txt       #copia o conteudo de tmp.txt para agendamento.txt, escrevendo por cima
rm tmp.txt                          
else
  echo "nenhum enfermeiro disponível!"
  echo "sem vacinas hoje!" > agendamento.txt
  exit 1
fi

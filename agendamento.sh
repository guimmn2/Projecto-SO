#!/bin/bash

###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos
##
## Aluno: Nº:98662       Nome:Guilherme Nunes 
## Nome do Módulo: stats.sh
## Descrição/Explicação do Módulo: O script possui uma função da qual depende a eventual execução do script chamada verifDisp()
## esta função verifica se existem enfermeiros disponíveis. Se existirem o 'corpo' do script é executado, caso contrário não.
## O funcionamento do 'corpo' do script encontra-se explicado ao longo do mesmo por meio de comentários
##
###############################################################################


verifDisp() {

  if grep -q '1$' enfermeiros.txt; then
   true 
  else
    false
  fi

}

if verifDisp true; then

  data=$( date +%Y-%m-%d ) #obtem a data bem formatada ANO-MÊS-DIA

  awk -F ":" '{ OFS = ":" } { print $2, $1, $4 }' cidadaos.txt > tmp.txt #coloca, separado por ':' as colunas nome, id e localidade (por ordem)
                                                                         #num ficheiro temporário de texto
  IFS=$'\n' #faz com que o read leia uma linha de cada vez (lê até \n = line feed)

  #lê cada linha do ficheiro tmp.txt que contém os dados carregados acima do ficheiro cidadaos.txt
  #obtem, por cada linha a localidade do cidadão fazendo grep do campo que tem apenas uma palavra ([A-Za-z])+$, ou seja a localidade
  #guarda a localidade em localCid
  #depois, obtem os dados pertinentes do enfermeiro que corresponde à localidade - se existir e estiver disponível
  #grep : 1$ verifica disp; -i "localCid" verifica localidade 
  #awk obtem os dados do nome, id e localidade ($2, $1, $3) e faz o output correctamente com OFS = ":" 
  #guarda os dados em enfData
  #por fim faz eco do enfData:$line(linha do cidadão formatada anteriormente no primeiro awk):data(de hoje)
  #com o sed formata o output devidamente retirando o CSLocalidade a mais e depois adicionando CS a localidade depois do cidadão
  #output final vai para ficheiro temporário 2 (tmp2.txt)
  while read line; do
    localCid=$( echo "$line" | grep -o -E "([A-Za-z])+$" )
    enfData=$( grep '1$' enfermeiros.txt | grep -i "$localCid" | awk -F ":" '{ OFS = ":"} { print $2, $1, $3 }' )
    echo "$enfData:$line:$data" | sed -e "s/CS$localCid:// ; s/$localCid/CS$localCid/" >> tmp2.txt
  done < tmp.txt


  nrLines=$( cat tmp.txt | wc -l ) #para saber quantas linhas ficaram depois de escrever para o tmp2.txt

  #da mesma forma que em cima lê cada linha, mas agora do 2º ficheiro temporário
  #ao ter reparado que a função de cima escrevia também os enfermeiros que não tinham cidadão correspondente começando com ':'
  #decidi aproveitar esse facto para eliminar essas mesmas linhas
  #Portanto, por cada linha, se começar por ':' não é gravada no ficheiro temporário tmp.txt, o qual usei para evitar criar um terceiro
  while read line; do
    if [[ ! $line =~ ^: ]]; then
      echo "$line" >> tmp.txt
    fi 
  done < tmp2.txt

  #como gravei o nº de linhas uso esse nº para saber, com o tail, a partir de que linha é que tenho em tmp.txt os dados pertinentes
  #os dados pertinentes são escritos, finalmente, em agendamento.txt e os ficheiros tmp são removidos
  tail -n +$(( $nrLines + 1 )) tmp.txt > agendamento.txt
  rm tmp2.txt tmp.txt
  echo "agendamento efectuado com sucesso!"
  exit 0

else
  echo "não existem enfermeiros disponíveis!"
  echo "sem vacinações hoje!" > agendamento.txt
  exit 1
fi


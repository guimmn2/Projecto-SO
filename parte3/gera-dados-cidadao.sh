#!/bin/bash
## Este script gera automaticamente um ficheiro "dados_cidadao.txt" com os dados de um cidadao aleatório existente no ficheiro cidadaos.dat
## O ficheiro depois pode ser usado como input do programa cidadao (e.g., ./cidadao < dados_cidadao.txt) para ter um cidadao existente como input
cidadao=$(./show-cidadaos.sh | shuf -n1)
num_utente=$(echo $cidadao | cut -d'|' -f2 | xargs)
nome=$(echo $cidadao | cut -d'|' -f3 | xargs)
printf "$num_utente\n$nome\n" > dados_cidadao.txt
#!/bin/bash

###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos
##
## Aluno: Nº:98662       Nome:Guilherme Nunes 
## Nome do Módulo: lista_cidadaos.sh
## Descrição/Explicação do Módulo: 
## 
##	 Para este módulo a solução que encontrei é 
##	 relativamente simples. Basta utilizar os programas awk e sed para obter as
##	 informações que desejamos e manipulá-las, respectivamente.
##
###############################################################################

awk -F '[:|-]' '{ OFS = " :"} { print (NR + 10000) , $2,(2021 - $6), $8, $10 }' listagem.txt

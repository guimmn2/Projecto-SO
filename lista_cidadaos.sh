#!/bin/bash

###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos
##
## Aluno: Nº:98662       Nome:Guilherme Nunes 
## Nome do Módulo: lista_cidadaos.sh
## Descrição/Explicação do Módulo:  
##
## Para este módulo a solução que encontrei foi usar uma combinação de AWK e Sed de forma a obter as informações
## relevantes e a manipular o seu output.
##
###############################################################################


# -F '[:|-]' estabelece os delimitadores, tal que a coluna $2 corresponde ao nome; a $8 à localidade e a $10 ao nº de telemóvel

# O comando OFS devolve-me o output com os campos separados por ":", mas tive que usar o sed para substituir o '<espaço>:' por apenas ":"

# sem o sed teria algo do género: <field> :<field1> ; com o sed fico com <field>:<field1>

# NR corresponde ao nº de linhas a qual foi só necessário somar 10000 e colocar na primeira coluna

# A idade foi calculada subtraíndo a 2021 o ano do nascimento da pessoa que corresponde à coluna $6

# O 0 corresponde à inicialização do status de vacinação a 0


awk -F '[:|-]' '{ OFS = ":"} { print (NR + 10000) , $2,(2021 - $6), $8, $10, 0 }' listagem.txt | sed 's/ :/:/g' > cidadaos.txt

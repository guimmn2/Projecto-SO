/******************************************************************************
 ** ISCTE-IUL: Trabalho prático de Sistemas Operativos
 **
 ** Aluno: Nº:       Nome: 
 ** Nome do Módulo: utils.h
 ** Descrição/Explicação do Módulo: 
 **     Definição de funções utilitárias genéricas
 **
 ******************************************************************************/
#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <string.h>

/**
 *  Impressão de mensagens de DEBUG incluindo o módulo e a linha de código. Para ativar, alterar DEBUG_MODE para 1
 */
#define DEBUG_MODE 1         // Se estiver a 1, apresentará mensagens de DEBUG

// Escreve uma mensagem de debug (parâmetros iguais ao printf) se DEBUG_MODE estiver a 1
#define debug(fmt, ...) do { if (DEBUG_MODE) fprintf(stderr, "@@DEBUG@@:%s:%d:%s(): " fmt "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__); } while (0)

/**
 *  Macros para leitura de Strings a partir de um ficheiro ou do STDIN
 */
// Leitura de uma string de um ficheiro, definindo um buffer size. Semelhante a fgets(), mas removendo o '\n'
#define my_fgets(buffer,size,file) ({ char *_result = fgets(buffer, size, file); if (NULL != _result) { if ('\n' == buffer[0]) _result = fgets(buffer, size, file); if ('\n' == buffer[strlen(buffer)-1]) buffer[strlen(buffer)-1] = 0; else while (getchar() != '\n') /* do nothing */; } _result; })
// Leitura de uma string do STDIN, definindo um buffer size.
#define my_gets(buffer,size) my_fgets(buffer, size, stdin)

#endif
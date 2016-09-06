/*
 *	TIPO ABSTRATO DE DADOS ARVORE DIGITAL
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas de uma arvore digital
 */

#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include "boolutils.h"

#define TAMANHO_ALFABETO 26

typedef struct _TArvoreDigitalNo* TArvoreDigitalNo;

struct _TArvoreDigitalNo {
	TArvoreDigitalNo* Alfabeto;		/* Nó da arvore digital */
	unsigned long Contador;			/* Contador da quantidade de palavras no texto */
	unsigned long Repeticao;		/* Contador da quantidade de palavras no dicionario */
	bool Prefixo;					/* Indica se o nó representa um prefixo ou uma palavra */
};

typedef struct _TArvoreDigital {
	TArvoreDigitalNo Raiz;			/* Guarda a raiz da árvore */
} TArvoreDigital;

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigitalNo_Criar
 * 				Cria um nó de arvore digital vazio
 * @param:		(vazio)
 * @retorna:	No
 *---------------------------------------------------------------------------*/
TArvoreDigitalNo TArvoreDigitalNo_Criar();

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigitalNo_Destruir
 * 				Destroi um nó de arvore digital
 * @param:		No da arvore
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TArvoreDigitalNo_Destruir(TArvoreDigitalNo* PArvoreDigitalNo);

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigitalNo_ExibirContador
 * 				Exibe o valor do contador armazenado no nó
 * @param:		No
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TArvoreDigitalNo_ExibirContador(TArvoreDigitalNo No);

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigital_Criar
 * 				Cria uma arvore digital vazia
 * @param:		(vazio)
 * @retorna:	Arvore
 *---------------------------------------------------------------------------*/ 
TArvoreDigital* TArvoreDigital_Criar();

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigital_Destruir
 * 				Destroi a arvore
 * @param:		Arvore
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreDigital_Destruir(TArvoreDigital** PArvore);

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigital_Adicionar
 * 				Adiciona uma palavra à árvore
 * @param:		Arvore e a palavra
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreDigital_Adicionar(TArvoreDigital* Arvore, char* Palavra);

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigital_CarregarArquivo
 * 				Carrega um dicionário armazenado em um arquivo
 * @param:		Arvore e o arquivo
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreDigital_CarregarArquivo(TArvoreDigital* Arvore, FILE* Arquivo);

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigital_CarregarString
 * 				Carrega um dicionário armazenda em uma string
 * @param:		Arvore e a string
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreDigital_CarregarString(TArvoreDigital* Arvore, char* Entrada);

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigital_CarregarTela
 * 				Carrega um dicionário informado na tela
 * @param:		Arvore e o arquivo
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/
void TArvoreDigital_CarregarTela(TArvoreDigital* Arvore);

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigital_ContarPalavrasArquivo
 * 				Conta as palavras da árvore que estão presente em um arquivo
 * @param:		Arvore e o arquivo
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreDigital_ContarPalavrasArquivo(TArvoreDigital* Arvore, FILE* Arquivo);

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigital_ContarPalavrasString
 * 				Conta as palavras da árvore que estão presente em uma string
 * @param:		Arvore e a string
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreDigital_ContarPalavrasString(TArvoreDigital* Arvore, char* Entrada);

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigital_ContarPalavrasTela
 * 				Conta as palavras da árvore que estão presente na tela
 * @param:		Arvore
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreDigital_ContarPalavrasTela(TArvoreDigital* Arvore);

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreDigital_ExibirContador
 * 				Exibe os contadores de cada palavra armazenada na árvore
 * @param:		Arvore
 * @retorna:	(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreDigital_ExibirContador(TArvoreDigital* Arvore);
#endif

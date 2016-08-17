/*
 *	ALGORITMOS DE CASAMENTO DE CADEIA DE CARACTERES
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas para casamento de cadeia de caracteres
 */

#ifndef CARACTERES_H
#define CARACTERES_H

/* tamanho maximo da tabela de caracteres ASCII */
#define MAXCHAR 256

unsigned long PesquisarCarac_ForcaBruta(char* Texto, unsigned long TamanhoTexto, char* Padrao, unsigned long TamanhoPadrao);

unsigned long PesquisarCarac_BMH(char* Texto, unsigned long TamanhoTexto, char* Padrao, unsigned long TamanhoPadrao);

unsigned long PesquisarCarac_BMHS(char* Texto, unsigned long TamanhoTexto, char* Padrao, unsigned long TamanhoPadrao);

#endif
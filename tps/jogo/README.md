# TP1 de AEDS1
Nome: Calabouço da Morte

Assunto: Programação em C

Linguagem: C

Bibliotecas necessárias: Allegro 5

Compilador: GCC

Ambiente: Windows

Disciplina: AEDS1

## ARQUIVO LEIAME DO JOGO

### Assuntos
1. Requisitos minimos para compilacao
2. Requisitos recomendados para compilacao
3. Requisitos minimos para execucao
4. Verificando seu sistema
5. Instalando o MingW-w64
5. Compilando o jogo
6. Configurando o jogo antes de executar
7. O instalador

### REQUISITOS MINIMOS PARA COMPILACAO
Para compilar o jogo com sucesso, eh necessario, pelo, menos:
* Microsoft Windows 7 64 bits ou superior.
* GCC 5.2.0 ou superior;
* MingW-w64 4.0.2 ou superior.
* Biblioteca Allegro Gaming 5.1.9 ou superior.

*ATENCAO:* O jogo nao eh compativel com o MingW original.
Para atualizar seu computador, consulte a secao "Instalando o MingW-w64".

### REQUISITOS RECOMENDADOS PARA COMPILACAO
Para compilar o jogo com sucesso, eh recomendavel ter as versoes
mais recentes das ferramentas de desenvolvimento.
* Microsoft Windows 8.1 64 bits ou superior;
* GCC 5.2.0 ou superior.
* MingW-w64 4.0.2 ou superior.
* Biblioteca Allegro Gaming 5.1.9 ou superior.
* InnoSetup 5.5.6 ou superior, para gerar o instalador.

### REQUISITOS MINIMOS PARA EXECUCAO
Para executar o jogo compilado, eh necessario:
* Microsoft Windows 7 64 bits ou superior.
* Mouse ou outro dispositivo apontador compativel.

### VERIFICANDO SEU SISTEMA
Para verificar se seu sistema possui os requisitos necessarios para compilar
e executar o jogo, digite o comando:

```
MAKE SYSINFO
```

Em alguns sistemas, o comando MAKE nao eh reconhecido. Experimente digitar o
comando x86_64-w64-mingw32-make nestes casos.

Confira o resultado com a lista de requisitos descrita neste documento.

### INSTALANDO O MINGW-W64
O MingW-w64 eh um ambiente de desenvolvimento para Microsoft Windows. Ele
inclui o compilador GCC e bibliotecas necessarias para criacao de aplicacoes
compativeis com a arquitetura x86-64.
Para instalar o MingW-w64 eh necessario uma conexao com a Internet. O endereco para baixar o MingW-w64 eh:

http://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/mingw-w64-v4.0.2.tar.bz2/download

As seguintes bibliotecas sao necessarias para compilar o jogo:
* Allegro
* Freetype
* OpenAL
* LibVorbis
* LibPNG
* LibJPEG Turbo

### COMPILANDO O JOGO
Para compilar o jogo, digite o comando:

```
MAKE
```

Em alguns sistemas, o comando MAKE nao eh reconhecido. Experimente digitar o
comando x86_64-w64-mingw32-make nestes casos.

### CONFIGURANDO O JOGO ANTES DE EXECUTAR
O jogo requer a instalacao de um codec MPEG-4 para execucao de videos.
Digite o comando abaixo antes de executar o jogo pela primeira vez.

```
MAKE INSTALL
```

Em alguns sistemas, o comando MAKE nao eh reconhecido. Experimente digitar o
comando x86_64-w64-mingw32-make nestes casos.

ATENCAO: Eh necessario privilegios de administrador do sistema para execucao
do comando acima.

### O INSTALADOR
Uma versão do instalador para teste do jogo esta disponivel para download no endereco:

https://www.dropbox.com/s/xl0q19258olyhsx/tp_douglas_jogo1.exe?dl=0
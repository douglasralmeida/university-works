TP3 de SO - fsshell

Comandos:

make       - compila o programa

make test  - cria uma imagem em branco e roda o programa em cima

make clean - exclui a imagem e arquivos temporários

make debug - executa o programa sob o GDB


Links úteis:

https://pt.wikipedia.org/wiki/Ext2

http://www.nongnu.org/ext2-doc/ext2.html

http://web.mit.edu/tytso/www/linux/ext2intro.html


Design:

|  BOOT  |   SB   |  GDT   |   BB   |   IB   |     IT    |  DB
-----------------------------------------------------------------
|  1024  |  1024  |  1024  |  1024  |  1024  |  1024x23  |  ....
|  ---   |  x000  |  x400  |  x800  |  xC00  |  x1000    |  ....
-----------------------------------------------------------------
   Bl.0     Bl.1     Bl.2     Bl.3     Bl.4     Bl.5        Bl.27
   
Esperado

  SB =  x0
  GDT = x400
  Bloco da tabela de nos i: 5
  Tabela de nos = x1000
  ROOT
  No i = 2
  Bloco do nó i do root = 5
  Endereco do nó i do root = x1000 + x80 = x1080

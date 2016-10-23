#Makefile do TP1 - Biblioteca do Filipe
#
#Douglas Rodrigue de Almeida
#

PROJECTNAME=tp1
CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -pedantic -std=c99 $(DEFS)
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer 
OBJFILES=strutils.o fila.o arvoreb.o livro.o memoria.o ordenador.o sistema_consulta.o sistema_es.o sistema_mb.o sistema.o principal.o
OBJECTS=$(addprefix $(OBJDIR), $(OBJFILES))
ARGS=

%.o: %.c
	@echo 
	@echo Compilando $<...
	$(CC) $(DBGFLAGS) $(CFLAGS) $< -o $@

$(PROJECTNAME): $(OBJECTS) 
	@echo 
	@echo Gerando executavel...
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

.PHONY: all
all:
	$(PROJECTNAME)
	
.PHONY:clean
clean:
	@echo 
	@echo Excluindo executavel...
	rm -f $(PROJECTNAME)
	@echo Excluindo objetos...
	rm -f $(OBJECTS)

.PHONY: debug
debug:
	gdb --args ./$(PROJECTNAME) $(ARGS)

.PHONY: memcheck
memcheck:
	valgrind -v --leak-check=yes --track-origins=yes ./$(PROJECTNAME) $(ARGS)

.PHONY: run
run:
	./$(PROJECTNAME) $(ARGS)

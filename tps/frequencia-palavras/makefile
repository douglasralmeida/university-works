#Makefile do TP0 - Frequencia de Palavras
#
#Douglas Rodrigue de Almeida
#

PROJECTNAME=teste
CC=gcc

MATRICULA=2015112728

CFLAGS=-c -Wall -Wextra -Wpedantic $(DEFS) -Iinclude/
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer 
BINDIR=bin
OBJDIR=obj
OBJFILES=trie.o test.o
OBJECTS=$(addprefix $(OBJDIR)/, $(OBJFILES))
SOURCEDIR=src
ARGS=

$(OBJDIR)/%.o: $(SOURCEDIR)/%.c
	@echo 
	@echo Compilando $<...
	$(CC) $(DBGFLAGS) $(CFLAGS) $< -o $@

$(PROJECTNAME): $(OBJECTS) 
	@echo 
	@echo Gerando executavel...
	$(CC) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LIBS)

.PHONY: all build clean debug memcheck run test

all:
	$(PROJECTNAME)

build:
	@echo 
	@echo Gerando arquivo compactado...
	tar zcvf ../$(MATRICULA).tar.gz doc/documentacao.pdf src/* include/* --exclude-vcs

clean:
	@echo 
	@echo Excluindo executavel...
	rm -f $(BINDIR)/$(PROJECTNAME)
	@echo Excluindo objetos...
	rm -f $(OBJECTS)
	
debug:
	gdb --args ./$(BINDIR)/$(PROJECTNAME) $(ARGS)

memcheck:
	valgrind -v --leak-check=yes --track-origins=yes $(BINDIR)/$(PROJECTNAME) $(ARGS)

run:
	./$(BINDIR)/$(PROJECTNAME) $(ARGS)
	
test:
	./executartestes

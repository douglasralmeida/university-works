#Makefile do TP0 - Frequencia de Palavras
#
#Douglas Rodrigue de Almeida
#

PROJECTNAME=tp0
CC=gcc

MATRICULA=2015112728

#Usar padrao c99 para suportar 10^16 palavras conforme pre-requisito do trabalho
CFLAGS=-std=c99 -c -Wall -Wextra -Wpedantic $(DEFS) -Iinclude/
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer 
BINDIR=bin
OBJDIR=obj
OBJFILES=trie.o principal.o
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

.PHONY: all
all:
	$(PROJECTNAME)
	
.PHONY:clean
clean:
	@echo 
	@echo Excluindo executavel...
	rm -f $(BINDIR)/$(PROJECTNAME)
	@echo Excluindo objetos...
	rm -f $(OBJECTS)

.PHONY: debug
debug:
	gdb --args ./$(BINDIR)/$(PROJECTNAME) $(ARGS)

.PHONY: deploy
deploy:
	@echo 
	@echo Gerando arquivo compactado...
	tar zcvf ../$(MATRICULA).tar.gz doc/documentacao.pdf src/* include/* --exclude-vcs

.PHONY: memcheck
memcheck:
	valgrind -v --leak-check=yes --track-origins=yes $(BINDIR)/$(PROJECTNAME) $(ARGS)

.PHONY: run
run:
	./$(BINDIR)/$(PROJECTNAME) $(ARGS)
	
.PHONY: test
test:
	./executartestes $(BINDIR)/$(PROJECTNAME)

#Makefile do TP1 - Biblioteca do Filipe
#
#Douglas Rodrigue de Almeida
#

PROJECTNAME=tp1
CC=gcc
CFLAGS=-c -Wall -Wextra -Wpedantic $(DEFS) -Iinclude/
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer 
BINDIR=bin
OBJDIR=obj
OBJFILES=strutils.o fila.o arvoreb.o livro.o memoria.o ordenador.o sistema_consulta.o sistema_es.o sistema.o principal.o
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
	mkdir -p $(PROJECTNAME)
	cp makefile $(PROJECTNAME)/makefile
	cp -r $(SOURCEDIR) $(PROJECTNAME)/$(SOURCEDIR)
	zip -r $(PROJECTNAME).zip $(PROJECTNAME)
	rm $(PROJECTNAME)/$(SOURCEDIR)/*	
	rmdir $(PROJECTNAME)/$(SOURCEDIR)
	rm $(PROJECTNAME)/*
	rmdir $(PROJECTNAME)

.PHONY: memcheck
memcheck:
	valgrind -v --leak-check=yes --track-origins=yes $(BINDIR)/$(PROJECTNAME) $(ARGS)

.PHONY: run
run:
	./$(BINDIR)/$(PROJECTNAME) $(ARGS)
	
.PHONY: test
test:
	./script/executartestes $(BINDIR)/$(PROJECTNAME)

#Makefile do TP2 - Andando na Física
#
#Douglas Rodrigue de Almeida
#

PROJECTNAME=tp2
CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -pedantic -std=c99 $(DEFS) -Iinclude/
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer 
BINDIR=bin
OBJDIR=obj
OBJFILES=list.o filaprior.o grafo_item.o grafo.o mapa.o mapa_caminhamento.o principal.o
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
	valgrind -v --leak-check=full --track-origins=yes --show-leak-kinds=all $(BINDIR)/$(PROJECTNAME) $(ARGS)

.PHONY: run
run:
	./$(BINDIR)/$(PROJECTNAME) $(ARGS)
	
.PHONY: test
test:
	./script/testar $(BINDIR)/$(PROJECTNAME)

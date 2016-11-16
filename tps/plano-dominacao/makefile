#Makefile do TP3 - Plano de dominação
#
#Douglas Rodrigue de Almeida
#

PROJECTNAME=tp3
CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -pedantic -std=c99 $(DEFS) -Iinclude/
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer
LDFLAGS=
BINDIR=bin
DEPLOYDIR=deploy
DOCDIR=doc
INCDIR=include
OBJDIR=obj
SOURCEDIR=src
OBJFILES=mundo.o principal.o
OBJECTS=$(addprefix $(OBJDIR)/, $(OBJFILES))
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
	@echo 
	@echo Depurando...
	gdb --args ./$(BINDIR)/$(PROJECTNAME) $(ARGS)

.PHONY: deploy
deploy:
	@echo 
	@echo Gerando arquivo compactado...
	cp $(SOURCEDIR)/* $(INCDIR)/* $(DOCDIR)/documentacao.pdf $(DEPLOYDIR)
	zip -j $(DEPLOYDIR)/$(PROJECTNAME).zip $(DEPLOYDIR)/*
	rm $(DEPLOYDIR)/*.c $(DEPLOYDIR)/*.h $(DEPLOYDIR)/*.pdf

.PHONY: memcheck
memcheck:
	@echo 
	@echo Verificando vazamento de memória...
	valgrind -v --leak-check=full --track-origins=yes --show-leak-kinds=all $(BINDIR)/$(PROJECTNAME) $(ARGS)

.PHONY: run
run:
	@echo 
	@echo Executando aplicação...
	./$(BINDIR)/$(PROJECTNAME) $(ARGS)
	
.PHONY: test
test:
	@echo 
	@echo Testando...
	./script/testar $(BINDIR)/$(PROJECTNAME) 

#TIPO ABSTRATO DE DADOS GRAFO
#DOUGLAS RODRIGUES DE ALMEIDA
#
#Makefile do TAD Grafo por Vetores
PROJECTNAME=test-grafo
CC=gcc
ARGS=

#Flags de compilação
CFLAGS=-c -Wall -Wextra -Wpedantic $(DEFS) -I../core/ -Iinclude/
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer 

#Diretorios do projeto
BINDIR=bin
OBJDIR=obj
TESTDIR=test
SOURCEDIR=src

#Arquivos do projeto
OBJFILES=	grafo.o test-grafo.o
OBJECTS=$(addprefix $(OBJDIR)/, $(OBJFILES))

#Compilar o codigo
$(OBJDIR)/%.o: $(SOURCEDIR)/%.c
	@echo 
	@echo Compilando $<...
	$(CC) $(DBGFLAGS) $(CFLAGS) $< -o $@

#Gerar executavel
$(PROJECTNAME): $(OBJECTS) 
	@echo 
	@echo Gerando executavel...
	$(CC) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LIBS)

#Regra padrao
.PHONY: all
all:
	$(PROJECTNAME)

#Limpar arquivos
.PHONY: clean
clean:
	@echo 
	@echo Excluindo executavel...
	rm -f $(BINDIR)/$(PROJECTNAME)
	@echo Excluindo objetos...
	rm -f $(OBJECTS)

#Depuracao
.PHONY: debug
debug:
	gdb --args ./$(BINDIR)/$(PROJECTNAME) $(ARGS)

#Checar vazamentos de memoria
.PHONY: memcheck
memcheck:
	valgrind -v --leak-check=full --track-origins=yes --show-leak-kinds=all $(BINDIR)/$(PROJECTNAME) $(ARGS)

#Executar aplicacao
.PHONY: run
run:
	./$(BINDIR)/$(PROJECTNAME) $(ARGS)

PROJECTNAME=main
CC=gcc

CFLAGS=-c -Wall -Wextra -Wpedantic $(DEFS) -Iinclude/
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer 
BINDIR=bin
OBJDIR=obj
OBJFILES=datautils.o arquivo.o cliente.o atendimento.o relatorio.o principal.o
OBJECTS=$(addprefix $(OBJDIR)/, $(OBJFILES))
SOURCEDIR=src

$(OBJDIR)/%.o: $(SOURCEDIR)/%.c
	@echo 
	@echo Compilando $<...
	$(CC) $(DBGFLAGS) $(CFLAGS) $< -o $@

$(PROJECTNAME): $(OBJECTS)
	@echo 
	@echo Gerando executavel...
	$(CC) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LIBS)

all:
	$(PROJECTNAME)

build:
	@echo 
	@echo Gerando arquivo compactado...
	tar zcvf ../1234.tar.gz * --exclude='main' --exclude='*.o' --exclude='*.txt' --exclude='*.pdf' --exclude='*.gz' --exclude-vcs

clean:
	@echo 
	@echo Excluindo executavel...
	rm -f $(BINDIR)/$(PROJECTNAME)
	@echo Excluindo objetos...
	rm -f $(OBJECTS)
	
debug:
	gdb --args ./$(BINDIR)/$(PROJECTNAME) bin/entrada.txt bin/saida.txt

memcheck:
	valgrind -v --leak-check=yes --track-origins=yes $(BINDIR)/$(PROJECTNAME) bin/entrada.txt bin/saida.txt
	valgrind -v --leak-check=yes --track-origins=yes $(BINDIR)/$(PROJECTNAME) bin/entradavazia.txt bin/saidavazia.txt

run:
	./$(BINDIR)/$(PROJECTNAME) bin/entrada.txt bin/saida.txt

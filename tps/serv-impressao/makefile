PROJECTNAME=main
CC=gcc

MATRICULA=2015112728

CFLAGS=-c -Wall -Wextra -Wpedantic $(DEFS) -Iinclude/
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer 
BINDIR=bin
OBJDIR=obj
OBJFILES=item.o filaprio.o principal.o
OBJECTS=$(addprefix $(OBJDIR)/, $(OBJFILES))
SOURCEDIR=src
ARGS=$(BINDIR)/entrada.txt $(BINDIR)/saida.txt

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
	tar zcvf ../$(MATRICULA).tar.gz * --exclude='main' --exclude='*.o' --exclude='*.txt' --exclude='*.pdf' --exclude='*.gz' --exclude-vcs

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
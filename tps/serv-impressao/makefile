PROJECTNAME=main
TESTNAME=test
CC=gcc

MATRICULA=2015112728

CFLAGS=-c -Wall -Wextra -Wpedantic $(DEFS) -Iinclude/
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer 
BINDIR=bin
OBJDIR=obj
TESTDIR=test
OBJFILES=list.c
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

.PHONY: all build clean debug memcheck run test

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

test:
	@echo Compilando item.c...
	$(CC) $(DBGFLAGS) $(CFLAGS) $(SOURCEDIR)/list.c -o $(OBJDIR)/list.o
	@echo Compilando test-list.c...
	$(CC) $(DBGFLAGS) $(CFLAGS) $(TESTDIR)/test-list.c -o $(TESTDIR)/test-list.o
	@echo Compilando executavel de teste...
	$(CC) $(LDFLAGS) -o $(TESTDIR)/test $(OBJDIR)/list.o $(TESTDIR)/test-list.o
	@echo Testando e depurando...
	gdb --args ./$(TESTDIR)/$(TESTNAME)
	@echo Testando uso de memoria...
	valgrind -v --leak-check=yes --track-origins=yes $(TESTDIR)/test



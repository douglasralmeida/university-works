#Makefile do TP1 de SO - Shell e Top
#
#Douglas Rodrigue de Almeida
#

PROJECTNAME=shell
TOPNAME=mytop
CC=gcc
CFLAGS=-c -Wall -Wextra $(DEFS)
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer
BINDIR=bin
OBJDIR=obj
OBJFILES=sh.o
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
	@echo TP1 de SO
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
	gdb --args ./$(BINDIR)/$(PROJECTNAME)

.PHONY: memcheck
memcheck:
	valgrind -v --leak-check=full --track-origins=yes --show-leak-kinds=all $(BINDIR)/$(PROJECTNAME)

.PHONY: run
run:
	./$(BINDIR)/$(PROJECTNAME)
	
.PHONY: test
test:
	./grade.sh

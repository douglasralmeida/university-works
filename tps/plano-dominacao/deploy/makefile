#Makefile do TP3 - Plano de Dominação
#
#Douglas Rodrigue de Almeida
#

PROJECTNAME=tp3
CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -pedantic -std=c99 $(DEFS)
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer 
OBJFILES=principal.o
OBJECTS=$(addprefix $(OBJDIR), $(OBJFILES))
ARGS=

%.o: %.c
	@echo 
	@echo Compilando $<...
	$(CC) $(DBGFLAGS) $(CFLAGS) $< -o $@

$(PROJECTNAME): $(OBJECTS) 
	@echo 
	@echo Gerando executavel...
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

.PHONY: all
all:
	$(PROJECTNAME)
	
.PHONY:clean
clean:
	@echo 
	@echo Excluindo executavel...
	rm -f $(PROJECTNAME)
	@echo Excluindo objetos...
	rm -f $(OBJECTS)

.PHONY: debug
debug:
	gdb --args ./$(PROJECTNAME) $(ARGS)

.PHONY: memcheck
memcheck:
	valgrind -v --leak-check=yes --track-origins=yes ./$(PROJECTNAME) $(ARGS)

.PHONY: run
run:
	./$(PROJECTNAME) $(ARGS)

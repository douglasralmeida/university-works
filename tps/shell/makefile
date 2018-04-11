#Makefile do TP1 de SO - Shell e Top
#
#Douglas Rodrigue de Almeida
#Saulo Weikert Bicalho
#

CC=gcc
CFLAGS=-c -Wall -Wextra $(DEFS)
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer
LDFLAGS=-pthread
BINDIR=bin
OBJDIR=obj
SOURCEDIR=src

SH_PROJECTNAME=shell
SH_OBJFILES=sh.o
SH_OBJECTS=$(addprefix $(OBJDIR)/, $(SH_OBJFILES))

MT_PROJECTNAME=meutop
MT_OBJFILES=meutop.o
MT_OBJECTS=$(addprefix $(OBJDIR)/, $(MT_OBJFILES))

MT_SIGNALTESTER=signaltester
MT_STFILES=signaltester.o
MT_STOBJ=$(addprefix $(OBJDIR)/, $(MT_STFILES))

ARGS=

$(OBJDIR)/%.o: $(SOURCEDIR)/%.c
	@echo 
	@echo Compilando $<...
	$(CC) $(DBGFLAGS) $(CFLAGS) $< -o $@

$(SH_PROJECTNAME): $(SH_OBJECTS) 
	@echo 
	@echo Gerando executavel do shell...
	$(CC) -o $(BINDIR)/$@ $^ $(LIBS)
	
$(MT_PROJECTNAME): $(MT_OBJECTS) 
	@echo 
	@echo Gerando executavel do meutop...
	$(CC) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LIBS)

$(MT_SIGNALTESTER): $(MT_STOBJ) 
	@echo 
	@echo Gerando executavel do singaltester...
	$(CC) -o $(BINDIR)/$@ $^ $(LIBS)

.PHONY: all
all:
	@echo TP1 de SO
	$(SH_PROJECTNAME)
	$(MT_PROJECTNAME)
	$(MT_SIGNALTESTER)
	
.PHONY:clear
clear:
	@echo 
	@echo Excluindo executaveis...
	rm -f $(BINDIR)/$(MT_PROJECTNAME)
	rm -f $(BINDIR)/$(SH_PROJECTNAME)
	@echo Excluindo objetos...
	rm -f $(SH_OBJECTS)
	rm -f $(MT_OBJECTS)
	rm -f $(MT_STFILES)

.PHONY: debugsh
debugsh:
	gdb --args ./$(BINDIR)/$(SH_PROJECTNAME)
	
.PHONY: debugmt
debugmt:
	gdb --args ./$(BINDIR)/$(MT_PROJECTNAME)

.PHONY: memchecksh
memchecksh:
	valgrind -v --leak-check=full --track-origins=yes --show-leak-kinds=all $(BINDIR)/$(SH_PROJECTNAME)
	
.PHONY: memcheckmt
memcheckmt:
	valgrind -v --leak-check=full --track-origins=yes --show-leak-kinds=all $(BINDIR)/$(MT_PROJECTNAME)

.PHONY: runsh
runsh:
	./$(BINDIR)/$(SH_PROJECTNAME)

.PHONY: runmt
runmt:
	./$(BINDIR)/$(MT_PROJECTNAME)

.PHONY: testsh
testsh:
	./grade.sh
	
.PHONY: testmt
testmt:
	./$(BINDIR)/signaltester

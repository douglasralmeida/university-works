#Makefile do TP3 de SO
#
#A1
#A2
#

PROJECTNAME=dcc_fs_shell
CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -pedantic
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer
BINDIR=bin
OBJDIR=obj
SOURCEDIR=src
OBJFILES=fs.o
OBJECTS=$(addprefix $(OBJDIR)/, $(OBJFILES))

$(OBJDIR)/%.o: $(SOURCEDIR)/%.c
	@echo 
	@echo Compilando $<...
	$(CC) $(DBGFLAGS) $(CFLAGS) $< -o $@

$(PROJECTNAME): $(OBJECTS)
	@echo 
	@echo Gerando executavel...
	$(CC) -o $(BINDIR)/$@ $^

fs.img:
	@echo 
	@echo Gerando imagem...
	dd if=/dev/zero of=$@ bs=1024 count=100
	mkfs.ext2 $@

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
	@echo Excluindo imagem...
	rm -f fs.img

.PHONY: debug
debug: fs.img
	@echo 
	@echo Iniciando GDB...
	gdb --args ./$(BINDIR)/$(PROJECTNAME) fs.img
	
.PHONY: run
run:
	./$(BINDIR)/$(PROJECTNAME)

.PHONY: test
test: fs.img
	@echo 
	@echo Executando aplicativo...
	./$(BINDIR)/$(PROJECTNAME) fs.img

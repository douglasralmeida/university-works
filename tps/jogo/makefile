# Makefile do jogo
# Dezembro de 2015

# Aluno Douglas Rodrigues de Almeida

#### Secao dos cabecalhos ####
PROJECTNAME=aterror
CC=gcc
DEFS=-D_UNICODE -DUNICODE -D_WIN32_WINNT=0x0600 -D_WIN32_IE=0x0800
# Comandos para usar no DEFS
# -D_UNICODE -DUNICODE		Adicona suporte a Unicode.
# -D_WIN32_WINNT=0x0600		O aplicativo requer Windows Vista ou superior.
# -D_WIN32_IE=0x0800		O aplicativo requer MS Internet Explorer 8 ou superior.

CFLAGS=-c -Wall -Wextra -Wpedantic $(DEFS) -Iinclude/
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer 
WRES=windres -Iinclude/
# O comando windres compila os recursos do aplicativo, como ícone, definicao de versao, etc.

LIBS=-lallegro -lallegro_image -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_primitives -lcomctl32 -lole32 -lstrmiids
LDFLAGS=-mwindows -municode
BINDIR=bin
OBJDIR=obj
OBJFILES=recursos.ro vetor.o funcoes.o matematica.o fisica.o colisoes.o mouse.o teclado.o arquivo.o video.o audio.o fonte.o graficos.o projetil.o personagem.o mapa.o fase.o painelstatus.o jogo.o menu.o janela.o janelas.o principal.o
OBJECTS=$(addprefix $(OBJDIR)/, $(OBJFILES))
RESDIR=res
SOURCEDIR=source
TESTDIR=test

#### Secao das regras ####
$(OBJDIR)/%.o: $(SOURCEDIR)/%.c
	@(echo. && echo Compilando $<...)
	$(CC) $(DBGFLAGS) $(CFLAGS) $< -o $@

$(OBJDIR)/%.ro: $(RESDIR)/%.rc
	@(echo. && echo Compilando $<...)
	$(WRES) $< -o $@

$(TESTDIR)/%.to: $(TESTDIR)/%.c
	@(echo. && echo Compilando $<...)
	$(CC) $(DBGFLAGS) $(CFLAGS) $< -o $@

.PHONY: all clean help install readme run sysinfo test debug
# Impede do comando nao ser executado caso exista um arquivo de mesmo nome ja atualizado.

all: clean $(PROJECTNAME).exe
	
$(PROJECTNAME).exe: $(OBJECTS)
	@(echo. && echo Gerando executavel...)
	$(CC) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LIBS)

clean:
	@echo Executando limpeza...
	del /q $(addprefix $(OBJDIR)\, $(OBJFILES))
	del /q $(BINDIR)\$(PROJECTNAME).exe
	
debug:
	gdb -q -ex 'cd bin' --args $(BINDIR)\$(PROJECTNAME).exe /d
	
help:
	@(echo Parametros disponiveis: && echo.)
	@echo MAKE			Compila o aplicativo.
	@echo MAKE CLEAN	Limpa os objetos e executaveis para uma nova compilacao.
	@echo MAKE DEBUG	Execute o jogo no modo de depuracao com a supervisao do GDB.
	@echo MAKE HELP		Exibe este menu de ajuda.
	@echo MAKE INSTALL	Prepare o sistema para a execucao do jogo. Execute-o antes de iniciar a primeira execucao.
	@echo MAKE README	Exibe o arquivo leiame do jogo. Leia-o antes de iniciar a primeira compilacao.

	@echo MAKE RUN		Executa o aplicativo ja compilado.
	@echo MAKE SYSINFO	Exibe informacoes do sistema relevantes para a compilacao.
	@echo MAKE TEST		Realiza testes unitários nas estruturas de dados.
	@echo.
	@echo *Caso o comando MAKE nao seja reconhecido, utilize x86_64-w64-mingw32-make.

install:
	regsvr32 $(BINDIR)\mp4demux.dll
	
# Use o comando MAKE README para verificar se seu computador possui os requisitos minimos
# de compilacao e execucao do jogo.	
readme:
	@type readme
	@echo.
	
run:
	cd bin && $(PROJECTNAME).exe	
	
sysinfo:
	@(echo Informacoes do sistema: && echo.)
	@(ver | find "Microsoft")
	@(echo Arquitetura: ^< %PROCESSOR_ARCHITECTURE%)
	@(gcc -v 2>&1 | find "gcc version")
	@(gcc -v 2>&1 | find "Target")	
	@(gdb -v | find "GNU gdb")
	@(ld -v | find "GNU ld")
	@(windres --version | find "GNU windres")
	@(dlltool --version | find "GNU dlltool")
	@(make -v | find "GNU Make")

test: $(OBJECTS) $(TESTDIR)/teste.to
	@(echo Gerando testes... && echo.)
	$(CC) -o $(TESTDIR)/teste.exe $(OBJECTS) $(TESTDIR)/teste.to $(LIBS) -lcriterion
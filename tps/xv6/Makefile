## MAKEFILE DO XV6 MODIFICADO
#  Aluno: 
#  Aluno: 

# Para compilação cruzada (em outro SO, ex: MacOS X)
# TOOLPREFIX = i386-jos-elf

# Para compilação com ferramentas nativas (ex: Linux x86)
# TOOLPREFIX = 

# Se TOOLPREFIX não foi configurado, tentar encontrar o GCC correto
ifndef TOOLPREFIX
TOOLPREFIX := $(shell if i386-jos-elf-objdump -i 2>&1 | grep '^elf32-i386$$' >/dev/null 2>&1; \
	then echo 'i386-jos-elf-'; \
	elif objdump -i 2>&1 | grep 'elf32-i386' >/dev/null 2>&1; \
	then echo ''; \
	else echo "***" 1>&2; \
	echo "*** Erro: Não foi possível encontrar uma versão i386-*-elf do GCC/binutils." 1>&2; \
	echo "*** O diretório do i386-jos-elf-gcc está no PATH do sistema?" 1>&2; \
	echo "*** Se seu compilador i386-*-elf estiver instalado com um prefixo" 1>&2; \
	echo "*** de comando diferente de 'i386-jos-elf-', configure a variável" 1>&2; \
	echo "*** TOOLPREFIX para o tal prefixo e execute o comando 'make' novamente." 1>&2; \
	echo "*** Para desativar este erro, execute 'gmake TOOLPREFIX= ...'." 1>&2; \
	echo "***" 1>&2; exit 1; fi)
endif

# Se o makefile nao econtrar o QEMU, informe seu caminho aqui
# QEMU = qemu-system-i386

# Se QEMU não foi configurado, tentar ecnontrar o QEMU correto
ifndef QEMU
QEMU = $(shell if which qemu > /dev/null; \
	then echo qemu; exit; \
	elif which qemu-system-i386 > /dev/null; \
	then echo qemu-system-i386; exit; \
	elif which qemu-system-x86_64 > /dev/null; \
	then echo qemu-system-x86_64; exit; \
	else \
	qemu=/Applications/Q.app/Contents/MacOS/i386-softmmu.app/Contents/MacOS/i386-softmmu; \
	if test -x $$qemu; then echo $$qemu; exit; fi; fi; \
	echo "***" 1>&2; \
	echo "*** Erro: Não foi possível econtrar o executável do QEMU." 1>&2; \
	echo "*** O diretório que contem o executável do QEMU está no PATH do sistema?" 1>&2; \
	echo "*** ou você tentou configurar a variável QEMU no Makefile?" 1>&2; \
	echo "***" 1>&2; exit 1)
endif

CC = $(TOOLPREFIX)gcc
LD = $(TOOLPREFIX)ld
OBJCOPY = $(TOOLPREFIX)objcopy
OBJDUMP = $(TOOLPREFIX)objdump
CFLAGS = -fno-pic -static -fno-builtin -fno-strict-aliasing -O2 -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer
CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)
# O comando ld do FreeBSD exige ''elf_i386_fbsd''
LDFLAGS += -m $(shell $(LD) -V | grep elf_i386 2>/dev/null | head -n 1)
BINDIR=bin
CNFDIR=config
OBJDIR=obj
SPTDIR=scripts
SRCDIR=src
SYMDIR=sym

OBJS = \
	bio.o\
	console.o\
	exec.o\
	file.o\
	fs.o\
	ide.o\
	ioapic.o\
	kalloc.o\
	kbd.o\
	lapic.o\
	log.o\
	main.o\
	mp.o\
	picirq.o\
	pipe.o\
	proc.o\
	sleeplock.o\
	spinlock.o\
	string.o\
	swtch.o\
	syscall.o\
	sysfile.o\
	sysproc.o\
	trapasm.o\
	trap.o\
	uart.o\
	vectors.o\
	vm.o\

OBJFILES = $(addprefix $(OBJDIR)/, $(OBJS))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.S
	$(CC) -c -o $@ $< $(CFLAGS)

##Imagem do SO

# XV6.IMG
# >Cria o arquivo xv6.img com 10.000 kb de tamanho preechido com \0
# >Anexa uma copia do arquivo bootblock (tam. max. 512 bytes)
#  no arquivo xv6.img sem truncar
# >Anexa uma copia do arquivo kernel na imagem xv6, a partir
#  do segundo bloco (cada bloco tem 512 bytes) sem truncar
xv6.img: $(OBJDIR)/bootblock $(OBJDIR)/kernel fs.img
	@echo 
	@echo "Criando imagem do SO..."
	dd if=/dev/zero of=xv6.img count=10000
	dd if=$(OBJDIR)/bootblock of=xv6.img conv=notrunc
	dd if=$(OBJDIR)/kernel of=xv6.img seek=1 conv=notrunc

xv6memfs.img: $(OBJDIR)/bootblock $(OBJDIR)/kernelmemfs
	dd if=/dev/zero of=xv6memfs.img count=10000
	dd if=$(OBJDIR)/bootblock of=xv6memfs.img conv=notrunc
	dd if=$(OBJDIR)/kernelmemfs of=xv6memfs.img seek=1 conv=notrunc

##Bloco do setor de Boot do HD

# BOOTBLOCK
# >Compila os arquivos bootasm.S bootmain.c
# >Vincula os arquivos compilados num unico arquivo executavel bootblock.o
# >Desmonta o executavel bootblock.o no arquivo bootblock.asm
# >Cria o arquivo bootblock copiado de bootlock.o sem os simbolos, info. de realocação
#  e depuração, copiando somente a seção .text do executavel no formato binário puro
# >Checa se o arquivo bootblock possui mais de 510 bytes, anexando ao final, caracteres
#  \0 até completar 510 bytes. Por fim, anexa os caracteres \55(HEX) e \AA(HEX).
#  O arquivo final (que será o bloco do setor de boot) possuirá exatos 512 bytes de tamanho
# * Ver: https://en.wikipedia.org/wiki/Master_boot_record
$(OBJDIR)/bootblock: $(SRCDIR)/bootasm.S $(SRCDIR)/bootmain.c
	@echo 
	@echo "Gerando bloco de inicialização..."
	$(CC) $(CFLAGS) -fno-pic -O -nostdinc -I. -c -o $(OBJDIR)/bootmain.o $(SRCDIR)/bootmain.c
	$(CC) $(CFLAGS) -fno-pic -nostdinc -I. -c -o $(OBJDIR)/bootasm.o $(SRCDIR)/bootasm.S
	$(LD) $(LDFLAGS) -N -e start -Ttext 0x7C00 -o $(OBJDIR)/bootblock.o $(OBJDIR)/bootasm.o $(OBJDIR)/bootmain.o
	$(OBJDUMP) -S $(OBJDIR)/bootblock.o > $(SYMDIR)/bootblock.asm
	$(OBJCOPY) -S -O binary -j .text $(OBJDIR)/bootblock.o $@
	./$(SPTDIR)/sign.pl $@

##Kernel

$(OBJDIR)/entryother: $(SRCDIR)/entryother.S
	$(CC) $(CFLAGS) -fno-pic -nostdinc -I. -c -o $(OBJDIR)/entryother.o $<
	$(LD) $(LDFLAGS) -N -e start -Ttext 0x7000 -o $(OBJDIR)/entryother.out $(OBJDIR)/entryother.o
	$(OBJCOPY) -S -O binary -j .text $(OBJDIR)/entryother.out $@
	$(OBJDUMP) -S $(OBJDIR)/entryother.out > $(SYMDIR)/entryother.asm

$(OBJDIR)/initcode: $(SRCDIR)/initcode.S
	$(CC) $(CFLAGS) -nostdinc -I. -c -o $(OBJDIR)/initcode.o $<
	$(LD) $(LDFLAGS) -N -e start -Ttext 0 -o $(OBJDIR)/initcode.out $(OBJDIR)/initcode.o
	$(OBJCOPY) -S -O binary $(OBJDIR)/initcode.out $@
	$(OBJDUMP) -S $(OBJDIR)/initcode.o > $(SYMDIR)/initcode.asm

$(OBJDIR)/kernel: $(OBJFILES) $(OBJDIR)/entry.o $(OBJDIR)/entryother $(OBJDIR)/initcode $(SPTDIR)/kernel.ld
	@echo 
	@echo "Gerando kernel..."
	$(LD) $(LDFLAGS) -T $(SPTDIR)/kernel.ld -o $@ $(OBJDIR)/entry.o $(OBJFILES) -b binary $(OBJDIR)/initcode $(OBJDIR)/entryother
	$(OBJDUMP) -S $@ > $(SYMDIR)/kernel.asm
	$(OBJDUMP) -t $@ | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > $(SYMDIR)/kernel.sym

# kernelmemfs is a copy of kernel that maintains the
# disk image in memory instead of writing to a disk.
# This is not so useful for testing persistent storage or
# exploring disk buffering implementations, but it is
# great for testing the kernel on real hardware without
# needing a scratch disk.
MEMFSOBJS = $(filter-out $(OBJDIR)/ide.o,$(OBJFILES)) $(OBJDIR)/memide.o
$(OBJDIR)/kernelmemfs: $(MEMFSOBJS) $(OBJDIR)/entry.o $(OBJDIR)/entryother $(OBJDIR)/initcode $(SPTDIR)/kernel.ld fs.img
	$(LD) $(LDFLAGS) -T $(SPTDIR)/kernel.ld -o $@ $(OBJDIR)/entry.o  $(MEMFSOBJS) -b binary $(OBJDIR)/initcode $(OBJDIR)/entryother fs.img
	$(OBJDUMP) -S $@ > $(SYMDIR)/kernelmemfs.asm
	$(OBJDUMP) -t $@ | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > $(SYMDIR)/kernelmemfs.sym

##Tags para VI/Emacs
tags: $(OBJFILES) $(SRCDIR)/entryother.S $(BINDIR)/_init
	etags *.S *.c

##Tabela de interrupções/traps
$(SRCDIR)/vectors.S: $(SPTDIR)/vectors.pl
	perl $< > $@

ULIB = $(OBJDIR)/ulib.o $(OBJDIR)/usys.o $(OBJDIR)/printf.o $(OBJDIR)/umalloc.o

##Apps incluídos no SO
$(BINDIR)/_%: $(OBJDIR)/%.o $(ULIB)
	$(LD) $(LDFLAGS) -N -e main -Ttext 0 -o $@ $^
	$(OBJDUMP) -S $@ > $(SYMDIR)/$*.asm
	$(OBJDUMP) -t $@ | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > $(SYMDIR)/$*.sym

$(BINDIR)/_forktest: $(OBJDIR)/forktest.o $(ULIB)
	# forktest has less library code linked in - needs to be small
	# in order to be able to max out the proc table.
	$(LD) $(LDFLAGS) -N -e main -Ttext 0 -o $@ $(OBJDIR)/forktest.o $(OBJDIR)/ulib.o $(OBJDIR)/usys.o
	$(OBJDUMP) -S $@ > $(SYMDIR)/forktest.asm

# Aplicativo Make FileSystem
# >Compila e gera o executável que constrói imagens com o sistema de arquivos
$(BINDIR)/mkfs: $(SRCDIR)/mkfs.c
	$(CC) -Werror -Wall -o $@ $<

# Prevent deletion of intermediate files, e.g. cat.o, after first build, so
# that disk image changes after first build are persistent until clean.  More
# details:
# http://www.gnu.org/software/make/manual/html_node/Chained-Rules.html
.PRECIOUS: $(OBJDIR)/%.o

APPS=\
	_cat\
	_corretor\
	_date\
	_echo\
	_forktest\
	_grep\
	_init\
	_kill\
	_ln\
	_ls\
	_mkdir\
	_rm\
	_sh\
	_stressfs\
	_usertests\
	_wc\
	_zombie\
	
APPFILES = $(addprefix $(BINDIR)/, $(APPS))

##SISTEMA DE ARQUIVOS
# >Gera uma imagem com o sistema de arquivos e
#  copia os arquivos e aplicativos do SO
fs.img: $(BINDIR)/mkfs README $(APPFILES)
	@echo 
	@echo "Gerando FS..."
	cp README $(BINDIR)/
	(cd $(BINDIR) && ./mkfs ../$@ README $(APPS))

-include *.d

clean:
	@echo 
	@echo "Executando limpeza..."
	rm -f *.tex *.dvi *.idx *.aux *.log *.ind *.ilg \
	*.o *.d *.asm *.sym $(SRCDIR)/vectors.S bootblock entryother \
	initcode initcode.out kernel xv6.img fs.img kernelmemfs $(BINDIR)/mkfs \
	.gdbinit $(BINDIR)/README $(SYMDIR)/* $(OBJDIR)/* \
	$(APPFILES)

# make a printout
FILES = $(shell grep -v '^\#' $(CNFDIR)/runoff.list)
PRINT = $(CNFDIR)/runoff.list $(CNFDIR)/runoff.spec README toc.hdr toc.ftr $(FILES)

xv6.pdf: $(PRINT)
	./$(SPTDIR)/runoff
	ls -l xv6.pdf

print: xv6.pdf

##COMANDOS PARA EMULADORES

bochs : fs.img xv6.img
	if [ ! -e .bochsrc ]; then ln -s $(CNFDIR)/dot-bochsrc .bochsrc; fi
	bochs -q

# try to generate a unique GDB port
GDBPORT = $(shell expr `id -u` % 5000 + 25000)
# QEMU's gdb stub command line changed in 0.11
QEMUGDB = $(shell if $(QEMU) -help | grep -q '^-gdb'; \
	then echo "-gdb tcp::$(GDBPORT)"; \
	else echo "-s -p $(GDBPORT)"; fi)
ifndef CPUS
CPUS := 2
endif
QEMUOPTS = -drive file=fs.img,index=1,media=disk,format=raw -drive file=xv6.img,index=0,media=disk,format=raw -smp $(CPUS) -m 512 $(QEMUEXTRA)

qemu: fs.img xv6.img
	$(QEMU) -serial mon:stdio $(QEMUOPTS)

qemu-memfs: xv6memfs.img
	$(QEMU) -drive file=xv6memfs.img,index=0,media=disk,format=raw -smp $(CPUS) -m 256

qemu-nox: fs.img xv6.img
	$(QEMU) -nographic $(QEMUOPTS)

.gdbinit: $(CNFDIR)/.gdbinit.tmpl
	sed "s/localhost:1234/localhost:$(GDBPORT)/" < $^ > $@

qemu-gdb: fs.img xv6.img $(CNFDIR)/.gdbinit
	@echo "*** Agora, execute 'gdb'." 1>&2
	$(QEMU) -serial mon:stdio $(QEMUOPTS) -S $(QEMUGDB)

qemu-nox-gdb: fs.img xv6.img $(CNFDIR)/.gdbinit
	@echo "*** Agora, execute 'gdb'." 1>&2
	$(QEMU) -nographic $(QEMUOPTS) -S $(QEMUGDB)

EXTRA=\
	mkfs.c ulib.c user.h cat.c echo.c forktest.c grep.c kill.c \
	ln.c ls.c mkdir.c rm.c stressfs.c usertests.c wc.c zombie.c \
	printf.c umalloc.c \
	README toc.* \
	$(SPTDIR)/*.pl $(SPTDIR)/runoff $(SPTDIR)/runoff1 $(CNFDIR)/runoff.list \
	$(CNFDIR)/dot-bochsrc $(CNFDIR)/.gdbinit.tmpl $(CNFDIR)/gdbutil \

dist:
	rm -rf dist
	mkdir dist
	for i in $(FILES); \
	do \
		grep -v PAGEBREAK $$i >dist/$$i; \
	done
	sed '/CUT HERE/,$$d' Makefile >dist/Makefile
	echo >dist/runoff.spec
	cp $(EXTRA) dist

dist-test:
	rm -rf dist
	make dist
	rm -rf dist-test
	mkdir dist-test
	cp dist/* dist-test
	cd dist-test; $(MAKE) print
	cd dist-test; $(MAKE) bochs || true
	cd dist-test; $(MAKE) qemu

tar:
	rm -rf /tmp/xv6
	mkdir -p /tmp/xv6
	cp dist/* dist/.gdbinit.tmpl /tmp/xv6
	(cd /tmp; tar cf - xv6) | gzip >xv6-doug.tar.gz

.PHONY: dist-test dist
